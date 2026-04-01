#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <cctype>
#include <cmath>
#include <string>

std::string GetInfix();
std::string GetPolish();
std::string ChangeInfix(std::string input);
std::string ChangePolish(std::string input);
int IsOperator(char s);
int IsLeft(char s);
int IsRight(char s);
int Precedence(char input);
int RightAos(char s);
double CalPolish(std::string& output);
double CalInfix(std::string ouput);
