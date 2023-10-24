#ifndef AFORM_HPP
# define AFORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm{
private:
	const std::string name;
	bool sign;
	const int signGrade;
	const int execGrade;
public:
	AForm(void);
	AForm(std::string name, int signGrade, int execGrade);
	AForm(AForm const &form);
	AForm &operator=(AForm const &form);
	virtual ~AForm(void);

	std::string getName(void) const;
	bool getSign(void) const;
	int	getSignGrade(void) const;
	int getExecGrade(void) const;

	void setSign(bool sign);

	void beSigned(Bureaucrat const &person);
	virtual void execute(Bureaucrat const &executor) const = 0;
	void checkExecuteGrade(Bureaucrat const &executor) const;


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
	class NotSignedException : public std::exception
	{
		public:
			const char *what(void) const throw();
	};
	class ExecuteDeninedException : public std::exception
	{
		public:
			const char *what(void) const throw();
	};
	class FileException : public std::exception
	{
		public:
			const char *what(void) const throw();
	};
};

std::ostream &operator<<(std::ostream &out, const AForm &form);

# endif