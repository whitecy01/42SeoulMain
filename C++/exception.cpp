#include <iostream>
#include <string>
#include <exception>

int main()
{
   try
   {
       std::string s;
       s.resize(-1);  // 예외 발생
   }
   catch (const std::exception & e)
   {
       std::cout << typeid(e).name() << std::endl;
       std::cerr << e.what() << std::endl;
   }

   return 0;
}