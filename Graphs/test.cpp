#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <array>
#include <unordered_map>


#define TILE_COUNT_HORIZONTAL 25 
#define TILE_COUNT_VERITCAL TILE_COUNT_HORIZONTAL

#define HALF_COUNT_HORIZONTAL 12
#define HALF_COUNT_VERITCAL 12

enum class ECalamity
{
  EC_Minoris,
  EC_Majoris,
  EC_Fatalis,
  EC_Terminus
};

struct RGen
{
  static auto GenerateRandom(const std::pair<int,int>& Range)
  {
    std::random_device d; 
    std::uniform_int_distribution<> u{Range.first, Range.second} ; 
    return u(d);  
  }

  static bool BooleanFromProbability(float Proability)
  {
    float v = (float) RGen::GenerateRandom({0,10}) / 10 ;
    return v >= Proability;
  }
};

void cb0(){ std::cout << "Minoris1" << std::endl ; }
void cb1(){ std::cout << "Minoris2" << std::endl ; }

void cb2(){ std::cout << "Majoris1" << std::endl ; }
void cb3(){ std::cout << "Majoris2" << std::endl ; }

void cb4(){ std::cout << "Fatalis1" << std::endl ; }
void cb5(){ std::cout << "Fatalis2" << std::endl ; }


void cb6(){ std::cout << "Terminus1" << std::endl ; }
void cb7(){ std::cout << "Terminus2" << std::endl ; }

std::unordered_map<ECalamity, std::array<void(*)(),2>> Callbacks = 
{
  {ECalamity::EC_Minoris, {&cb0, &cb1}},
  {ECalamity::EC_Majoris, {&cb2, &cb3}},
  {ECalamity::EC_Fatalis, {&cb4, &cb5}},
  {ECalamity::EC_Terminus, {&cb6, &cb7}}
};


/* 1KB */ 

struct Tile 
{
  using Coordinate = std::pair<short,short> ; 
  void(*invocable)(void) ;
  Coordinate Coordinates{};
  ECalamity Event{}; 

  inline constexpr auto Value(std::pair<short,short> Coordinates)
  {
    double p1{std::pow(Coordinates.first - HALF_COUNT_HORIZONTAL, 2)};
    double p2{std::pow(Coordinates.second- HALF_COUNT_VERITCAL, 2)};
    return std::sqrt(p1 + p2) ; 
  }

  inline constexpr ECalamity GenerateCalamity(float Distance)
  {
    if(Distance < 4)
    {
      return ECalamity::EC_Terminus; 
    }else if (Distance < 7) {
      return ECalamity::EC_Fatalis; 
    }else if(Distance < 8)
    {
      return ECalamity::EC_Majoris; 
    }
    return ECalamity::EC_Minoris; 
  }

  Tile(const Coordinate& b)
    : Coordinates(b)
  {
    auto rng_num = RGen::GenerateRandom({0,100}) ;
    Event = RGen::BooleanFromProbability(0.8) ? GenerateCalamity(Value(b)) : static_cast<ECalamity>(rng_num % 4); 
    auto cb = Callbacks[Event] ; 
    invocable = static_cast<decltype(invocable)>(cb[rng_num % 2]); 
  }

  Tile(short x , short y)
    : Coordinates(x,y)
  {
    auto rng_num  = RGen::GenerateRandom({0,100}) ;
    //Event = static_cast<decltype(Event)>(rng_num % 4); 
    Event = RGen::BooleanFromProbability(0.8) ? GenerateCalamity(Value({x,y})) : static_cast<ECalamity>(rng_num % 4); 
    auto cb = Callbacks[Event] ; 
    invocable = static_cast<decltype(invocable)>(cb[rng_num % 2]); 
  }

};

struct Board
{
  using Coordinates = std::pair<short,short> ; 
private: 
  static unsigned char Representation[25][25];
  static Tile Playable[138];
  static Coordinates Events[138];

  friend class BoardOperon; 
};



unsigned char Board::Representation[TILE_COUNT_HORIZONTAL][TILE_COUNT_VERITCAL] = 
  {
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ','#','#',' ',' ',' ','#',' ',' ',' ','#','#',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#','#',' ',' ',' ','#','#','#',' ',' ',' ','#','#','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ','#','#',' ',' ',' ','#','#',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#','#','#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#','#','#','#',' ',' ','#','#','#',' ',' ','#','#','#','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#','#','#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ','#','#',' ',' ',' ','#','#',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#','#',' ',' ',' ','#','#','#',' ',' ',' ','#','#','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ','#','#',' ',' ',' ','#',' ',' ',' ','#','#',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
  }; 

