#include <iostream>

template<typename... Args>
bool all( Args... args ){
  return ( ... && args ) ;
}


/*template<typename... Args>*/
/*void shift_mem(){*/
/*}*/





// Replace lambda here for logic for reading in array and shifting chunk ; 
template<typename... T>
void shift_mem( T... x) 
{
  (( [] { std::cout << sizeof(T) << " " ; }() ) , ... )  ; 
}

int main (int argc, char *argv[]) 
{
  /*shift_mem<int,bool,bool>() ; */


  shift_mem( 1  , 'a' , 3ul ) ; 
  return 0;
}
