#include "data.h"
#include "cash.h"

void bullet_enemy(gameState* game)
{
	for (int i = 0; i < bullet_number; i++)
	{
		for (int j = 0; j < enemy_number; j++)
		{
			if (game->dot[i].y == game->foe[j].y && game->dot[i].x == game->foe[j].x) //当相碰时
			{
				game->score++; //分数加一
				game->dot[i].active = false;
				game->foe[j].active = false; //释放位置
				game->foe[j].y = 1; //重置
				game->gameArea[game->dot[i].y][game->dot[i].x] = ' '; //相撞后消失
			}
		}
	}
} //子弹与敌机

void foe_player(gameState* game)
{
	for (int i = 0; i < enemy_number; i++)
	{
		if (game->foe[i].x == game->player.x && game->foe[i].y == game->player.y)
		{
			game->game_mode = 1;
		}
	}
} //我方飞机与敌机相碰就判负

void miracle_player(gameState* game)
{
	int count = 0; //分数
	for (int i = 0; i < magic_number; i++)
	{
		if (game->miracle[i].active == true && game->miracle[i].x == game->player.x && game->miracle[i].y == game->player.y)//当我方飞机与道具相碰时
		{
			game->gameArea[game->miracle[i].y][game->miracle[i].x] = game->player.symbol; //我方飞机吃掉道具
			game->miracle[i].active = false; //释放位置
			game->miracle[i].y = 1;  //重置
			for (int j = 0; j < 10; j++) //清空敌机
			{
				if(game->foe[j].active)
				{
					count++;
					game->gameArea[game->foe[j].y][game->foe[j].x] = ' ';
					game->foe[j].active = false;
					game->foe[j].y = 1;
				}
			}
			break;
		}

	}
	game->score += count; //增加清空的飞机的分数
}

void bullet_miracle(gameState* game)
{
	int key = 0;
	int count = 0; //分数
	for (int i = 0; i < bullet_number; i++)
	{
		if (key) break;
		for (int j = 0; j < magic_number; j++)
		{
			if (key) break;
			if (game->dot[i].y == game->miracle[j].y && game->dot[i].x == game->miracle[j].x)
			{
				game->dot[i].active = false;
				game->miracle[j].active = false;
				game->miracle[j].y = 1;
				game->gameArea[game->dot[i].y][game->dot[i].x] = ' '; //判断相撞后进行重置
				for (int k = 0; k < 10; k++) //开始清空敌机
				{
					if (game->foe[k].active)
					{
						count++;
						game->gameArea[game->foe[k].y][game->foe[k].x] = ' ';
						game->foe[k].active = false;
						game->foe[k].y = 1;
					}
				}
				game->score += count;
				key = 1;
			}
		}
	}
}