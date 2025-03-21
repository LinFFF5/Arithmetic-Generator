#pragma once
#include <iostream>
#include <numeric>  // for std::gcd
#include <cmath>    
#include <cstdlib>  // ���� rand() �� srand()
#include <ctime>    //��ʼ���������
#include <string>
#include <sstream>  //
#include <fstream>  //����ļ���
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
	//��������
	Fraction(int num = 0, int den = 1);
	Fraction(int integerpart, int num, int den);
	//����
	void simplify();
	//�ӷ�
	Fraction operator + (const Fraction& other) const;
	//����
	Fraction operator - (const Fraction& other) const;
	//�˷�
	Fraction operator * (const Fraction& other) const;
	//����
	Fraction operator / (const Fraction& other) const;
	//�����ʽ
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

