#include <iostream> 
#include <string> 


// sizeof register in 64bit architecture

template <typename T>
bool registerFit( T x){
   return sizeof( x ) <= sizeof( void* ) * 2 ;
}

const std::string& larger( const std::string& value )
{
  std::cout << value << std::endl ;
  return value ; 
}

int main (int argc, char *argv[]) {
  std::string value = "Hello world" ;
  const std::string& ( *ptrfunc )( const std::string& ) = &larger ; 
  (*ptrfunc)( value ) ; 
  return 0;
}
