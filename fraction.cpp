#include "main.h"

class Fraction {
private:
	int integer;
	int numerator;
	int denominator;

public:

	//��������
	Fraction(int integerpart, int num, int den) {
		if (den == 0) {
			throw std::invalid_argument("Denominator cannot be zero.");
		}
		integer = integerpart;
		numerator = num;
		denominator = den;
		simplify();
	}

	//����
	void simplify() {

		if (integer != 0) {
			integer += numerator / denominator;
		}
		else {
			integer = numerator / denominator;
		}
		//���·���
		numerator = numerator % denominator;
		// ʹ�����Լ���򻯷���
		int gcd_value = gcd(abs(numerator), denominator); 
		numerator /= gcd_value;
		denominator /= gcd_value;
	}

	//�ӷ�
	Fraction operator + (const Fraction& other) const {

		int new_numerator = (integer * denominator + numerator) * other.denominator
			+ (other.integer * other.denominator + other.numerator) * denominator;
		int new_denominator = denominator * other.denominator;
		return Fraction(0, new_numerator, new_denominator);
	}
	//����
	Fraction operator - (const Fraction& other) const {
		int new_numerator = (integer * denominator + numerator) * other.denominator
			- (other.integer * other.denominator + other.numerator) * denominator;
		int new_denominator = denominator * other.denominator;
		return Fraction(0, new_numerator, new_denominator);
	}
	//�˷�
	Fraction operator * (const Fraction& other) const {
		int new_numerator = (integer * denominator + numerator) * (other.integer * other.denominator + other.numerator);
		int new_denominator = denominator * other.denominator;
		return Fraction(0, new_numerator, new_denominator);
	}
	//����
	Fraction operator/(const Fraction& other) const {
		if (other.numerator == 0) {
			throw std::invalid_argument("Cannot divide by a fraction with a numerator of zero.");
		}
		int new_numerator = (integer * denominator + numerator) * other.denominator;
		int new_denominator = denominator * (other.integer * other.denominator + other.numerator);
		return Fraction(0, new_numerator, new_denominator);
	}

};