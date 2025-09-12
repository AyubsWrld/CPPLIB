#include <iostream> 
#include <filesystem> 


#ifndef IOSTREAM_H

int value = 3 ; 

#endif 


#ifdef IOSTREAM_H

int value = 4 ; 

#endif 


int main (int argc, char *argv[]) {
  std::cout << value << std::endl ; 
  return 0;
}
