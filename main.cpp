#include "generation.h"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Usage:Myapp.exe -n <number_of_problems> -r <range_of_numbers>" << endl;
        return 1;  // 参数不正确时，退出程序
    }
    srand(time(0));
    int numProblems = 0, range = 0;
    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-n") {
            numProblems = atoi(argv[++i]);
        }
        else if (string(argv[i]) == "-r") {
            range = atoi(argv[++i]);
        }
    }
    if (numProblems <= 0 || range <= 0) {
        cout << "Invalid arguments! Please provide valid -n and -r values." << endl;
        return 1;
    }

    ofstream exercisesFile("Exercises.txt");
    ofstream answersFile("Answers.txt");
    if (!exercisesFile || !answersFile) {
        cout << "Error opening files!" << endl;
        return 1;
    }

    string problem;
    string result;
    for (int i = 1; i <= numProblems; i++) {
        generate_Problem(problem, range);  // 生成题目
        auto postfix = infixToPostfix(problem);
        result = evaluatePostfix(postfix).toString();     // 计算答案

        // 写入题目到Exercises.txt
        exercisesFile << i << ". " << problem << " = " << endl;

        // 写入答案到Answers.txt
        answersFile << i << ". " << result << endl;
    }

    // 关闭文件
    exercisesFile.close();
    answersFile.close();
    return 0;

}