Tile Board::Playable[138] = {
      {0,12},{1,12},{2,12},{3,12},{4,12},
      {5,5},{5,6},{5,7},{5,8},{5,9},{5,10},{5,11},{5,12},{5,13},{5,14},{5,15},{5,16},{5,17},{5,18},{5,19},
      {6,5},{6,8},{6,12},{6,16},{6,19},
      {7,5},{7,7},{7,8},{7,12},{7,16},{7,17},{7,19},
      {8,5},{8,6},{8,7},{8,11},{8,12},{8,13},{8,17},{8,18},{8,19},
      {9,5},{9,9},{9,10},{9,14},{9,15},{9,19},
      {10,5},{10,9},{10,15},{10,19},
      {11,5},{11,8},{11,11},{11,12},{11,13},{11,16},{11,19},{11,25},
      {12,0},{12,1},{12,2},{12,3},{12,4},{12,5},{12,6},{12,7},{12,8},{12,11},{12,12},{12,13},{12,16},{12,17},{12,18},{12,19},{12,20},{12,21},{12,22},{12,23},{12,24},
      {13,5},{13,8},{13,11},{13,12},{13,13},{13,16},{13,19},
      {14,5},{14,9},{14,15},{14,19},
      {15,5},{15,9},{15,10},{15,14},{15,15},{15,19},
      {16,5},{16,6},{16,7},{16,11},{16,12},{16,13},{16,17},{16,18},{16,19},
      {17,5},{17,7},{17,8},{17,12},{17,16},{17,17},{17,19},
      {18,5},{18,8},{18,12},{18,16},{18,19},
      {19,5},{19,6},{19,7},{19,8},{19,9},{19,10},{19,11},{19,12},{19,13},{19,14},{19,15},{19,16},{19,17},{19,18},{19,19},
      {20,12},{21,12},{22,12},{23,12},{24,12}
};

struct Colouring
{
  std::unordered_map<ECalamity, std::string> Colours = 
  {
    {ECalamity::EC_Minoris, "\033[32m"},
    {ECalamity::EC_Majoris, "\033[33m"},
    {ECalamity::EC_Fatalis, "\033[31m"},
    {ECalamity::EC_Terminus, "\033[35m"}
  };

  std::string Visit(ECalamity e, const std::string& v = "") 
  {
    return Colours[e] + v  + "\033[0m"; 
  }
};


struct BoardOperon
{
  Colouring c{} ; 

  ECalamity GetTile(short i , short j) 
  {
    for(const auto t : Board::Playable)
    {
      std::pair<short,short> p{i,j} ;
      if(t.Coordinates == p)
      {
        return t.Event;
      }
    }
    return ECalamity::EC_Fatalis;
  }

  void ShowBoard()  
  {
    for(int i{}; i < 25 ; i++)
    {
      for(int j{}; j < 25 ; j++)
      {
        if(Board::Representation[i][j] == '#')
        {
          std::cout << c.Visit(GetTile(i,j),"#") << " " ; 
        }
        else
        {
          std::cout << Board::Representation[i][j] << " " ;
        }
      }
      std::cout << std::endl ; 
    }
  }

  std::pair<float,float> GetNormalized(std::pair<short,short> v)
  {
    float x{(float) v.first / TILE_COUNT_HORIZONTAL}; 
    float y{(float) v.first / TILE_COUNT_VERITCAL}  ; 
    return {x,y} ; 
  }

  void Invoke(int x)
  {
    if(x < 0 || x >= 138)
      return;
    Board::Playable[x].invocable();
    auto Coords = Board::Playable[x].Coordinates ;
    Board::Representation[Coords.first][Coords.second] = 'x';
  }

  float GenerateHeauristic(short x, short y)
  {
    return 0.0f;
  }
};


/* Each coordinate has a tile */

unsigned char GenerateGlyph()
{
  std::random_device gen{} ; 
  std::mt19937 seed ; 
  std::uniform_int_distribution<int> dis(32,127); 
  return dis(gen);
}

int main (int argc, char *argv[]) 
{
  BoardOperon b; 
  b.ShowBoard(); 
  return 0; 
}
