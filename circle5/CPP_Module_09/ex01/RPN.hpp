#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <cstdlib>

#define number 1
#define operand 2

class RPN 
{
	private: 
		std::stack<int> stack;
		std::string math_str;
	public:
		RPN();
		RPN(const char *argv);
		~RPN();
		RPN&operator=(RPN const &rpn);
		RPN(RPN const &rpn);


		int checkValue(char math);
		int operand_calc(char op, int num1, int num2);
		int takePop();
		int handleError(std::string math);
		int calcRpn(void);
		void showMessage(std::string message);
};

#endif