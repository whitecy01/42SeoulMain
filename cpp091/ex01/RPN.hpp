#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <queue>
# include <iostream>

# define OPERATOR 0
# define DIGIT 1
# define FAIL -1

class RPN
{
private:
    std::stack<int> stack;
    std::string notation;
public:
    RPN(void);
    RPN(const char *data);
    RPN(RPN const &rpn);
    ~RPN(void);
    RPN& operator=(RPN const &rpn);

    int takeTop(void);
    int calcRpn(void);
    int calcNum(char op, int num1, int num2);
    int checkChar(char ch);
    void handleError(std::string message);
};

#endif
