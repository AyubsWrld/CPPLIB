#include<string>
#include<iostream>





// Why didn't >= 0 work ? 

int lengthOfLastWord(std::string s)
{
  size_t size = s.length() ; 
  int len = 0 ; 
  --size ; 

  // Go to the first occurence of the letter 
  
  while( s[size] == ' ' ) {
    --size ;
  }


  while( s[size] != ' ' )
  {
    ++ len ; 
    --size ; 
  }
  std::cout << len;
  return len ; 
}

int main() 
{
  std::string s = "   fly me   to   the moon  " ; 
  lengthOfLastWord(s) ; 
  return 0 ; 
}
