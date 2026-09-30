#ifndef SHRUBBERYCRETIONFORM_HPP
# define SHRUBBERYCRETIONFORM_HPP

#include <fstream>
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"


class ShrubberyCreationForm : public AForm
{
private:
	std::string target;
public:
	ShrubberyCreationForm(void);
	ShrubberyCreationForm(std::string target);
	ShrubberyCreationForm(ShrubberyCreationForm const &shrubberyCreationForm);
	ShrubberyCreationForm &operator=(ShrubberyCreationForm const &shrubberyCreationForm);
	~ShrubberyCreationForm(void);

	std::string getTarget(void) const;

	void execute(Bureaucrat const &executor) const;
};




# endif