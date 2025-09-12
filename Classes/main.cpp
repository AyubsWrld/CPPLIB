#include <iostream>
#include <string>




class Ball 
{
  std::string m_color{};
  float m_radius{} ; 

public: 


  Ball( const std::string& color = "black" , float radius = 10.0f )
    : m_color{color}
    , m_radius{radius} 
    {
      print();
    }

  Ball( float radius ) 
    : Ball{ "black" , radius }
    {
    }

  void print() 
  {
      std::cout << "Ball Created ( " << m_color << " , " << m_radius << " )\n"  ; 
  }
  
};

int main (int argc, char *argv[]) 
{
  Ball b{} ; 
  Ball r{ 20.0f } ; 
  Ball y{ "blue" , 20.0f } ; 
  return EXIT_SUCCESS;
}
