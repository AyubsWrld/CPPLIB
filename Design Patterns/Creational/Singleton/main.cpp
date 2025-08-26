#include <iostream>
#include <unordered_map>
#include <tuple>

typedef const char* IID;
typedef const char* PID;
class IItemBroker; 

enum class ItemCategory
{
    IC_None,
    IC_Medical,
    IC_LightSource,
    IC_AudioTool,
    IC_Special
};

struct ItemSlot
{
    IID ItemID{}; 
    ItemCategory ItemType;
};


class IItemBroker
{
    
public:
    virtual void AddItem(PID, ItemSlot&) = 0 ; 
};

class IBSingleton : public IItemBroker
{
    std::unordered_map<PID, ItemSlot> PlayerInventory;
    
public:

    static IBSingleton* instance ; 

    static IBSingleton* GetInstance(); 

    IBSingleton() = default ;

    IBSingleton(IBSingleton& other) = delete; 
    
    void operator=(const IBSingleton&) = delete; 
   
    virtual void AddItem(PID, ItemSlot&) override
    {
        std::cout << "Invoked from singleton" << std::endl ; 
    }
    
};

IBSingleton* IBSingleton::GetInstance()
{
  if(IBSingleton::instance == nullptr)
  {
      instance = new IBSingleton(); 
  }
  return instance; 
}

class Player
{
    IItemBroker* itemBroker; 
    ItemSlot _inventory[4]; 
    PID _playerID; 
    
public:

    Player(IItemBroker* ib, const char* pid)
      : _playerID(pid),
        itemBroker(ib)
    {
    }

    void AddItem()
    {
      /* RPC here to server */
      ItemSlot tmp = {  "123981270398", ItemCategory::IC_LightSource} ; 
      itemBroker->AddItem(_playerID, tmp); 
    }
};

IBSingleton* IBSingleton::instance = nullptr; 


int main() {
    auto print_index = []<std::size_t I>(std::integral_constant<std::size_t, I>) {
        std::cout << "Element index: " << I << '\n';
    };

    print_index(std::integral_constant<std::size_t, 2>{}); // Element index: 2
}

