#include <iostream>
#include <random>

int main (int argc, char *argv[]) 
{
  std::random_device gen{}; 
  std::uniform_int_distribution<> dv(1,10) ; 

  for (int i = 0; i < 10; i++) 
  {
    std::cout << "[" << i << "]: " ;
    for(int i{} ; i < dv(gen); i++)
    {
      std::cout << "*" ;
    }
    std::cout << std::endl; 
  }
  return 0;
}
