#include <bitset>
#include <initializer_list>
#include <iostream>
#include <string.h>
#include <vector>
#include <type_traits>



template < typename T > 
struct vector{
  T size ; 
};

int main (int argc, char *argv[]) 
{
  vector<int> num ;
  num.size = 3 ; 
  return 0;
}
