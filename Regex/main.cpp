#include<string>
#include<regex>
#include<iostream>

int strStr(std::string haystack, std::string needle)
{
  std::smatch m ; 
  if( std::regex_search( haystack , m  , std::regex(needle))){
    return m.position() ; 
  }
  return -1 ; 
}


int main(){
  std::string haystack = "sadbutsad"  ; 
  std::string needle = "sad";

  if(strStr( haystack , needle )  != -1){
    std::cout << "Match found" << "\n" ;
  }
  return 0 ; 
}



