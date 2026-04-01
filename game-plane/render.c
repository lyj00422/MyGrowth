#include "data.h"
#include "render.h"
#include <windows.h>
#include <stdio.h>
#include <time.h>


void initShow(gameState* game)
{
	for (int i = 0; i < show_hight; i++)
	{
		for (int j = 0; j < show_length; j++)
		{
			game->gameArea[i][j] = ' ';
		}
	}//整体初始化
	for (int i = 0; i < show_hight; i++)
	{
		game->gameArea[i][0] = '|';
	} //左边界
	for (int i = 0; i < show_hight; i++)
	{
		game->gameArea[i][show_length - 1] = '|';
	} //右边界

	game->score = 0;
	game->game_mode = 0;
	game->player.x = (show_length - 1) / 2;
	game->player.y = (show_hight - 2); //将飞机放置于画面正下方中央
	game->player.symbol = 'M'; //飞机形状
	game->player.speed = 1;
	game->gameArea[game->player.y][game->player.x] = game->player.symbol;
};//初始化画面，以便后续加入重开功能

void plantShow(gameState* game)
{
	for (int i = 0; i < show_hight; i++)
	{
		for (int j = 0; j < show_length; j++)
		{
			printf("%c", game->gameArea[i][j]);
			if (j == show_length - 1) printf("\n");
		}
	}
};

void refresh()
{
	system("cls");
}; //本来想在这基础上添加功能（废弃）

void wait(gameState* game) //解决外部exe运行时游戏结束后界面直接消失
{
	int count = 0;
	clock_t start_time = clock();
	printf("请按三次Y退出，按R重玩，或者等待10秒\n"); //解决误触，以让玩家看清得分
	while ((double)((clock() - start_time) / CLOCKS_PER_SEC) < 10) //两种退出方式
	{
		if (_kbhit())
		{
			char in = _getch();

			if (in == 'Y' || in == 'y')
			{
				count++;
				if (count == 3)
				{
					break;
				}
			}
			else if (in == 'r' || in == 'R')
			{
				game->game_mode = 6;
				break;
			}
		}
	}
}

void some_word_to_say()
{
	printf("简易版飞机大战\n");
	printf("WASD移动,Q强制退出,F重新开始,E暂停,空格攻击\n");
	printf("根据最后一次移动的方向发射对应方向的子弹\n");
	printf("希望你喜欢我的游戏\n");
	printf("按任意键继续\n");
	system("pause");
} //前言