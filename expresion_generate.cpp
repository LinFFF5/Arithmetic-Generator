#include "generation.h"


//�������һ�� [1,n]����
int generate_integer(int n) {

    return rand() % n + 1;
}

//�������һ�����������ӷ�Χ��[1, n]����ĸ��Χ��[1, n]
Fraction generate_fraction (int n) {

    int numerator = rand() % n + 1;
    int denominator = rand() % n + 1;
    return Fraction(0, numerator, denominator);
}

//���ѡ��һ�������
char generateOperator() {
    int option = rand() % 4;  // ����0-3֮��������
    switch (option) {
    case 0: return '+';
    case 1: return '-';
    case 2: return '*';
    case 3: return '/';
    default: return '+';
    }
}
//����������Ľ��
string calculate(const string& operand_str1, const string& operand_str2, char option) {

    stringstream ss1(operand_str1), ss2(operand_str2);
    Fraction operand_1, operand_2;
    int integer_1, integer_2;

    if (operand_str1.find('/') != string::npos) {
        //�Ƿ���
        ss1 >> operand_1;
    }
    else {
        ss1 >> integer_1;
        operand_1 = Fraction(integer_1, 0, 1);  // ��ɷ���
    }
    if (operand_str2.find('/') != string::npos) {
        


        ss2 >> integer_2;
    }
    else {
        ss2 >> operand_2;
    }

}



string expresion_generate(int n) {

    Fraction f();


    return ;
}

