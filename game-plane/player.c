#include "data.h"
#include "player.h"
#include <conio.h>

void player_move(gameState* game, char input)
{
		game->gameArea[game->player.y][game->player.x] = ' ';
		switch (input)
		{
		case 'w':
		case'W':
			if (game->player.y > 1)
			{
				game->player.y -= game->player.speed;
				game->player.direct = 'W';
			}
			break;// 上
		case 's':
		case'S':
			if (game->player.y < show_hight - 2)
			{
				game->player.y += game->player.speed;
				game->player.direct = 'S';
			}
			break;//下
		case 'a':
		case'A':
			if (game->player.x > 1)
			{
				game->player.x -= game->player.speed;
				game->player.direct = 'A';
			}
			break;//左
		case 'd':
		case'D':
			if (game->player.x < show_length - 2)
			{
				game->player.x += game->player.speed;
				game->player.direct = 'D';
			}
			break;//右
		}
		game->gameArea[game->player.y][game->player.x] = game->player.symbol;
} //先清空再绘制，并且调整飞机朝向