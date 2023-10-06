#ifndef INTERN_HPP
# define INTERN_HPP

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern 
{
private:
public:

	Intern(void);
	Intern(Intern const &intern);
	Intern &operator=(Intern const &intern);
	~Intern(void);


	AForm *createShrubbery(const std::string &target);
	AForm *createRobotomy(const std::string &target);
	AForm *createPresidentia(const std::string &target);

	AForm *makeForm(const std::string &form, const std::string &target);

	class FormNotExistException : public std::exception
	{
		const char *what() const throw();
	};
};
#endif