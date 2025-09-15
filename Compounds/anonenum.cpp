#include <iostream>
#include <type_traits>


struct Configuration
{
  enum{
    OPTION_A ,
    OPTION_B ,
    OPTION_C 
  }option;

  void PrintConfiguration()
  {
    std::cout << option << std::endl; 
  }

  using underlying = std::underlying_type<decltype(option)>;

  static bool is_integral_underlying(){ return std::is_integral_v<underlying>;};

  ~Configuration(){}
  //~Configuration(){}

};

template <typename T>
requires std::is_trivially_destructible_v<T>
void destroy_fast(const T& obj) {
    std::cout << "Destroying trivially destructible object\n";
}

template <typename T>
void destroy_fast(const T& obj) {
    std::cout << "Non-trivially destructible\n";
}

int main (int argc, char *argv[]) 
{
  int x{};
  int* px{&x};
  destroy_fast(px);
  return 0;
}
