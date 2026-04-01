#include <string>
#include "tool.h"

int main()
{
	for (;;)
	{
		std::cout << "请输入数字：" << std::endl;
		std::cout << "(0表示会输入退出，1表示会输入中缀表达式，2表示会输入后缀表达式）" << std::endl;
		int mod;
		std::cin >> mod;
		std::cin.ignore();
		int flag = 0;
		switch (mod)
		{
		case 0: return 0;
		case 1:
		{
			auto input = GetInfix();
			auto output = ChangeInfix(input);
			auto res = CalPolish(output);
			std::cout << output << std::endl;
			std::cout << res << std::endl;
			break;
		}
		case 2:
			auto input = GetPolish();
			auto output = ChangePolish(input);
			auto res = CalInfix(output);
			std::cout << output << std::endl;
			std::cout << res << std::endl;
			break;
		}
	}
}