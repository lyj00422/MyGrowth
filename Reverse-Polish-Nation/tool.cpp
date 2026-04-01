#include "tool.h"

int RightAos(char s)
{
	return s == '^';
}
int IsOperator(char s)
{
	return s == '+' || s == '-' || s == '/' || s == '*' || s == '^';
}

int IsLeft(char s)
{
	return s == '(' || s == '（';
}

int Precedence(char input)
{
	if (input == '^') return 3;
	if (input == '*' || input == '/') return 2;
	if (input == '+' || input == '-') return 1;
	return 0;
}

int IsRight(char s)
{
	return s == ')' || s == '）';
}

std::string GetInfix()
{
	std::string input;
	std::cout << "请输入中缀表达式" << std::endl;
	std::getline(std::cin, input);

	return input;
}

std::string GetPolish()
{
	std::string input;
	std::cout << "请输入后缀表达式" << std::endl;
	std::getline(std::cin, input);

	return input;
}

std::string ChangeInfix(std::string input)
{
	std::stack<char> stack;
	std::string output;
	for (int i = 0; i < input.size(); i++)
	{
		if (isdigit(input[i]))
		{
			while (i < input.size() && isdigit(input[i]))
			{
				output += input[i];
				i++;
			}
			i--;
			output += ' ';
		}
		else if (IsLeft(input[i]))
		{
			stack.push(input[i]);
		}
		else if (IsRight(input[i]))
		{
			while (!stack.empty() && stack.top() != '(' && stack.top() != '（')
			{
				output += stack.top();
				output += ' ';
				stack.pop();
			}

			if(!stack.empty() && IsLeft(stack.top())) stack.pop();
		}
		else if (isspace(input[i])) continue;
		else if (IsOperator(input[i]))
		{
			while (!stack.empty() && stack.top() != '(' && stack.top() != '（')
			{
				if (RightAos(input[i]))
				{
					if (Precedence(stack.top()) > Precedence(input[i]))
					{
						output += stack.top();
						output += ' ';
						stack.pop();
					}
					else break;
				}
				else
				{
					if (Precedence(stack.top()) >= Precedence(input[i]))
					{
						output += stack.top();
						stack.pop();
					}
					else break;
				}
			}

			stack.push(input[i]);
		}
	}

	while (!stack.empty())
	{
		output += stack.top();
		stack.pop();
	}

	return output;
}

std::string ChangePolish(std::string input)
{
	std::stack<std::string> st;
	for (int i = 0; i < input.size(); i++)
	{
		if (isspace(input[i])) continue;
		else if (isdigit(input[i]))
		{
			std::string num;
			while (i < input.size() && isdigit(input[i]))
			{
				num += input[i];
				i++;
			}
			i--;
			st.push(num);
		}
		else if (IsOperator(input[i]))
		{
			std::string right = st.top(); st.pop();
			std::string left = st.top(); st.pop();
			st.push("(" + left + input[i] + right + ")");
		}
	}

	return st.top();
}

double CalPolish(std::string& output)
{
	std::stack<double> st;
	for (int i = 0; i < output.size(); i++)
	{
		if (isdigit(output[i]))
		{
			double num = 0;
			while (i < output.size() && std::isdigit(output[i]))
			{
				num = num * 10 + (output[i] - '0');
				i++;
			}
			i--;
			st.push(num);
		}
		else if (IsOperator(output[i]))
		{
			double right = st.top(); st.pop();
			double left = st.top(); st.pop();
			double res = 0.0;

			switch (output[i])
			{
			case '+': res = left + right; break;
			case '-': res = left - right; break;
			case '*': res = left * right; break;
			case '/': res = left / right; break;
			case '^': res = pow(left, right); break;
			}
			st.push(res);
		}
	}
	return st.top();
}

double CalInfix(std::string output)
{
	std::stack<double> num;
	std::stack<char> op;


	auto apply = [](double left, char op,double right ) -> double
		{
			switch (op)
			{
			case '+': return left + right;
			case '-': return left - right;
			case '*': return left * right;
			case '/': return left / right;
			case '^': return pow(left, right);
			}
		};

	auto get = [&]()
		{
			double right = num.top(); num.pop();
			double left = num.top(); num.pop();
			char ops = op.top(); op.pop();

			num.push(apply(left, ops, right));
		};

	for (int i = 0; i < output.size(); i++)
	{
		if (isspace(output[i])) continue;
		else if (isdigit(output[i]))
			{
				double sum = 0.0;
				while (i < output.size() && isdigit(output[i]))
				{
					sum = sum * 10 + (output[i] - '0');
					i++;
				}
				i--;
				num.push(sum);
			}
		else if (IsLeft(output[i]))
		{
			op.push(output[i]);
		}
		else if (IsRight(output[i]))
		{
			while (!op.empty() && !IsLeft(op.top()))
			{
				get();
			}
			if (!op.empty()) op.pop();
		}
		else if (IsOperator(output[i]))
		{
			while (!op.empty() && !IsLeft(op.top())) {
				if ((RightAos(output[i]) && Precedence(op.top()) > Precedence(output[i])) || (!RightAos(output[i]) && Precedence(op.top()) >= Precedence(output[i])))
				{
					get();
				}
				else break;
			}
			op.push(output[i]);
		}
	}
	while (!op.empty())
	{
		get();
	}
	return num.top();
}