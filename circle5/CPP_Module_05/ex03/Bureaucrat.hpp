#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include "AForm.hpp"

class AForm;

class Bureaucrat{
private:
	const std::string name;
	int grade;
public:
	Bureaucrat(void);
	Bureaucrat(std::string name, int grade);
	Bureaucrat(Bureaucrat const &bureaucrat);
	Bureaucrat &operator=(Bureaucrat const &bureaucrat);
	~Bureaucrat(void);

	std::string getName(void) const;
	int getGrade(void) const;

	void upGrade(void);
	void downGrade(void);
	void signForm(AForm &form);
	void executeForm(AForm const & form);

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

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat);




# endif