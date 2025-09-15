#include <iostream>


template<typename T>
struct Point
{
  T m_x ; 
  T m_y ; 

private:

  T m_z ; 


  Point(const T& x, const T& y, const T& z)
    : m_x{x},
      m_y{y},
      m_z{z} 
  {

  }

  bool operator==(const Point<T>& Other);

};

template<typename T>
bool Point<T>::operator==(const Point<T>& Other)
{
  return ( 
            m_x == Other.m_x &&
            m_y == Other.m_y  
          );
}


int main(int argc, char *argv[])
{
  return EXIT_SUCCESS;
}
