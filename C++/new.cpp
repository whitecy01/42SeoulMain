#include <iostream>

// class A
// {
//     private:
//         int a;
//     public:
//         A(int a) : a(a)
//         {

//         }
//         int getA()
//         {
//             return a;
//         }
// };

class A
{
    private:
        int a;
    public:
        A(int b) : a(b)
        {

        }
        int getA()
        {
            return a;
        }
};



int main()
{
    A *tmp = new A(2);
    std::cout << tmp->getA() << std::endl;
    delete tmp;
}