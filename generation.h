#pragma once
#include <iostream>
#include <numeric>  // for std::gcd
#include <cmath>    
#include <cstdlib>  // ���� rand() �� srand()
#include <ctime>    //��ʼ���������
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
	//������ַ�������ȡ Fraction ����
	friend istream& operator>>(istream& in, Fraction& frac);
	//�����ʽ
	string toString() const;
};