#pragma once
#include <iostream>
#include <numeric>  // for std::gcd
#include <cmath>    
#include <cstdlib>  // 用于 rand() 和 srand()
#include <ctime>    //初始化随机种子
#include <string>
#include <sstream>  //
#include <fstream>  //输出文件流
#include <vector>
#include <stack>
using namespace std;

#ifndef FRACTION_H
#define FRACTION_H
class Fraction {

public:
	int integer;
	int numerator;
	int denominator;
	//析构函数
	Fraction(int num = 0, int den = 1);
	Fraction(int integerpart, int num, int den);
	//化简
	void simplify();
	//加法
	Fraction operator + (const Fraction& other) const;
	//减法
	Fraction operator - (const Fraction& other) const;
	//乘法
	Fraction operator * (const Fraction& other) const;
	//除法
	Fraction operator / (const Fraction& other) const;
	//输出格式
	string toString();
};
#endif


int generate_integer(int n);
Fraction generate_fraction(int n);
bool ifgenerateFraction();
char generateOperator();

bool isOperator(char c);
int getOperatorPrecedence(char op);
vector<string> infixToPostfix(const string& expression);
Fraction evaluatePostfix(const vector<string>& postfix);
Fraction calculate(const string& expression);
Fraction generate_fraction_with_max(int range, const Fraction& max_value);
Fraction parseResult(const std::string& result_str);
string generate_Problem(string& problem, int r);

