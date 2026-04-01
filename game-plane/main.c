#include "render.h"
#include "data.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "cash.h"
#include "score.h"
#include "magic.h"
#include "modeChange.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>

int main()
{
	char input = '0';
	gameState game; //定义用户输入和游戏状态

	initShow(&game);
	initBullet(&game);
	enemy_init(&game);
	magic_init(&game);

	clock_t start_time = clock();
	const int game_span =game_time;
	int remaining_time = 0;// 游戏时长20秒

	some_word_to_say();

	for (;;)
	{
		switch (game.game_mode)
		{
		case 1:
			refresh();
			if (!(score(&game)))
			printf("你在自杀吗？！\n 得分%d\n", game.score);
			wait(&game);
			if (game.game_mode == 6) continue; //重玩
			return 1;
		case 2:
			refresh();
			if (!(score(&game)))
			printf("人家都杀到你家里了，你在干嘛！\n 得分%d\n", game.score);
			wait(&game);
			if (game.game_mode == 6) continue;
			return 2;
		case 3:
			refresh();
			if (!(score(&game)))
			printf("时间到了 伙计\n 得分%d\n", game.score);
			wait(&game);
			if (game.game_mode == 6) continue;
			return 3;
		case 4:
			refresh();
			if (!(score(&game)))
			printf("为什么不玩下去，嗯？look in my eyes！\n 得分%d\n", game.score);
			wait(&game);
			if (game.game_mode == 6) continue;
			return 4;
		case 5:
			pause(&game);
			if (game.game_mode == 6) continue;
			continue;
		case 6:
			replay(&game);
			game.time = remaining_time = 40;
			game.score = 0;
			game.game_mode = 0;
			start_time = clock();
			continue;
		} //游戏的不同状态，结束、暂停、重玩

		double elapsed_seconds = (double)(clock() - start_time) / CLOCKS_PER_SEC;
		int remaining_time = game_span - (int)elapsed_seconds; //计算时间
		if (remaining_time <= 0)
		{
			game.game_mode = 3;
			continue;
		} // 检查是否超时
		game.time = remaining_time; // 更新游戏时间

		refresh(); //刷新屏幕
		plantShow(&game);
		printf("分数: %d     剩余时间: %d秒\n", game.score, remaining_time); //显示剩余时间和分数
		enemy_emerge(&game);
		magic_emerge(&game);//刷新敌人

		if (_kbhit())
		{
			input = _getch();
			if (input == 'q' || input == 'Q')
			{
				game.game_mode = 4;
				continue;
			}
			else if (input == ' ')
			{
				shot(&game);
			}
			else if (input == 'e' || input == 'E')
			{
				game.game_mode = 5;
				continue;
			}
			else if (input == 'r' || input == 'R')
			{
				game.game_mode = 6;
				continue;
			}
			player_move(&game, input);
		} //读取输入，进行强制退出、攻击、暂停、重玩

		bullet_move(&game);
		enemy_move(&game);
		magic_move(&game);//移动模块

		bullet_enemy(&game);
		foe_player(&game);
		miracle_player(&game);
		bullet_miracle(&game);//碰撞模块

		Sleep(game_rate); //控制游戏帧率
	}

	return 0;
}