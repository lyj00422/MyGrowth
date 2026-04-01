#pragma once //避免重复包含头文件
#include <stdbool.h>

#define show_hight 28
#define show_length 45 //窗口大小
#define game_time 60 //游戏时间60秒
#define bullet_number 10
#define enemy_number 10
#define magic_number 3 //子弹、敌机、道具数量
#define enemy_emerge_rate 15
#define enemy_move_rate 5
#define magic_emerge_rate 80
#define magic_move_rate 20
#define game_rate 100 //各个东西的帧率

typedef struct
{
	int x;
	int y;
	char symbol;
	int speed;
	char direct;
}plane; //我方飞机信息，前者是基本的，后面的是给道具做准备

typedef struct
{
	int speed;
	bool active;
	int x;
	int y;
	char direct;
	char symbol;
}bullet; //子弹信息

typedef struct
{
	int x;
	int y;
	int speed;
	bool active;
	char symbol;
}enemy; //敌机信息

typedef struct
{
	int x;
	int y;
	int speed;
	bool active;
	char symbol;
}prop; //道具信息

typedef struct
{
	plane player;
	char gameArea[show_hight][show_length];
	bullet dot[10];
	enemy foe[10];
	prop miracle[3];
	int score;
	int game_mode;
	int time;
}gameState; //游戏基本信息