#include <iostream>
#include <cassert>
#include <array>
#include <type_traits>
#include <unordered_map>
#include <cstring>

#define HEIGHT 5 
#define WIDTH  5 

const unsigned char array[HEIGHT][WIDTH] = 
{
  {'#', '#', '#', '#', '#'},
  {'#', '#', '#', '#', '#'},
  {'#', '#', '#', '#', '#'},
  {'#', '#', '#', '#', '#'},
  {'#', '#', '#', '#', '#'}
};


void callback()
{
  std::cout << "Hello world" << std::endl; 
}

struct FTile
{
  void(*cb)(); 

  bool operator==(const FTile& other)
  {
    if(cb && other.cb)
      return *cb == *other.cb;
    return false; 
  }
};


template<typename T>
struct Foo 
{
  T m;
};

/* User defined template specialization */ 

template<>
struct std::hash<std::pair<int,int>>
{
  size_t operator()(const std::pair<int,int>& value) const noexcept
  {
    return ( size_t )  value.first ^ value.second << 10 ; 
  }
};

int main (int argc, char *argv[]) 
{
  std::cout << std::boolalpha << std::is_c
  return 0;
}
