#include <array>
#include <cstdint>
#include <fstream>
#include <type_traits>
#include <iostream>
#include <concepts>
#include <typeinfo>
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include <array>



// Types w pointers to the beginning of a chunk of memory. does this handle all cases ?
/*template <typename T>*/
/*concept Aggregate = requires( T x ){ x.size() || std::is_same<const char*, decltype(x)>::value ;  } ; */


/*template < typename T>*/
/*concept Serializable = requires ( T x ) { x.serialize() && x.deserealize() ; } ; */
/**/
/**/
/*template <Serializable T> */
/*size_t Serialize( T x ) */
/*{*/
/*  x.serialize(); */
/*  return 0 ;*/
/*}*/



/*
  NOTE: Idrk if using the canonical_routine_name is useful or even if thats saved after converting it to a binary ( Probably Not ).
        Its really just a matter of having the routine map to some function.
*/



struct Routine
{
  enum class Type : uint8_t { Void = 1 , Bool , Char , Integer , Float , Aggregate }; // All fundamental types 32bits wide, start at 1 so that empty entries are known.
  
  struct TypeIdentifier 
  {
    Routine::Type return_type ; 
    std::array<Routine::Type, 7> arguments ;  // 64
  };

  TypeIdentifier routine_info ; 
  char cannonical_routine_name[32] ;
  char padding[24] ;  // pad for byte aligned 

  void deserialize( std::ifstream& fstream ) noexcept {  
    /*routine_info.fstream.read( reinterpret_cast<char*>(&routine_info.return_type) , sizeof(uint8_t)) ; */
    /*fstream.read( reinterpret_cast<char*>(&routine_info.argument_type) , sizeof(uint8_t)) ; */
    
    /*fstream.read( reinterpret_cast<char*>(&cannonical_routine_name) , sizeof(char) * 30 ) ; */ 

    std::cout << "deserealize" << std::endl ; 
 }

  void serialize( std::ofstream& fstream ) noexcept {
    fstream.write( reinterpret_cast<char*>(&routine_info.return_type) , sizeof(uint8_t)) ; 
    fstream.write( reinterpret_cast<char*>(&cannonical_routine_name) , sizeof(char) * 30 ) ; 
  }

};


/* [ 1 ] [ 2 ] [ 1 ] [ 1 ] [ 4 ] [ 0 ] [ 0 ] [ 0 ] */
/* [ 1 ] [ 1 ] [ 1 ] [ 1 ] [ 1 ] [ 0 ] [ 0 ] [ 0 ] */



void dispatch_routine( const Routine& target )
{

}

int main (int argc, char *argv[]) 
{

  std::unordered_map<std::string, int > test = { 
    { "Ayub" , 2 },
    { "Green" , 2 },
    { "Blue" , 2 },
    { "Four" , 2 },
  } ; 


  std::cout << test["Ayub"] ; 
  using enum Routine::Type ; 
  Routine T = { .routine_info = { .return_type = { Void } , .arguments = { Char , Char , Aggregate }} , .cannonical_routine_name = "getName" } ; 
  
  return 0;
}
