#include <iostream>

class Point
{
  int m_x{} ; 
  int m_y{} ; 

public:
  const static int m_z{};
  Point(int x = 0, int y = 0)
    : m_x(x),
      m_y(y) 
  {

  }


  //Point(const Point& other) = delete;
  Point(const Point& other)
    : m_x(other.m_x),
      m_y(other.m_y)
  {
    std::cout << "Copy constructor called" << std::endl; 
  }

  // Point(const Point& other)
  // {
  //   std::cout << "Copy constructor called" << std::endl; 
  // }

};

int main () 
{
  Point p{1,2}; 
  auto y{p};
  return 0;
}
