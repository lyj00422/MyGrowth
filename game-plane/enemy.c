#include "enemy.h"
#include "data.h"
#include <time.h>
#include <windows.h>

void enemy_init(gameState* game)
{
	for (int i = 0; i < enemy_number; i++)
	{
		game->foe[i].y = 1; //敌机应该生成在最上端
		game->foe[i].x = 0; //初始化
		game->foe[i].symbol = '$';
		game->foe[i].active = false;
		game->foe[i].speed = 1;
	}
}

void enemy_emerge(gameState* game)
{
	static int count = 0; //帧率
	static int a = 0;
	count++;
	if (!a)
	{
		srand((unsigned int)time(NULL));
		a = 1;
	} //只初始化种子一次

	if (count == enemy_emerge_rate)
	{
		count = 0;
		int num = rand() % (show_length - 2) + 1; //保证敌机生成在游戏界面内
		for (int i = 0; i < enemy_number; i++)
		{
			if (!game->foe[i].active)
			{
				game->foe[i].x = num;
				game->foe[i].active = true;
				break; //找到第一个有位置的飞机
			}
		}
	};
}

void enemy_move(gameState* game)
{
	static int count = 0; //帧率
	count++;

	if (count == enemy_move_rate)
	{
		count = 0;
		for (int i = 0; i < enemy_number; i++)
		{
			if (game->foe[i].active) //所有释放的敌机
			{
				game->gameArea[game->foe[i].y][game->foe[i].x] = ' '; //先清空
				if (game->foe[i].y < show_hight - 2)
				{
					game->foe[i].y += game->foe[i].speed;
					game->gameArea[game->foe[i].y][game->foe[i].x] = game->foe[i].symbol; //在界面内就下落
				}
				else
				{
					game->game_mode = 2;
				}//到下边界判负
			}
		}
	}
}