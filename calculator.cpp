#include "calculator.hpp"

// Empty constructor for get the infix Expression from user
calculator::calculator(std::string numericExpression) : infixExpression(numericExpression)
{
}

bool calculator::isNumber(char unknownCharacter)
{

    if ((unknownCharacter >= 48 && unknownCharacter <= 57) || unknownCharacter == '.')
        return true;
    else
        return false;
}

bool calculator::isSpace(char unknownCharacter)
{
    if (unknownCharacter == ' ')
        return true;
    else
        return false;
}

bool calculator::isOperator(char unknownCharacter)
{
    if (unknownCharacter == '+' || unknownCharacter == '-' || unknownCharacter == '*' || unknownCharacter == '/' || unknownCharacter == '^' || unknownCharacter == '%')
        return true;
    else
        return false;
}

bool calculator::isOpenBracket(char unknownCharacter)
{
    if (unknownCharacter == '(')
        return true;
    else
        return false;
}
bool calculator::isCloseBracket(char unknownCharacter)
{
    if (unknownCharacter == ')')
        return true;
    else
        return false;
}

int calculator::getOperatorPriority(char Operator)
{
    int Priority = 0;

    // a Look at the operator so we can determine how much its priority
    // The higher its priority, the greater the value of the Priority variable
    switch (Operator)
    {
    case '+':
    case '-':
        Priority = 1;
        break;
    case '*':
    case '/':
    case '%':
        Priority = 2;
        break;
    case '^':
        Priority = 3;
        break;
    }
    return Priority;
}

bool calculator::hasPriority(char Operator1, char Operator2)
{
    // Specifies whether the first Operator has priority or not
    return getOperatorPriority(Operator1) >= getOperatorPriority(Operator2);
}

double calculator::makeCalculation(std::string number1, std::string number2, char Operator)
{

    double product = 0;
    switch (Operator)
    {
    case '+':
        product = (std::stod(number2) + std::stod(number1)); // stod() The variable shifts from string to double
        break;
    case '-':
        product = (std::stod(number2) - std::stod(number1));
        break;
    case '*':
        product = (std::stod(number2) * std::stod(number1));
        break;
    case '/':
        // handling for the divide by 0 error
        try
        {
            if (std::stod(number1) == 0)
                throw std::runtime_error("Division operation encountered a zero divisor");

            product = (std::stod(number2) / std::stod(number1));
            break;
        }
        catch (std::runtime_error e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            std::exit(1);
        }
    case '^':
        product = std::pow(std::stod(number2), std::stod(number1));
        break;
    case '%':
        // handling for the divide by 0 error
        try
        {
            if (std::stod(number1) == 0)
                throw std::runtime_error("modulo operation encountered a zero divisor");

            product = (std::stoi(number2) % std::stoi(number1));
            break;
        }
        catch (std::runtime_error e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            std::exit(1);
        }
    }

    return product;
}

void calculator::ConvertToPostfix()
{
    // Delete spaces from the infix Expression
    infixExpression.erase(std::remove(infixExpression.begin(), infixExpression.end(), ' '), infixExpression.end());
    std::string::iterator strIt;
    for (strIt = infixExpression.begin(); strIt != infixExpression.end(); strIt++)
    {
        char currentValue = *strIt;
        // Figure compilation
        if (isNumber(currentValue))
        {
            postfixExpression += currentValue;

            // Peek ahead, if next character is part of previous number
            while (isNumber(*(strIt + 1)))
            {
                postfixExpression += *(strIt + 1);
                strIt++;
            }

            postfixExpression += ' '; // to separate each number
        }
        else if (isOperator(currentValue))
        {
            // Add the operator with the highest priority to the postfix Expression
            while (!operations.empty() && isOperator(operations.top()) && hasPriority(operations.top(), currentValue))
            {
                postfixExpression += operations.top();
                postfixExpression += ' ';
                operations.pop();
            }
            operations.push(currentValue);
        }
        else if (isOpenBracket(currentValue))
        {
            operations.push(currentValue);
        }
        else if (isCloseBracket(currentValue))
        {
            // call the remaining operators inside the brackets and add them to postfix Expression
            char activeItem = operations.top();
            operations.pop();
            while (!isOpenBracket(activeItem))
            {
                postfixExpression += activeItem;
                postfixExpression += ' ';
                activeItem = operations.top();
                operations.pop();
            }
        }
    }
    // Add the rest of the factors to the end of the postfix Expression If found
    while (!operations.empty())
    {
        char activeItem = operations.top();
        postfixExpression += activeItem;
        postfixExpression += ' ';
        operations.pop();
    }
}

double calculator::computeExpression()
{
    std::string::iterator strIt;
    for (strIt = postfixExpression.begin(); strIt != postfixExpression.end(); strIt++)
    {
        char currentValue = *(strIt);

        if (isSpace(currentValue))
            continue;

        else if (isNumber(currentValue))
        {
            std::string finalNumber;
            finalNumber += currentValue;
            while (isNumber(*(strIt + 1)))
            {
                finalNumber += *(strIt + 1);
                strIt++;
            }
            products.push(finalNumber); // put the numbers inside product stack
        }

        else if (isOperator(currentValue))
        {
            // call the first two numbers on top product stack
            std::string num1, num2;
            num1 = products.top();
            products.pop();
            num2 = products.top();
            products.pop();
            double result = makeCalculation(num1, num2, currentValue); // do the Operation
            // In the end it should be inside product stack final output only
            products.push(std::to_string(result));
        }
    }
    return std::stod(products.top());
}