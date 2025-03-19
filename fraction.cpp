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
	//���������
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
	Fraction operator / (const Fraction& other) const {

		if (other.numerator == 0) {
			throw std::invalid_argument("Cannot divide by a fraction with a numerator of zero.");
		}
		int new_numerator = (integer * denominator + numerator) * other.denominator;
		int new_denominator = denominator * (other.integer * other.denominator + other.numerator);
		return Fraction(0, new_numerator, new_denominator);
	}

	// ���������������� >>��������ַ�������ȡ Fraction ����
	friend istream& operator>>(istream& in, Fraction& frac) {
		string s;
		in >> s;  // ��ȡ������ַ���

		// �ж��Ƿ�����������ַ� '/'
		if (s.find("'") != string::npos) {
			// ��������ʽ���� "2'3/8"
			size_t pos = s.find("'");
			frac.integer = stoi(s.substr(0, pos)); // ��ȡ��������
			s = s.substr(pos + 1); // ȥ����������

			pos = s.find('/');
			frac.numerator = stoi(s.substr(0, pos)); // ��ȡ����
			frac.denominator = stoi(s.substr(pos + 1)); // ��ȡ��ĸ
		}
		else if (s.find("/") != string::npos) {
			// �������ʽ���� "3/8"
			size_t pos = s.find('/');
			frac.integer = 0;  // û����������
			frac.numerator = stoi(s.substr(0, pos)); // ��ȡ����
			frac.denominator = stoi(s.substr(pos + 1)); // ��ȡ��ĸ
		}
		else {
			// ������ʽ���� "3"
			frac.integer = stoi(s); // ��ȡ��������
			frac.numerator = 0;     // û�з�������
			frac.denominator = 1;   // Ĭ�Ϸ�ĸΪ 1
		}

		frac.simplify(); // �򻯷���
		return in;
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