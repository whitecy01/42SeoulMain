#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void) {
    Bureaucrat king("king", 1);
    Bureaucrat jaeyojun("jaeyojun", 150);
	ShrubberyCreationForm form("hello");

	king.signForm(form);
	jaeyojun.executeForm(form);
    std::cout << "[King] : " << king << "\n";
    std::cout << "[jaeyojun] : " << jaeyojun << "\n";

    std::cout << "============= Shrubbery ============\n";
    ShrubberyCreationForm form1("home");
    std::cout << "[Form]\n" << form1 << "\n";
    king.signForm(form1);
    king.executeForm(form1);
    jaeyojun.signForm(form1);
    jaeyojun.executeForm(form1);
    std::cout << "\n\n";

    std::cout << "============= Robotomy ============\n";
    RobotomyRequestForm form2("home");
    std::cout << "[Form]\n" << form2 << "\n";
    king.signForm(form2);
    jaeyojun.signForm(form2);
    king.executeForm(form2);
    jaeyojun.executeForm(form2);
    std::cout << "\n\n";

    std::cout << "============= Presidential ============\n";
    PresidentialPardonForm form3("home");
    std::cout << "[Form]\n" << form3 << "\n";
    king.signForm(form3);
    jaeyojun.signForm(form3);
    king.executeForm(form3);
    jaeyojun.executeForm(form3);
    std::cout << "\n\n";
}