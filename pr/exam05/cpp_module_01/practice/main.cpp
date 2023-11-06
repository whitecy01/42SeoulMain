#include "Warlock.hpp"
#include "Fwoosh.hpp"
#include "Dummy.hpp"

void check()
{
    system("leaks a.out");
}


int main()
{
  Warlock richard("Richard", "the Titled");

  Dummy bob;
  Fwoosh* fwoosh = new Fwoosh();

  richard.learnSpell(fwoosh);

  richard.introduce();
  richard.launchSpell("Fwoosh", bob);

  richard.forgetSpell("Fwoosh");
  richard.launchSpell("Fwoosh", bob);
  delete fwoosh;
    atexit(check);
}