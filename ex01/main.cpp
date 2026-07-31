#include <iostream>
#include <stack>
#include <string>
#include <climits>

/*
    RPN: Reverse Polish Notation
    https://en.wikipedia.org/wiki/Reverse_Polish_notation

    INPUT: "8 9 * 9 - 9 - 9 - 4 - 1 +"
    Data: stack<int>
    LOGIC:
        1. Read the input string from left to right.
        2. If the token is a number, push it onto the stack.
        3. If the token is an operator, pop the top two numbers from the stack, apply the operator,
   and push the result back onto the stack.
        4. Repeat until all tokens are processed.
        5. The final result will be the only number left in the stack.
*/

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Error: wrong number of arguments" << std::endl;
        return (1);
    }

    std::string input = argv[1];
    size_t i = 0;

    std::stack<int> rpn_stack;
    while (i < input.length()) {
        if (std::isdigit(input[i])) {
            rpn_stack.push(input[i] - '0');
        } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            if (rpn_stack.size() < 2) {
                std::cerr << "Error: Not enough operands for operator: " << input[i] << std::endl;
                return (1);
            }
            int rh = rpn_stack.top();
            rpn_stack.pop();
            int lh = rpn_stack.top();
            rpn_stack.pop();
            int result;

            switch (input[i]) {
            case '+':
                if (lh < INT_MAX - rh)
                    result = lh + rh;
                else
                {
                    std::cerr << "Overflow: " << std::endl;
                    return (1);
                };
                break;
            case '-':
                if (lh < 0 && !(lh >= INT_MIN + rh))
                {
                    std::cerr << "Underflow: " << std::endl;
                    return (1);
                }
                result = lh - rh;
                break;
            case '*':
                if (lh > 0 && rh!=0 && !(lh <= INT_MAX/rh))
                {
                    std::cerr << "Overflow: " << std::endl;
                    return (1);
                }
                else if (lh < 0 && rh!=0 &&  !(lh >= INT_MIN/rh))
                {
                    std::cerr << "Underflow: " << std::endl;
                    return (1);
                }
                result = lh * rh;
                break;
            case '/':
                if (rh == 0) {
                    std::cerr << "Error: Division by zero" << std::endl;
                    return (1);
                }
                result = lh / rh;
                break;
            }
            rpn_stack.push(result);
        } else if (input[i] == ' ') {
            // ignore space
        } else {
            std::cerr << "Invalid character: " << input[i] << std::endl;
            return (1);
        }
        ++i;
    }
    if (rpn_stack.size() != 1) {
        std::cerr << "Error: Invalid expression" << std::endl;
        return (1);
    }
    std::cout << rpn_stack.top() << std::endl;
    return (0);
}
