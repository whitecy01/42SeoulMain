#ifndef ROBOTOMYREQUESTFROM_HPP
# define  ROBOTOMYREQUESTFROM_HPP


#include "AForm.hpp"
#include <cstdlib>

class RobotomyRequestForm : public AForm
{
private:
	std::string target;
public:
	RobotomyRequestForm(void);
	RobotomyRequestForm(const std::string target);
	RobotomyRequestForm(RobotomyRequestForm const &robotomyRequestForm);
	~RobotomyRequestForm(void);
	RobotomyRequestForm &operator=(RobotomyRequestForm const &robotomyRequestForm);

	std::string getTarget(void) const;
	void execute(Bureaucrat const &executor) const;

};

#endif