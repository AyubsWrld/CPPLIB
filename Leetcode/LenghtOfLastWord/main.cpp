#include<string>
#include<iostream>



int lengthOfLastWord(std::string s)
{
  size_t size = s.length() ; 
  while( s[size] > 0 ){
    std::cout << s[size] << " " ;
    -- size ;
  }
  std::cout << std::endl; 
  return 0 ; 
}

int main() 
{
  std::string s = "   fly me   to   the moon  " ; 
  lengthOfLastWord(s) ; 
  return 0 ; 
}
