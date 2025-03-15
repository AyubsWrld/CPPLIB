#include <iostream>
#include <bitset>

int main (int argc, char *argv[]) {
  std::bitset<8> bin = 0b0000'00101 ; 
  int x = ( int ) bin.to_ulong() ; 
  std::cout << x << std::endl ; 
  x >>= 1 ; 
  std::cout << x << std::endl ; 
  return 0;
}

