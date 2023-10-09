#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"


int main(void) {

    try {
        Intern intern;
        AForm* scf = intern.makeForm("shrubbery creation", "42seoul");
        std::cout << *scf << "\n";
        delete scf;
        std::cout << "================ Shrubbery ================\n";

        AForm *rrfe = intern.makeForm("robotomy request", "42seoul");
        std::cout << *rrfe << "\n";
        delete rrfe;
        std::cout << "\n================ Robotomy ================\n";

        AForm *ppf = intern.makeForm("presidential pardon", "42seoul");
        std::cout << *ppf << "\n";
        delete ppf;
        std::cout << "\n================ Presidential ================\n";

        AForm *unknown = intern.makeForm("Unknown", "42seoul");
        std::cout << unknown << "\n";
        delete unknown;
        std::cout << "\n================ Unknown ================\n";

		{
			Intern someRandomIntern;
			AForm* rrf;

			rrf = someRandomIntern.makeForm("robotomy request" , "Bender");
			std::cout << *rrf << "\n";
			delete rrf;

		}
		 std::cout << "\n================ Main ================\n";

    } catch (const std::exception &e) {
        std::cout << e.what() << "\n";
    }
}