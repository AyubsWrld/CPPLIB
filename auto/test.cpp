#include <iostream>


int main()
{
  const char* greeting = "Hello there" ; 

  char v[6] ; 
  memcpy( &v , &greeting[6] , sizeof(v)); 
  std::cout << v << std::endl ; 
  return 0;
}
