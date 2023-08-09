#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>
class calculator
{
private:
    std::string infixExpression;
    std::string postfixExpression;
    std::stack<char> operations;
    std::stack<std::string> products;

    bool isNumber(char unknownCharacter);

    bool isSpace(char unknownCharacter);

    bool isOperator(char unknownCharacter);

    bool isOpenBracket(char unknownCharacter);

    bool isCloseBracket(char unknownCharacter);

    int getOperatorPriority(char Operator);

    bool hasPriority(char Operator1, char Operator2);

    double makeCalculation(std::string number1, std::string number2, char Operator);

public:
    calculator(std::string numericExpression);

    void ConvertToPostfix();

    double computeExpression();
};
