#include "generation.h"

class Fraction {
private:
	int integer;
	int numerator;
	int denominator;

public:
	//默认构造函数
	Fraction(int num = 0, int den = 1) : integer(0), numerator(num), denominator(den) {
		if (denominator == 0) {
			std::cerr << "Error: Denominator cannot be zero!" << std::endl;
			denominator = 1;
		}
		simplify();
	}
	//构造带分数
	Fraction(int integerpart, int num, int den) : integer(integerpart), numerator(num), denominator(den){
		if (den == 0) {
			throw std::invalid_argument("Denominator cannot be zero.");
		}
		simplify();
	}

	//化简
	void simplify() {

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
	Fraction operator + (const Fraction& other) const {

		int new_numerator = (integer * denominator + numerator) * other.denominator
			+ (other.integer * other.denominator + other.numerator) * denominator;
		int new_denominator = denominator * other.denominator;
		return Fraction(0, new_numerator, new_denominator);
	}

	//减法
	Fraction operator - (const Fraction& other) const {

		int new_numerator = (integer * denominator + numerator) * other.denominator
			- (other.integer * other.denominator + other.numerator) * denominator;
		int new_denominator = denominator * other.denominator;
		return Fraction(0, new_numerator, new_denominator);
	}

	//乘法
	Fraction operator * (const Fraction& other) const {

		int new_numerator = (integer * denominator + numerator) * (other.integer * other.denominator + other.numerator);
		int new_denominator = denominator * other.denominator;
		return Fraction(0, new_numerator, new_denominator);
	}

	//除法
	Fraction operator / (const Fraction& other) const {

		if (other.numerator == 0) {
			throw std::invalid_argument("Cannot divide by a fraction with a numerator of zero.");
		}
		int new_numerator = (integer * denominator + numerator) * other.denominator;
		int new_denominator = denominator * (other.integer * other.denominator + other.numerator);
		return Fraction(0, new_numerator, new_denominator);
	}

	// 重载输入流操作符 >>，允许从字符串流读取 Fraction 对象
	friend istream& operator>>(istream& in, Fraction& frac) {
		string s;
		in >> s;  // 读取输入的字符串

		// 判断是否包含分数的字符 '/'
		if (s.find("'") != string::npos) {
			// 带分数格式，如 "2'3/8"
			size_t pos = s.find("'");
			frac.integer = stoi(s.substr(0, pos)); // 获取整数部分
			s = s.substr(pos + 1); // 去掉整数部分

			pos = s.find('/');
			frac.numerator = stoi(s.substr(0, pos)); // 获取分子
			frac.denominator = stoi(s.substr(pos + 1)); // 获取分母
		}
		else if (s.find("/") != string::npos) {
			// 真分数格式，如 "3/8"
			size_t pos = s.find('/');
			frac.integer = 0;  // 没有整数部分
			frac.numerator = stoi(s.substr(0, pos)); // 获取分子
			frac.denominator = stoi(s.substr(pos + 1)); // 获取分母
		}
		else {
			// 整数格式，如 "3"
			frac.integer = stoi(s); // 获取整数部分
			frac.numerator = 0;     // 没有分数部分
			frac.denominator = 1;   // 默认分母为 1
		}

		frac.simplify(); // 简化分数
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