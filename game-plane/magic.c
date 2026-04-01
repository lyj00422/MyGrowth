#include "data.h"
#include "magic.h"
#include "time.h"

//以下逻辑和enemy.c逻辑一致，即直接复制的
void magic_init(gameState* game)
{
	for (int i = 0; i < magic_number; i++)
	{
		game->miracle[i].y = 1;
		game->miracle[i].x = 0;
		game->miracle[i].symbol = '@';
		game->miracle[i].active = false;
		game->miracle[i].speed = 1;
	}
} //初始化

void magic_emerge(gameState* game)
{
	static int count = 0;
	static int once = 0;
	if (!once)
	{
		srand((unsigned int)time(NULL));
		once++;
	}
	count++;

	if (count == magic_emerge_rate) //出现比敌机晚
	{
		int num = rand() % (show_length - 2) + 1;
		count = 0;
		for (int i = 0; i < magic_number; i++)
		{
			if (!game->miracle[i].active)
			{
				game->miracle[i].x = num;
				game->miracle[i].active = true;
				break;
			}
		}
	}
}

void magic_move(gameState* game)
{
	static int count = 0;
	count++;

	if (count == magic_move_rate) //道具的移动要比敌机晚
	{
		count = 0;
		for (int i = 0; i < magic_number; i++)
		{
			if (game->miracle[i].active)
			{
				game->gameArea[game->miracle[i].y][game->miracle[i].x] = ' ';
				if (game->miracle[i].y < show_hight - 2)
				{
					game->miracle[i].y += game->miracle[i].speed;
					game->gameArea[game->miracle[i].y][game->miracle[i].x] = game->miracle[i].symbol;
				}
				else
				{
					game->miracle[i].active = false;
					game->miracle[i].y = 1;
				}
			}
		}
	}
}