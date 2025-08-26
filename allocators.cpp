#include <iostream>
#include <type_traits>
#include <unordered_map>
#include <random>

enum class ECardType
{
  ECT_Undefined, 
  ECT_Chariot, 
  ECT_Lovers,
  ECT_World,
  ECT_Magician,
  ECT_Plague,
  ECT_Max
};



std::ostream& operator<<(std::ostream& ostream, const ECardType e)
{
  switch(e)
  {
    case ECardType::ECT_Undefined:
      ostream << "Undefined:" ; 
      break;
    case ECardType::ECT_Chariot:
      ostream << "Chariot:" ; 
      break;
    case ECardType::ECT_Lovers:
      ostream << "Lovers:" ; 
      break;
    case ECardType::ECT_World:
      ostream << "World:" ; 
      break;
    case ECardType::ECT_Magician:
      ostream << "Magician:" ; 
      break;
    case ECardType::ECT_Plague:
      ostream << "Plague:" ; 
      break;
    case ECardType::ECT_Max:
      ostream << "Plague:" ; 
      break;
  }
  return ostream; 
}

struct PlayerController
{
  void Invoke()
  {
    std::cout << "Invoking" << std::endl; 
  }
};

struct FTarotCard
{
  const ECardType Alignment{}; 
  const bool Affinity{};

  FTarotCard(ECardType CardType, bool Affinity) 
    : Alignment(CardType),
    Affinity(Affinity)
  {
    std::cout << "Card: [" << Alignment << ( Affinity ? "Upright" : "Reversed" )<< "]" <<std::endl ; 
  }

  FTarotCard(const std::pair<ECardType,bool>& InitializationPair) 
    : Alignment(InitializationPair.first),
    Affinity(InitializationPair.second)
  {
    std::cout << "Card: [" << Alignment << ( Affinity ? "Upright" : "Reversed" )<< "]" <<std::endl ; 
  }
};


struct FTarotCardGenerator
{
  std::unordered_map<ECardType,std::pair<int,int>> Telemetry; 

  static constexpr auto KCardTypeMax = static_cast<std::underlying_type_t<ECardType>>(ECardType::ECT_Max) ; 
  static int GenerateRandomInteger() 
  {
    std::random_device d; 
    std::mt19937 gen(d()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dv(1, KCardTypeMax);
    return dv(gen); 
  }
  static const std::pair<ECardType, bool> GenerateCardInfo(int rng_int)
  {
    return {static_cast<ECardType>( rng_int % KCardTypeMax + 1), rng_int % 2} ;
  }

  static FTarotCard GenerateCard()
  {
    std::pair<ECardType, bool> initialization_pair = FTarotCardGenerator::GenerateCardInfo(GenerateRandomInteger());
    return FTarotCard{initialization_pair}; 
  }
};


int main()
{
  std::unordered_map<ECardType,std::pair<int,int>> Telem{} ; 
  for (int i = 0; i < 10; ++i)
    FTarotCardGenerator::GenerateCard();
  return 0; 
}
