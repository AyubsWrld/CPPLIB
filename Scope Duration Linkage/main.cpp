#include <iostream> 
#include <string> 

int main (int argc, char *argv[]) {
  int x  , y ; 
  std::cout << "Please enter an integer: " ;
  std::cin >> x ; 
  std::cout << "Please enter another integer: " ;
  std::cin >> y ; 
  std::cout << "Swapping the variables" << std::endl ;
  {
    int y = x ;
    int x = y ;
    std::cout << x << " "  << y << std::endl ;
  }
  std::cout << x << " "  << y << std::endl ;
  return 0;
}
