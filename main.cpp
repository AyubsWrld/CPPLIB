#include <ios>
#include <iostream>
#include <fstream>


struct Request  // 8 bytes
{
	int x ; 
	int y ; 
};

int main (int argc, char *argv[]) {
	std::ofstream fptr ; 
	fptr.open("test.bin" , std::ios_base::binary ) ; 

  Request x = { 1 , 2 } ; 
  char* stream = reinterpret_cast<char*>(&x) ; 

  fptr.write( stream , sizeof(x)) ; 
	return 0;
}
