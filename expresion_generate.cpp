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

//�Ƿ����ɷ���
bool ifgenerateFraction() {
    return rand() % 2;
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
    //������
    Fraction result;
    switch (option) {
        case '+': result = operand_1 + operand_2;
        case '-': result = operand_1 - operand_2;
        case '*': result = operand_1 * operand_2;
        case '/': result = operand_1 / operand_2;
        default: return "���������";
    }
    return result.toString();

}

//������Ŀ
string generate_Problem(string& problem, int r) {

    string result;  // �洢������
    int operator_sum = (rand() % 3) + 1; // ���������
    bool isFractionProblem = ifgenerateFraction(); 
    string operand1_str;

    if (isFractionProblem) {
        operand1_str = generate_fraction(r).toString();  //true���ɷ���
    }
    else {
        operand1_str = to_string(generate_integer(r));  
    }

    problem = operand1_str;  // ��ʼ��Ŀ����
    result = operand1_str;  // ��ʼ�����Ϊ��һ��������

    for (int i = 0; i < operator_sum; ++i) {

        char op = generateOperator();

        // ������ɵڶ���������
        string operand2_str;
        if (isFractionProblem) {
            operand2_str = generate_fraction(r).toString(); 
        }
        else {
            operand2_str = to_string(generate_integer(r)); 
        }

        problem += " " + string(1, op) + " " + operand2_str;

        // ���㲿�ֽ��
        result = calculate(result, operand2_str, op);
    }
    problem += " =";
    return result; 
}

