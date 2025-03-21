#include "generation.h"
#include <stdexcept>

Fraction::Fraction(int num, int den) : integer(0), numerator(num), denominator(den) {
	if (denominator == 0) {
		//throw std::invalid_argument("1:Denominator cannot be zero");
		denominator = 1;
	}
	simplify();
}

Fraction::Fraction(int integerpart, int num, int den) : integer(integerpart), numerator(num), denominator(den) {
	if (den == 0) {
		//throw std::invalid_argument("2:Denominator cannot be zero");
		denominator = 1;
	}
	simplify();
}
	//化简
void Fraction::simplify() {

	if (numerator >= denominator) {

		integer += numerator / denominator;
		numerator = numerator % denominator;
	}

	// 使用最大公约数简化分数
	int gcd_value = gcd(abs(numerator), denominator); 
	numerator /= gcd_value;
	denominator /= gcd_value;
}

//加法
Fraction Fraction::operator + (const Fraction& other) const {

	int new_numerator = (integer * denominator + numerator) * other.denominator
			+ (other.integer * other.denominator + other.numerator) * denominator;
	int new_denominator = denominator * other.denominator;
	return Fraction(0, new_numerator, new_denominator);
}

//减法
Fraction Fraction::operator - (const Fraction& other) const {

	int new_numerator = (integer * denominator + numerator) * other.denominator
			- (other.integer * other.denominator + other.numerator) * denominator;
	int new_denominator = denominator * other.denominator;
	return Fraction(0, new_numerator, new_denominator);
}

//乘法
Fraction Fraction::operator * (const Fraction& other) const {

	int new_numerator = (integer * denominator + numerator) * (other.integer * other.denominator + other.numerator);
	int new_denominator = denominator * other.denominator;
	return Fraction(0, new_numerator, new_denominator);
}

//除法
Fraction Fraction::operator / (const Fraction& other) const {

	int new_numerator = 0;
	int new_denominator = 1;
	if (other.numerator == 0 && other.denominator == 1 && other.integer != 0) {
		//分数除以整数
		new_numerator = integer * denominator + numerator;
		new_denominator = other.denominator * denominator;
	}
	else if (numerator == 0 && denominator == 1 && integer != 0) {
		//整数除以分数
		new_numerator = integer * other.denominator;
		new_denominator = other.integer * other.denominator + other.numerator;
	}
	else if (numerator == 0 && denominator == 1 && integer != 0 
		&& other.numerator == 0 && other.denominator == 1 && other.integer != 0) {
		//整数除以整数
		new_numerator = integer;
		new_denominator = other.integer;
	}
	else {
		//分数除以分数
		new_numerator = (integer * denominator + numerator) * other.denominator;
		new_denominator = denominator * (other.integer * other.denominator + other.numerator);
	}
	return Fraction(0, new_numerator, new_denominator);
}


string Fraction::toString() {

	stringstream ss;
	if (integer != 0) {
		ss << integer;
		if (numerator != 0) {
			ss << "'" << numerator << "/" << denominator;
		}
	}
	else if (numerator != 0) {
		ss << numerator << "/" << denominator;
	}
	else {
		ss << "0";
	}
	return ss.str();
}
