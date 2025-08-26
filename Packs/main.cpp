#include <iostream>
#include <type_traits>
#include <algorithm>


template<typename T>
size_t getSize( T x ) 
{
  return sizeof(x)  ; 
}

template<typename... T>
size_t getMax( T... u) 
{
  return std::max( { getSize(u)... }) ; 
}


int main (int argc, char *argv[]) {
  
  return 0;
}
