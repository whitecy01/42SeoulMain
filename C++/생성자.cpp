

#include <iostream>

class Contact{
    public:
        Contact();
        Contact(int re);
        int x;
        int plus();
};

Contact::Contact(){
    x = 1;
    std::cout << "출력 : " << x << std::endl;
}

Contact::Contact(int re){
    x = re;
    std::cout << "출력2 : " << x << std::endl;
}

int Contact::plus(){
    return x + x;
}

int main(void)
{
    Contact s1;
    int ss = s1.plus();
    std::cout << "ss결과" << ss << std::endl;

    Contact s2(2);
    int sa = s2.plus();
    std::cout << "sa결과" << sa << std::endl;



}