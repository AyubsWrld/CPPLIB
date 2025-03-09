#include <iostream> 

int main() { 

  short x = 4 ; 
  short* ptr_to_short = &x ; 
  unsigned short y = 4  ; 
  size_t sizeof_ptr_to_short = sizeof(short)  ; 
  size_t pow = ( sizeof_ptr_to_short  * 32768 ) - 1 ;  // Assume this equals 65535 
  y = y + pow ; 

  std::cout << y << std::endl;
  return 0 ; 
}
