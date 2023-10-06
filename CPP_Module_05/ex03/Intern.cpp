#include "Intern.hpp"

Intern::Intern(void)
{
	std::cout << "Intern Constructor called\n";
}

Intern::~Intern(void)
{
	std::cout <<  "Intern Destructor called\n";
}

Intern::Intern(Intern const &intern)
{
	(void) intern;
	std::cout <<  "Intern copy Constructor called\n";
}

Intern& Intern::operator=(Intern const &intern)
{
	if (this == &intern)
		return (*this);
	std::cout <<  "Intern copy Constructor called\n";
	return (*this);
}

const char *Intern::FormNotExistException::what(void) const throw()
{
	return "AForm doesn't exist";
}

AForm *Intern::createShrubbery(const std::string &target)
{
	return new ShrubberyCreationForm(target);
}

AForm *Intern::createRobotomy(const std::string &target)
{
	return new RobotomyRequestForm(target);
}

AForm *Intern::createPresidentia(const std::string &target)
{
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(const std::string &form, const std::string &target)
{
	const std::string formName[3] = {"shrubbery creation", "robotomy request", "presidential pardon"}; 
	AForm *(Intern::*writeForm[3])(const std::string &) = {
		&Intern::createShrubbery, &Intern::createRobotomy, &Intern::createPresidentia};
	AForm *result = NULL;

	try
	{
		for(int i = 0; i < 3; i++)
		{
			if (formName[i] == form)
			{
				result = (this->*writeForm[i])(target);
				std::cout << "Intern creates " << result->getName() << "\n";
				return (result);
			}
		}
		throw Intern::FormNotExistException();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (NULL);
}
