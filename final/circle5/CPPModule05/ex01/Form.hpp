#ifndef FORM_HPP
# define FORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class Form{
private:
	const std::string name;
	bool sign;
	const int signGrade;
	const int execGrade;
public:
	Form(void);
	Form(std::string name, int signGrade, int execGrade);
	Form(Form const &form);
	Form &operator=(Form const &form);
	~Form(void);

	std::string getName(void) const;
	bool getSign(void) const;
	int	getSignGrade(void) const;
	int getExecGrade(void) const;
	void setSign(bool sign);
	void beSigned(Bureaucrat const &person);

	class GradeTooLowException : public std::exception
	{
		public:
			const char *what(void) const throw();
	};
	class GradeTooHighException : public std::exception
	{
		public:
			const char *what(void) const throw();
	};
};

std::ostream &operator<<(std::ostream &out, const Form &form);

# endif