#pragma once
#include <iostream>
#include <numeric>  // for std::gcd
#include <cmath>    
#include <cstdlib>  // 用于 rand() 和 srand()
#include <ctime>    //初始化随机种子
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Fraction {
private:
	int integer;
	int numerator;
	int denominator;

public:

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
	//允许从字符串流读取 Fraction 对象
	friend istream& operator>>(istream& in, Fraction& frac);
	//输出格式
	string toString() const;
};