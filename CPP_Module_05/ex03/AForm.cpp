#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(void) :name("undefined"), sign(false), signGrade(150), execGrade(150)
{
	std::cout << this->name << " Constructor called\n";
}

AForm::AForm(std::string name, int signGrade, int execGrade) : name(name), sign(false), signGrade(signGrade), execGrade(execGrade)
{
	if (signGrade < 1 || execGrade < 1)
		throw GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw GradeTooLowException();
	std::cout << this->name << " Constructor called\n";
}

AForm::AForm(AForm const &form) : name(form.getName()), sign(form.getSign()), signGrade(form.getSignGrade()), execGrade(form.getExecGrade())
{
	std::cout << this->name <<  " copy Constructor called\n";
}

AForm& AForm::operator=(AForm const &form)
{
	if (this == &form)
		return (*this);
	this->sign = form.getSign();
	std::cout << this->name <<  " copy Constructor called\n";
	return (*this);
}

AForm::~AForm()
{
	std::cout << this->name << " Destructor called\n";
}

std::string AForm::getName(void) const
{
	return (this->name);
}

bool AForm::getSign(void) const
{
	return (this->sign);
}

int AForm::getSignGrade(void) const
{
	return (this->signGrade);
}

int AForm::getExecGrade(void) const
{
	return (this->execGrade);
}

void AForm::setSign(bool sign)
{
	this->sign = sign;
}

void AForm::beSigned(Bureaucrat const &person)
{
	if (person.getGrade() >= this->signGrade)
	{
		throw GradeTooLowException();
	}
	else if (sign)
	{
		throw sign;
	}
	else
	{
		sign = true;
	}
}

void AForm::checkExecuteGrade(Bureaucrat const &executor) const
{
	if (!this->getSign())
	{
		throw NotSignedException();
	}
	if (executor.getGrade() >= this->getExecGrade())
	{
		throw ExecuteDeninedException();
	}
}

const char  *AForm::GradeTooLowException::what(void) const throw()
{
	return "Grade is too low\n";
}

const char  *AForm::GradeTooHighException::what(void) const throw()
{
	return "Grade is too high\n";
}

const char  *AForm::NotSignedException::what(void) const throw()
{
	return "AForm is not signed\n";
}

const char  *AForm::ExecuteDeninedException::what(void) const throw()
{
	return "Executable Access Denined";
}

const char  *AForm::FileException::what(void) const throw()
{
	return "File error";
}


std::ostream &operator<<(std::ostream &out, const AForm &form)
{
	out << "AForm : " << form.getName() << "\nSign : " << form.getSign() << "\nSignGrade : " << form.getSignGrade() << "\nExecgrade : " << form.getExecGrade() << "\n";
	return (out);
}

