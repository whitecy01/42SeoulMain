#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) :name("undefined"), grade(150)
{
	std::cout << this->name << " Constructor called\n";
}

Bureaucrat::Bureaucrat(std::string name, int grade) : name(name)
{
	if (grade < 1)
		throw GradeTooHighException();
	if (grade > 150)
		throw GradeTooLowException();
	this->grade = grade;
	std::cout << this->name << " Constructor called\n";
}

Bureaucrat::Bureaucrat(Bureaucrat const &bureaucrat) : name(bureaucrat.getName()), grade(bureaucrat.getGrade())
{
	std::cout << this->name <<  " copy Constructor called\n";
}

Bureaucrat& Bureaucrat::operator=(Bureaucrat const &bureaucrat)
{
	if (this == &bureaucrat)
		return (*this);
	this->grade = bureaucrat.getGrade();
	std::cout << this->name <<  " copy Constructor called\n";
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << this->name << " Destructor called\n";
}

void Bureaucrat::downGrade(void)
{
	if (this->grade >= 150)
		throw GradeTooLowException();
	this->grade++;
}

void Bureaucrat::upGrade(void)
{
	if (this->grade <= 1)
		throw GradeTooHighException();
	this->grade--;
}

void Bureaucrat::signForm(Form &form)
{
	try
	{
		form.beSigned(*this);
		std::cout << this->name << " signed " << form.getName() << "\n";
	}
	catch(bool sign)
	{
		std::cout << form.getName() << " was already signed\n";
	}
	catch(const std::exception& e)
	{
		std::cout << this->name << " couldn't sign " << form.getName();
		std::cout << " becuase " << e.what();
	}
	
}

const char  *Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return "Grade is too low\n";
}

const char  *Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return "Grade is too high\n";
}

std::string Bureaucrat::getName(void) const
{
	return (this->name);
}

int Bureaucrat::getGrade(void) const
{
	return (this->grade);
}


std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << "\n";
	return (out);
}

