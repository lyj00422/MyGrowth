#include "data.h"
#include "bullet.h"
#include <stdbool.h>

void initBullet(gameState* game)
{
	for (int i = 0; i < bullet_number; i++)
	{
		game->dot[i].active = false; //一开始位置都是空的
	}
} //子弹的初始化

void shot(gameState* game)
{
	for (int i = 0; i < bullet_number; i++)
	{
		if (!game->dot[i].active)
		{
			game->dot[i].x = game->player.x;
			game->dot[i].y = game->player.y; //以我方飞机为基准
			game->dot[i].speed = game->player.speed; //速度可以改，进行难度改变（已废弃）
			game->dot[i].direct = game->player.direct; //发射方向
			game->dot[i].symbol = '|';
			game->dot[i].active = true; //占位置
			break;
		}
	}
}//发射子弹

void bullet_move(gameState* game)
{
	for (int i = 0; i < bullet_number; i++)
	{
		if (game ->dot[i].active == true && game->gameArea[game->dot[i].y][game->dot[i].x] != game->player.symbol)
			game->gameArea[game->dot[i].y][game->dot[i].x] = ' '; //先清空再绘制
		if (game->dot[i].active) //找到第一个未被激活的子弹
		{
			switch (game->dot[i].direct) //根据方向发射
			{
			case 'W':
				if (game->dot[i].y > 1)
				{
					game->dot[i].y -= game->dot[i].speed;
					game->gameArea[game->dot[i].y][game->dot[i].x] = game->dot[i].symbol;//子弹不断移动
				}
				else
				{
					game->dot[i].active = false; //超出边界就释放子弹
				}
				break;
			case 'S': //同理
				if (game->dot[i].y < show_hight - 2)
				{
					game->dot[i].y += game->dot[i].speed;
					game->gameArea[game->dot[i].y][game->dot[i].x] = game->dot[i].symbol;
				}
				else
				{
					game->dot[i].active = false;
				}
				break;
			case 'A':
				if (game->dot[i].x > 1)
				{
					game->dot[i].x -= game->dot[i].speed;
					game->gameArea[game->dot[i].y][game->dot[i].x] = game->dot[i].symbol;
				}
				else
				{
					game->dot[i].active = false;
				}
				break;
			case 'D':
				if (game->dot[i].x < show_length - 2)
				{
					game->dot[i].x += game->dot[i].speed;
					game->gameArea[game->dot[i].y][game->dot[i].x] = game->dot[i].symbol;
				}
				else
				{
					game->dot[i].active = false;
				}
				break;

			}
		}
	}
}