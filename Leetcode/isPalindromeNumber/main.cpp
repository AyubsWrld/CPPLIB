#include <iostream>
#include <string>


bool isPalindrome(const int& x ) { 
  std::string normal = std::to_string(x) ; 
  std::string::iterator begin = normal.begin() ; 
  std::string::iterator end =  --( normal.end()) ; 

  int j = 0 ; 
  while( *end ) { 
    if ( *end != *begin ) {
      return false ; 
    }
    begin++ ; 
    end -- ; 
  }
  return true ;
}


int main(){
  std::cout 
  return 0 ; 
}
