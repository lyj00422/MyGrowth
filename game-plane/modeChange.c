#include "data.h"
#include "modeChange.h"
#include "render.h"
#include "bullet.h"
#include "enemy.h"
#include "magic.h"
#include <windows.h>
#include <time.h>

void pause(gameState* game)
{
	printf("按R重玩，其余键继续\n");
	char in = _getch();
	if (in == 'r' || in == "R")
	{
		game->game_mode = 6;
	}
	else
	{
		game->game_mode = 0;//重置游戏状态
	}
} //暂停功能 

void replay(gameState* game)
{
	initShow(game);
	initBullet(game);
	enemy_init(game);
	magic_init(game);
} //初始化