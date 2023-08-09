
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include "calculator.cpp"
int main()
{

    std::string Calculation;
    std::cout << "Enter the Calculation : ";
    std::cin >> Calculation;
    calculator myProcessor(Calculation);
    myProcessor.ConvertToPostfix();
    std::cout << myProcessor.computeExpression() << std::endl;
    return 0;
}
