#pragma once
#include <easyx.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <conio.h>

//游戏中用到的相关数据
#define scene_hight 640 
#define scene_width 480 //长度和宽度写反了
#define text_hight 40
#define text_width 20
#define text_startx 20
#define text_starty 20
#define spirit_length 10
#define fame_width 2
#define win_continue 20
//精灵类
class spirit
{
protected:
	int m_x;
	int m_y;
	COLORREF m_color;
public:
	spirit():spirit(0,0,RED){};
	spirit(int x, int y, COLORREF color = RED) :m_x(x), m_y(y), m_color(color) {};
	virtual void draw();
	void move(int dx,int dy);
	int getX() const { return m_x; };
	int getY() const { return m_y; };
	bool collision(const spirit other);
};

//蛇类
class snake :public spirit
{
protected:
	std::vector<spirit> nodes;
public:
	int dir;
	snake() :snake(scene_hight / 2, scene_width / 2) {};
	snake(int x, int y) :spirit(x, y), dir(VK_UP)
	{
		nodes.push_back(spirit(scene_hight/2,scene_width/2));  //生成在画面中间
		nodes.push_back(spirit(scene_hight / 2 , scene_width / 2+ spirit_length));
		nodes.push_back(spirit(scene_hight / 2 , scene_width / 2+ spirit_length * 2));  //初始化三节蛇
	}
	void draw() override;
	bool SnakeEatFood(const spirit& other);
	bool SnakeStrikeWall();
	bool SnakeStrikeBody();
	void grow();
	void move();
};

//食物类
class food :public spirit
{
public:
	food():spirit(0,0,YELLOW)
	{
		generatePos();
	}
	void generatePos();
	void draw() override;
	void changePos();
};

//画面类
class game_scene
{
private:
	spirit spirit;
	snake snake;
	food food;
	int score = 0;
	time_t startTime;
	int win = false;
public:
	game_scene()
	{
		startTime = time(nullptr);
	}
	void game_start();
	void run();
	void changeDir(ExMessage& msg);
	void scoreup();
	void StrikeWall();
	void StrikeSelf();
	void ShowTime();
	void ShowScore();
	void ShowPicture();
};