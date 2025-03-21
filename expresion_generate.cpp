#include "generation.h"

//随机生成一个 [1,n]的数
int generate_integer(int n) {
    if (n < 0) {
        return 0;
    }
    return rand() % n + 1;
}

//随机生成一个分数，分子范围是[1, n]，分母范围是[1, n]
Fraction generate_fraction (int n) {

    int numerator = rand() % n + 1;
    int denominator = rand() % n + 1;
    return Fraction(0, numerator, denominator);
}

//是否生成分数
bool ifgenerateFraction() {
    return rand() % 2;
}

//随机选择一个运算符
char generateOperator() {
    int option = rand() % 4;  // 生成0-3之间的随机数
    switch (option) {
    case 0: return '+';
    case 1: return '-';
    case 2: return '*';
    case 3: return '+';
    }
}


// 判断字符是否是操作符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 获取操作符的优先级
int getOperatorPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// 将中缀表达式转换为后缀表达式
vector<string> infixToPostfix(const string& expression) {
    std::stack<char> operators;
    std::vector<std::string> postfix;
    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (isdigit(token[0]) || token.find('/') != std::string::npos) {
            // 操作数（整数或分数）
            postfix.push_back(token);
        }
        else if (isOperator(token[0])) {
            // 运算符
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

    // 将剩余的运算符添加到后缀表达式
    while (!operators.empty()) {
        postfix.push_back(std::string(1, operators.top()));
        operators.pop();
    }

    return postfix;
}

// 计算后缀表达式的值
//Fraction evaluatePostfix(const vector<string>& postfix) {
//    std::stack<Fraction> stack;
//
//    for (const auto& token : postfix) {
//        if (isdigit(token[0]) || token.find('/') != string::npos) {
//            // 操作数
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
//            // 运算符
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
            // 操作数，处理整数或分数（包括带整数部分的分数，如 3'2/3）

            int num = 0;
            int den = 1;

            if (token.find("'") != string::npos) {
                // 处理带整数部分的分数，例如 3'2/3
                size_t pos = token.find("'");
                int integerPart = std::stoi(token.substr(0, pos)); // 整数部分
                string fracPart = token.substr(pos + 1);

                // 分数部分
                size_t slashPos = fracPart.find('/');
                if (slashPos != string::npos) {
                    num = std::stoi(fracPart.substr(0, slashPos));
                    den = std::stoi(fracPart.substr(slashPos + 1));
                    // 将整数部分加到分子上
                    num += integerPart * den;
                }
                else {
                    num = integerPart * den + std::stoi(fracPart);
                }
            }
            //else if (token.find('/') != string::npos) {
            //    // 处理标准分数
            //    size_t pos = token.find('/');
            //    num = std::stoi(token.substr(0, pos));
            //    den = std::stoi(token.substr(pos + 1));
            //}
            else if (token.find('/') != string::npos) {
                // 处理标准分数
                
                size_t pos = token.find('/');
                try {
                    // 确保分子和分母部分都是有效的数字
                    string numStr = token.substr(0, pos);
                    string denStr = token.substr(pos + 1);

                    // 只在分子和分母都有效的情况下调用 stoi
                    if (numStr.empty() || denStr.empty()) {
                        throw std::invalid_argument("Invalid fraction format: " + token);
                    }

                    num = std::stoi(numStr);
                    den = std::stoi(denStr);

                    // 检查分母是否为零
                    if (den == 0) {
                        throw std::invalid_argument("Denominator cannot be zero.");
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid fraction format: " << token << ". Error: " << e.what() << std::endl;
                    throw;  // 重新抛出异常
                }
            }
            else {
                // 处理整数
                num = stoi(token);
            }

            // 创建分数并推入栈中
            if (den == 0) {
                throw std::invalid_argument("Denominator cannot be zero.");
            }
            stack.push(Fraction(num, den));
        }
        else if (isOperator(token[0])) {
            // 运算符
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


//将中缀表达式转换为后缀，再计算值。
Fraction calculate(const string& expression) {
    auto postfix = infixToPostfix(expression);
    return evaluatePostfix(postfix);
}

Fraction generate_fraction_with_max(int range, const Fraction& max_value) {
    int count = 0;
    while (true) {
        
        int den = max_value.denominator + 2; // 分母
        int num = max_value.numerator ; // 分子
        Fraction frac(0,num, den);
        Fraction temp = max_value - frac;
        if (temp.numerator > 0 || temp.integer > 0) {
            return frac;
        }
        count++;
        if (count >= 10) return frac;

    }
}

// 将字符串解析为分数
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

    string result;  // 存储计算结果
    int operator_sum = (rand() % 3) + 1; // 运算符个数（1-3）
    bool isFractionProblem = ifgenerateFraction();  // 判断是否为分数题
    string operand1_str;

    if (isFractionProblem) {
        operand1_str = generate_fraction(r).toString(); // 1 生成初始分数
    }
    else {
        operand1_str = to_string(generate_integer(r)); // 0 生成初始整数
    }

    problem = operand1_str;
    result = operand1_str;

    for (int i = 0; i < operator_sum; ++i) {
        char op = generateOperator(); // 随机生成运算符
        Fraction current_value = parseResult(result); // 解析当前结果为Fraction

        // 生成第二个操作数
        string operand2_str;
        if (op == '-') {
            if (isFractionProblem) {
                // 生成不超过current_value且分母不超过r的分数
                Fraction operand2 = generate_fraction_with_max(r, current_value);
                operand2_str = operand2.toString();
            }
            else {
                // 生成不超过current_value的整数
                int max_op = current_value.integer - 1;
                if (max_op <= 0) {
                    // 如果最大操作数为零或负数，设置为 1
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

        // 计算新的结果
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


