#include "object.h"

//精灵类实现函数
void spirit::draw()
{
	setfillcolor(m_color);
	fillrectangle(m_x, m_y, m_x + spirit_length, m_y + spirit_length);
}

bool spirit::collision(const spirit other)
{
	return other.m_x == m_x && other.m_y == m_y;
}

void spirit::move(int dx,int dy)
{
	m_x += dx;
	m_y += dy;
}

//蛇类实现函数
void snake::draw()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i].draw();
	}
}

void snake::move()
{
	int temp_x = nodes[0].getX(), temp_y = nodes[0].getY();

	switch (dir)
	{
	case VK_UP: temp_y -= spirit_length; break;
	case VK_DOWN: temp_y += spirit_length; break;
	case VK_RIGHT: temp_x += spirit_length; break;
	case VK_LEFT: temp_x -= spirit_length; break;
	}
	spirit new_head(temp_x, temp_y, RED);
	nodes.insert(nodes.begin(), new_head);
	nodes.pop_back();
}

void snake::grow()
{
	int tempx = nodes.back().getX();
	int tempy = nodes.back().getY();
	nodes.push_back(spirit(tempx,tempy,m_color));
}

bool snake::SnakeEatFood(const spirit& other)
{
	return nodes[0].collision(other);
}

bool snake::SnakeStrikeWall()
{
	int tempx = nodes[0].getX();
	int tempy = nodes[0].getY();

	return tempx < fame_width || tempx > scene_hight - fame_width || tempy < fame_width || tempy > scene_width - fame_width;
}

bool snake::SnakeStrikeBody()
{
	int flag = false;

	for (int i = 1; i < nodes.size(); i++)
	{
		if (nodes[0].collision(nodes[i]))
		{
			flag = true;
		}
	}

	return flag;
}

//食物类实现函数
void food::generatePos()
{
	// 计算可生成的范围（考虑边框宽度和食物大小）
	int minX = fame_width;
	int maxX = scene_hight - fame_width - spirit_length;
	int minY = fame_width;
	int maxY = scene_width - fame_width - spirit_length;

	m_x = (minX + rand() % (maxX - minX + 1)) % 64 * 10;
	m_y = (minY + rand() % (maxY - minY + 1)) % 48 * 10;
}

void food::draw()
{
	setfillcolor(YELLOW);
	solidellipse(m_x, m_y, m_x + spirit_length, m_y + spirit_length);
}

void food::changePos()
{
	generatePos();
}

//游戏图像类实现函数
void game_scene::game_start()
{
	initgraph(scene_hight,scene_width); //绘制窗口
	setfillcolor(LIGHTCYAN); //设置背景颜色
	fillrectangle(0,0,scene_hight, scene_width); //填充亮青色
	settextcolor(BROWN); //字体颜色
	settextstyle(text_hight, text_width,L"微软雅黑"); //字体

	TCHAR s0[] = _T("欢迎游玩贪吃蛇小游戏");
	TCHAR s1[] = _T("按ENTER继续");
	TCHAR s2[] = _T("按ESC退出");

	outtextxy(text_startx, text_starty, s0);
	outtextxy(text_startx, text_starty + text_hight, s1);
	outtextxy(text_startx, text_starty + text_hight * 2, s2); //输出字体
}

void game_scene::run()
{
	if (win)
	{
		ShowPicture();
		return;
	}
	BeginBatchDraw();
	cleardevice();
	setlinecolor(WHITE);      	        
	setlinestyle(PS_SOLID, fame_width);  //绘制边框，为白色   
	rectangle(fame_width, fame_width, scene_hight - fame_width, scene_width - fame_width);
	snake.draw();
	food.draw();
	ShowScore();
	ShowTime();
	EndBatchDraw();
	snake.move();
	scoreup();
	StrikeWall();
	StrikeSelf();
}

void game_scene::changeDir(ExMessage& msg)
{
		switch (msg.vkcode)
		{
		case VK_UP:
			if (snake.dir != VK_DOWN)
				snake.dir = msg.vkcode;
			break;

		case VK_DOWN:
			if (snake.dir != VK_UP)
				snake.dir = msg.vkcode;
			break;

		case VK_RIGHT:
			if (snake.dir != VK_LEFT)
				snake.dir = msg.vkcode;
			break;

		case VK_LEFT:
			if (snake.dir != VK_RIGHT)
				snake.dir = msg.vkcode;
			break;
	}
}

void game_scene::scoreup()
{
	if (score >= win_continue)
	{
		win = true;
		return;
	}
	if (snake.SnakeEatFood(food))
	{
		snake.grow();
		food.changePos();
		score++;
	}
}

void game_scene::StrikeWall()
{
	if (snake.SnakeStrikeWall())
	{
		cleardevice();
		settextcolor(RED);
		settextstyle(text_hight,text_width , L"微软雅黑");
		TCHAR s0[] = _T("撞墙辣！！！！");
		outtextxy(text_startx, text_starty,s0);
		getchar();
		return;
	}
}

void game_scene::StrikeSelf()
{
	if (snake.SnakeStrikeBody())
	{
		cleardevice();
		settextcolor(RED);
		settextstyle(text_hight, text_width, L"微软雅黑");
		TCHAR s0[] = _T("撞到自己了!!!废物！");
		outtextxy(text_startx, text_starty, s0);
		getchar();
		return;
	}
}

void game_scene::ShowScore()
{
	TCHAR text_score[50];
	swprintf_s(text_score, _T("当前得分：%d"), score);
	settextcolor(LIGHTRED);
	settextstyle(text_hight/2, text_width/2, L"微软雅黑");
	int x = text_startx;
	int y = text_starty;  
	outtextxy(x, y, text_score);
}

void game_scene::ShowTime()
{
	time_t currentTime = time(nullptr); // 获取当前时间
	double elapsed = difftime(currentTime, startTime); // 计算存活时间（秒）
	// 转换存活时间为字符串
	TCHAR timeStr[50];
	swprintf_s(timeStr, _T("你存活了:%.0f 秒"), elapsed); // 使用 _stprintf 将 double 类型转换为字符串
	// 设置文本颜色
	settextcolor(WHITE);
	// 设置文本大小
	settextstyle(text_hight/2, text_width/2, L"微软雅黑");
	// 在屏幕上绘制文本
	outtextxy(text_startx, text_starty+text_width, timeStr);
}

void game_scene::ShowPicture()
{
		IMAGE image;
		if ((loadimage(&image, _T("asset\\picture.jpg"),scene_hight,scene_width) != NULL)) // 或检查 image.getwidth() > 0
		{
			std::cout << "????" << std::endl;
		}
		cleardevice();

		/*int x = (scene_width - image.getwidth()) / 2;    
		int y = (scene_hight - image.getheight()) / 2;*/

		putimage(0, 0, &image);
		_getch();

}
