#include "Bureaucrat.hpp"
#include "Form.hpp"
int main(void) {
    Bureaucrat jaeyojunA("jaeyojunA", 1);
    Bureaucrat jaeyojunB("jaeyojunB", 130);
    Form form("42seoul", 75, 150);
    std::cout << "====================================\n";
    try {
        std::cout << "[Before]\n" << form << "\n";
        jaeyojunA.signForm(form);
		jaeyojunA.signForm(form);
        std::cout << "[After]\n" << form << "\n";
    } catch (std::exception& e) {
        std::cout << e.what();
    }
    std::cout << "====================================\n";
    try {
        std::cout << "[Before]\n" << form << "\n";
        jaeyojunB.signForm(form);
        std::cout << "[After]\n" << form << "\n";
    } catch (std::exception& e) {
        std::cout << e.what();
    }
    std::cout << "====================================\n";
}