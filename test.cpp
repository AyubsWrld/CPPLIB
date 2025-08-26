#include <iostream> 
#include <type_traits> 
#include <memory> 
#include <utility> 
#include <algorithm> 
#include <array> 

/* 16 bytes */ 
struct alignas(double) DVector
{
  float x{} ; 
  float y{} ; 
  float z{} ; 
};

struct alignas(float) FVector
{
  float x{} ; 
  float y{} ; 
  float z{} ; 
};

class AItem
{
public:
  std::array<FVector, 5> SpawnLocations {} ;  //60 bytes
  virtual void nop(){ std::cout << "AItemBase" << std::endl ; } ;  // 8 bytes + 4 padding 
};

class ALightSource : public AItem 
{
public:
  float BFidelity{} ; //60 + 4 bytes?  64 % alignof(ALightSource)  == 0 ? why 72 , Also has vtable ptr so 60 + 4 + 8 = 72.
  virtual void nop() override { std::cout << "ALightSource" << std::endl ; } ;  // 8 bytes + 4 padding 
};

class AAudioTool : public AItem 
{
public:
  double BFidelity{} ;  // 60 + 8 + 8 = 76 -> 80. 
  virtual void nop() override { std::cout << "AAudioTool" << std::endl ; } ;  // 8 bytes + 4 padding 
};


template <typename T>
constexpr size_t bar()
{
  return sizeof(T) ; 
}

template <typename... T>
constexpr size_t foo()
{
  return (bar<T>() + ...) ;
}

template <typename... T>
constexpr size_t aof()
{
  return std::max(std::initializer_list<size_t>{ alignof(T)...}) ; 
}

template <typename... T>
inline std::tuple<T...> ctor()
{
}

enum class EItemCategory
{
  IC_Undefined,
  IC_Consumable,
  IC_LightSource,
  IC_Max
};

struct Item { 
  EItemCategory Category{};  //value-initialized -> undef 
  float x{} ; 
  float y{} ; 
  float z{} ; 
};

struct Consumable : public Item 
{ 
  EItemCategory Category{EItemCategory::IC_Consumable};  
  float w{}; 
};

struct LightSource : public Item 
{ 
  EItemCategory Category{EItemCategory::IC_LightSource};  
  double w{}; 
};

struct FItemSpawnConfiguration
{
  std::array<EItemCategory, 8> ItemTypes{} ; 
};

std::string eton(EItemCategory e)
{
  switch(e)
  {
    case EItemCategory::IC_Undefined:
      return "Undefined" ;
    case EItemCategory::IC_Consumable:
      return "Consumable" ;
    case EItemCategory::IC_LightSource:
      return "LightSource" ;
    default:
      return " ";
  }
}

using constructor = AItem(void) ; 

std::ostream& operator<<(std::ostream& o, EItemCategory e)
{
  std::cout << eton(e) << std::endl; 
  return o;
}

void TestGen()
{
  constexpr auto Max = static_cast<std::underlying_type_t<EItemCategory>>(EItemCategory::IC_Max) ; 
  for(int i{} ; i < 10 ; i++)
  {
    std::cout << static_cast<EItemCategory>(rand() % max) << std::endl ; 
  }
}


/*
template <typename T, size_t U>
struct IAllocator
{
  static constexpr auto max = static_cast<std::underlying_type_t<EItemCategory>>(EItemCategory::IC_Max) ; 
  std::initializer_list<std::shared_ptr<AItem>> Gen()
  {
    for(int i{} ; i < U ; i++)
    {
    }
  }
  std::array<std::shared_ptr<AItem>,8> V; 
};
*/

[[nodiscard]] std::shared_ptr<AItem> GetItemSharedPtr(EItemCategory e) 
{
  switch(e)
  {
    case EItemCategory::IC_Consumable : 
      return std::make_shared<AAudioTool>() ; 
    case EItemCategory::IC_LightSource: 
      return std::make_shared<ALightSource>() ; 
    default:
      return std::make_shared<AItem>() ; 
  }
}

template <size_t U>
struct IAllocator
{
  static constexpr auto max = static_cast<std::underlying_type_t<EItemCategory>>(EItemCategory::IC_Max) ;  // Rename ts
  std::array<std::shared_ptr<AItem>,U> V; 
  auto Gen()
  {
    for(size_t i{} ; i < U ; i++)
    {
      EItemCategory e = static_cast<EItemCategory>(rand() % max) ; 
      V[i] = GetItemSharedPtr(e);
    }
    return V; 
  }
};

int main()
{
  IAllocator<10> V{}; 
  auto x = V.Gen() ; 
  for (auto i : x) 
  {
    i->nop();
  }
  return 0; 
}


