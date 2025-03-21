#include "generation.h"

//�������һ�� [1,n]����
int generate_integer(int n) {
    if (n < 0) {
        return 0;
    }
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
    case 3: return '+';
    }
}


// �ж��ַ��Ƿ��ǲ�����
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// ��ȡ�����������ȼ�
int getOperatorPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// ����׺���ʽת��Ϊ��׺���ʽ
vector<string> infixToPostfix(const string& expression) {
    std::stack<char> operators;
    std::vector<std::string> postfix;
    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (isdigit(token[0]) || token.find('/') != std::string::npos) {
            // �������������������
            postfix.push_back(token);
        }
        else if (isOperator(token[0])) {
            // �����
            while (!operators.empty() && getOperatorPrecedence(operators.top()) >= getOperatorPrecedence(token[0])) {
                postfix.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(token[0]);
        }
        else {
            cout<< "Invalid character in expression.";
        }
    }

    // ��ʣ����������ӵ���׺���ʽ
    while (!operators.empty()) {
        postfix.push_back(std::string(1, operators.top()));
        operators.pop();
    }

    return postfix;
}

// �����׺���ʽ��ֵ
//Fraction evaluatePostfix(const vector<string>& postfix) {
//    std::stack<Fraction> stack;
//
//    for (const auto& token : postfix) {
//        if (isdigit(token[0]) || token.find('/') != string::npos) {
//            // ������
//            int num = 0;
//            int den = 1;
//            if (token.find('/') != string::npos) {
//                size_t pos = token.find('/');
//                num = stoi(token.substr(0, pos));
//                den = stoi(token.substr(pos + 1));
//            }
//            else {
//                num = std::stoi(token);
//            }
//            stack.push(Fraction(num, den));
//        }
//        else if (isOperator(token[0])) {
//            // �����
//            if (stack.size() < 2) {
//                throw std::runtime_error("Insufficient operands for operation");
//            }
//            Fraction b = stack.top();
//            stack.pop();
//            Fraction a = stack.top();
//            stack.pop();
//
//            Fraction result(0, 1);
//            switch (token[0]) {
//            case '+':
//                result = a + b;
//                break;
//            case '-':
//                result = a - b;
//                break;
//            case '*':
//                result = a * b;
//                break;
//            case '/':
//                result = a / b;
//                break;
//            }
//            stack.push(result);
//        }
//    }
//
//    if (stack.size() != 1) {
//        return stack.top();
//    }
//
//    return stack.top();
//}
Fraction evaluatePostfix(const vector<string>& postfix) {
    std::stack<Fraction> stack;

    for (const auto& token : postfix) {
        if (isdigit(token[0]) || token.find('/') != string::npos || token.find("'") != string::npos) {
            // ������������������������������������ֵķ������� 3'2/3��

            int num = 0;
            int den = 1;

            if (token.find("'") != string::npos) {
                // ������������ֵķ��������� 3'2/3
                size_t pos = token.find("'");
                int integerPart = std::stoi(token.substr(0, pos)); // ��������
                string fracPart = token.substr(pos + 1);

                // ��������
                size_t slashPos = fracPart.find('/');
                if (slashPos != string::npos) {
                    num = std::stoi(fracPart.substr(0, slashPos));
                    den = std::stoi(fracPart.substr(slashPos + 1));
                    // ���������ּӵ�������
                    num += integerPart * den;
                }
                else {
                    num = integerPart * den + std::stoi(fracPart);
                }
            }
            //else if (token.find('/') != string::npos) {
            //    // �����׼����
            //    size_t pos = token.find('/');
            //    num = std::stoi(token.substr(0, pos));
            //    den = std::stoi(token.substr(pos + 1));
            //}
            else if (token.find('/') != string::npos) {
                // �����׼����
                
                size_t pos = token.find('/');
                try {
                    // ȷ�����Ӻͷ�ĸ���ֶ�����Ч������
                    string numStr = token.substr(0, pos);
                    string denStr = token.substr(pos + 1);

                    // ֻ�ڷ��Ӻͷ�ĸ����Ч������µ��� stoi
                    if (numStr.empty() || denStr.empty()) {
                        throw std::invalid_argument("Invalid fraction format: " + token);
                    }

                    num = std::stoi(numStr);
                    den = std::stoi(denStr);

                    // ����ĸ�Ƿ�Ϊ��
                    if (den == 0) {
                        throw std::invalid_argument("Denominator cannot be zero.");
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid fraction format: " << token << ". Error: " << e.what() << std::endl;
                    throw;  // �����׳��쳣
                }
            }
            else {
                // ��������
                num = stoi(token);
            }

            // ��������������ջ��
            if (den == 0) {
                throw std::invalid_argument("Denominator cannot be zero.");
            }
            stack.push(Fraction(num, den));
        }
        else if (isOperator(token[0])) {
            // �����
            if (stack.size() < 2) {
                throw std::runtime_error("Insufficient operands for operation");
            }
            Fraction b = stack.top();
            stack.pop();
            Fraction a = stack.top();
            stack.pop();

            Fraction result(0, 1);
            switch (token[0]) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = a / b;
                break;
            }
            stack.push(result);
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression.");
    }

    return stack.top();
}


//����׺���ʽת��Ϊ��׺���ټ���ֵ��
Fraction calculate(const string& expression) {
    auto postfix = infixToPostfix(expression);
    return evaluatePostfix(postfix);
}

Fraction generate_fraction_with_max(int range, const Fraction& max_value) {
    int count = 0;
    while (true) {
        
        int den = max_value.denominator + 2; // ��ĸ
        int num = max_value.numerator ; // ����
        Fraction frac(0,num, den);
        Fraction temp = max_value - frac;
        if (temp.numerator > 0 || temp.integer > 0) {
            return frac;
        }
        count++;
        if (count >= 10) return frac;

    }
}

// ���ַ�������Ϊ����
Fraction parseResult(const std::string& result_str) {
    if (result_str.find('/') != std::string::npos) {
        size_t slash_pos = result_str.find('/');
        int num = std::stoi(result_str.substr(0, slash_pos));
        int den = std::stoi(result_str.substr(slash_pos + 1));
        return Fraction(num, den);
    }
    else {
        return Fraction(std::stoi(result_str), 1);
    }
}

string generate_Problem(string& problem, int r) {

    string result;  // �洢������
    int operator_sum = (rand() % 3) + 1; // �����������1-3��
    bool isFractionProblem = ifgenerateFraction();  // �ж��Ƿ�Ϊ������
    string operand1_str;

    if (isFractionProblem) {
        operand1_str = generate_fraction(r).toString(); // 1 ���ɳ�ʼ����
    }
    else {
        operand1_str = to_string(generate_integer(r)); // 0 ���ɳ�ʼ����
    }

    problem = operand1_str;
    result = operand1_str;

    for (int i = 0; i < operator_sum; ++i) {
        char op = generateOperator(); // ������������
        Fraction current_value = parseResult(result); // ������ǰ���ΪFraction

        // ���ɵڶ���������
        string operand2_str;
        if (op == '-') {
            if (isFractionProblem) {
                // ���ɲ�����current_value�ҷ�ĸ������r�ķ���
                Fraction operand2 = generate_fraction_with_max(r, current_value);
                operand2_str = operand2.toString();
            }
            else {
                // ���ɲ�����current_value������
                int max_op = current_value.integer - 1;
                if (max_op <= 0) {
                    // �����������Ϊ�����������Ϊ 1
                    max_op = 1;
                }
                int operand2_int = generate_integer(max_op);
                operand2_str = to_string(operand2_int);
            }
        }
        else {
            if (isFractionProblem) {
                operand2_str = generate_fraction(r).toString();
            }
            else {
                operand2_str = to_string(generate_integer(r));
            }
        }

        problem += " " + std::string(1, op) + " " + operand2_str;

        // �����µĽ��
        Fraction operand2 = parseResult(operand2_str);
        Fraction new_result;
        switch (op) {
        case '+': new_result = current_value + operand2; break;
        case '-': new_result = current_value - operand2; break;
        case '*': new_result = current_value * operand2; break;
        case '/':
            if (operand2.integer == 0 && operand2.numerator == 0) {
                cout << "division by zero.";
            }
            new_result = current_value / operand2;
            break;
        }
        result = new_result.toString();
    }
    return result;
}


