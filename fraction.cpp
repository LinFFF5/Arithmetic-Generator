#include "generation.h"

class Fraction {
private:
	int integer;
	int numerator;
	int denominator;

public:
	//Ĭ�Ϲ��캯��
	Fraction(int num = 0, int den = 1) : integer(0), numerator(num), denominator(den) {
		if (denominator == 0) {
			std::cerr << "Error: Denominator cannot be zero!" << std::endl;
			denominator = 1;
		}
		simplify();
	}
	//���캯��
	Fraction(int integerpart, int num, int den) : integer(integerpart), numerator(num), denominator(den){
		if (den == 0) {
			throw std::invalid_argument("Denominator cannot be zero.");
		}
		simplify();
	}

	//����
	void simplify() {

		if (numerator >= denominator) {

			integer += numerator / denominator;
			numerator = numerator % denominator;
		}

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

	string toString() const {

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
};