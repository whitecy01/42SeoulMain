#include "RPN.hpp"

RPN::RPN()
{
	this->math_str = "";
}

RPN::~RPN()
{

}

RPN::RPN(RPN const &rpn)
{
	*this = rpn;
}

RPN& RPN::operator=(RPN const &rpn)
{
	if (this == &rpn)
		return *this;
	this->stack = rpn.stack;
	this->math_str = rpn.math_str;
	return *this;
}



RPN::RPN(const char *argv)
{
	this->math_str = argv;
}


int RPN::takePop()
{
	int num;
	num = this->stack.top();
	this->stack.pop();
	return num; 
}

int RPN::operand_calc(char op, int num1, int num2)
{
	switch (op)
	{
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

int RPN::checkValue(char math)
{
	if (isdigit(math))
        return number;
    else if (math == '-' || math == '+' || math == '/' || math == '*')
        return operand;
	else
		return -1;
	return -1;
}

int RPN::calcRpn()
{
	if (handleError(this->math_str))
		showMessage("Error");

	for (unsigned int i = 0; i < math_str.size(); i++)
	{
		if (math_str[i] == ' ')
            continue;
		switch (checkValue(math_str[i]))
		{
			case number:
				stack.push(math_str[i] - '0');
				break;
			case operand:
				if (stack.size() < 2)
					showMessage("Error: too less numbers");
				stack.push(operand_calc(math_str[i], takePop(), takePop()));
				break;
            default:
				std::cout << math_str[i] << std::endl;
                showMessage("Error: Wrong Arguments");
                break;
		}
	}
	if (stack.size() != 1)
        showMessage("Error: too less numbers");
	return stack.top();
}

int RPN::handleError(std::string math)
{
	int i;

	i = 0;
	while (math[i])
	{
		if (i >= 0 && i <= 2)
		{
			if (i == 0)
			{
				if (!(math[i] >= '0' && math[i] <= '9'))
					return true;
			}
			else if (i == 1)
			{
				if (math[i] != ' ')
					return true;
			}
			else if(i == 2)
			{
				if (!(math[i] >= '0' && math[i] <= '9'))
					return true;
			}
		}
		else
		{
			if(!(math[i] >= '0' && math[i] <= '9') && math[i] != ' ' &&
				(!(math[i] == '+' || math[i] == '/' || math[i] == '-' || math[i] == '*')))
				return true;
		}
		i++;
	}

	i = 3;
	int flag = 0;
	while (math[i])
	{
		if (math[i] >= '0' && math[i] <= '9')
		{
			if (flag == 1)
				showMessage("Error");
			flag = 1;
		}
		else if (math[i] == ' ' || math[i] == '+' || math[i] == '/' || math[i] == '-' || math[i] == '*')
			flag = 0;
		i++;
	}

	i = 0;
	int flag2 = 0;
	while (math[i])
	{
		if ((math[i] >= '0' && math[i] <= '9') || \
			math[i] == '+' || math[i] == '/' || math[i] == '-' || math[i] == '*')
		{
			if (flag2 == 1)
				showMessage("Error");
			flag2 = 1;
		}
		else if (math[i] == ' ')
			flag2 = 0;
		i++;
	}
	return false;
}

void RPN::showMessage(std::string message)
{
	std::cout << message << std::endl;
	std::exit(1);
}
