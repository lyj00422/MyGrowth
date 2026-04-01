#include "object.h"

int main()
{
	srand(time(nullptr));
	game_scene game;
	game.game_start();
	ExMessage msg = { 0 };

	while (true)
	{
		msg = getmessage(EX_KEY);
		if (msg.message == WM_KEYDOWN)
		{
			if (msg.vkcode == VK_RETURN)
				break; //开始游戏
			else if(msg.vkcode == VK_ESCAPE)
			{
				cleardevice();
				TCHAR s0[] = _T("不是，你真退啊？？？");
				outtextxy(text_hight, text_width, s0);
				getchar();
				closegraph();
				break;
			}
		}
	}

	while (true)
	{
		game.run();

		while (peekmessage(&msg, EX_KEY))
		{
			game.changeDir(msg);
		}
		Sleep(92);
	}

	getchar();

	return 0;
}