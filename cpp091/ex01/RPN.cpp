# include "RPN.hpp"

RPN::RPN(void) { }

RPN::RPN(const char *data) {
    this->notation = data;
}

RPN::RPN(RPN const &rpn) {
    this->stack = rpn.stack;
    this->notation = rpn.notation;
}

RPN::~RPN(void) { }

RPN& RPN::operator=(RPN const &rpn) {
    if (this != &rpn) {
        this->stack = rpn.stack;
        this->notation = rpn.notation;
    }
    return (*this);
}

int RPN::takeTop(void) {
    int num = stack.top();
    stack.pop();
    return num;
}

int RPN::calcRpn(void) {
    char ch;

    for (size_t i = 0; i < this->notation.size(); i++) {
        ch = this->notation[i];
        if (ch == ' ')
            continue;
        switch (checkChar(ch)) {
            case OPERATOR:
                if (stack.size() < 2)
                    handleError("Error: too less numbers");
                stack.push(calcNum(ch, takeTop(), takeTop()));
                break;
            case DIGIT:
                stack.push(ch - '0');
                break;
            default:
                handleError("Error: Wrong Arguments");
                break;
        }
    }
    if (stack.size() != 1)
        handleError("Error: Not Enough Operator");
    return stack.top();
}

int RPN::calcNum(char op, int num1, int num2) {
    switch (op) {
        case '+':
            return num2 + num1;
        case '-':
            return num2 - num1;
        case '/':
            if (num1 == 0)
                handleError("Error: Zero Division");
            return num2 / num1;
        default:
            return num2 * num1;
    }        
}

int RPN::checkChar(char ch) {
    if (isdigit(ch))
        return 1;
    else if (ch == '-' || ch == '+' || ch == '/' || ch == '*')
        return 0;
    else
        return -1;
}

void RPN::handleError(std::string message) {
    std::cerr << message << "\n";
    std::exit(1);
}