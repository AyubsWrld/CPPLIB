#include <iostream>
#include <type_traits>




// I dont intend on using R-values can js change this to R&

template<typename R>
void invokable( R&& r ) 
{
  std::cout << r << std::endl ; 
}

using type_erased_t = void (*)(void*) ; 


template<typename T>
void wrapper( void* ptr ) 
{
  T* x = static_cast<T*>(ptr) ; 
  invokable(std::move(*x)) ; 
}


template<typename... T>
void foo( T... x )
{
  ( ( std::cout << x << std::endl ) , ... ) ; 
}

template<typename... T>
void prints( T... x ) // by value
{
  foo( x++... )  ; 
}

void cb( int x , char y )
{
  std::cout <<  ( x < y ) << "\n" ; 
}

static type_erased_t cb_array[] = 
{
  &wrapper<int>
};

int main (int argc, char *argv[]) 
{
  prints( 1 , 2 , 3 , 4 ) ; 
  return 0; 
}
