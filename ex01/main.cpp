#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

/*
    RPN: Reverse Polish Notation
    https://en.wikipedia.org/wiki/Reverse_Polish_notation

    INPUT: "8 9 * 9 - 9 - 9 - 4 - 1 +"
    Data: stack<int>
    LOGIC:
        1. Read the input string from left to right.
        2. If the token is a number, push it onto the stack.
        3. If the token is an operator, pop the top two numbers from the stack, apply the operator, and push the result back onto the stack.
        4. Repeat until all tokens are processed.
        5. The final result will be the only number left in the stack.
*/


int main(int argc, char *argv[])
{
    if (argc != 2)
        return (1);

    std::string input = argv[1];
    size_t i = 0;

    std::stack<int> rpn_stack;
    while (i<input.length())
    {
        if (std::isdigit(input[i]))
        {
            std::cout << "number: " << input[i] << std::endl;
            rpn_stack.push(input[i]-'0'); // convert char to int
        }
        else if (input[i]=='+' || input[i]=='-' || input[i]=='*' || input[i]=='/')
        {
            std::cout << "operator: " << input[i] << std::endl;
            if (rpn_stack.size()<2)
            {
                std::cout << "Error: Not enough operands for operator: " << input[i] << std::endl;
                return (1);
            }
            int rh = rpn_stack.top();
            rpn_stack.pop();
            int lh = rpn_stack.top();
            rpn_stack.pop();
            int result;
            switch (input[i])
            {
                case '+':
                    result = lh + rh;
                    break;
                case '-':
                    result = lh - rh;
                    break;
                case '*':
                    result = lh * rh;
                    break;
                case '/':
                    if (rh == 0)
                    {
                        std::cout << "Error: Division by zero" << std::endl;
                        return (1);
                    }
                    result = lh / rh;
                    break;
            }
            rpn_stack.push(result);
        }
        else if (input[i]==' ')
        {
            // ignore space
        }
        else
        {
            std::cout << "Invalid character: " << input[i] << std::endl;
            return (1);
        }
        ++i;
    }
    if (rpn_stack.size() != 1)
    {
        std::cout << "Error: Invalid expression" << std::endl;
        return (1);
    }
    std::cout << "Result: " << rpn_stack.top() << std::endl;
    return(0);
}
