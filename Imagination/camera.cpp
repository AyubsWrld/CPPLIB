#include <cstdint>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <array>

#define PLAYER_COUNT 8 



typedef enum 
{
  Unassigned,
  TeamRed,
  TeamBlue
}Team ; 


typedef enum 
{
  NotYetFound,
  Inventory,
  Placed,
}CameraState; 

class PlayableCharacter; 
class Monitor; 
class Battery; 
class SurveillanceCamera;

struct  camera_config_t ; 

using FVector = std::array<float,3> ; 
using CharacterArray = std::array< PlayableCharacter* , PLAYER_COUNT> ; 


namespace State{

  class State{ 
    protected:

      virtual void activate() = 0 ; 
      virtual void deactivate() = 0 ; 
                                            
    public:
      virtual bool getIsActive() const = 0 ; 
      virtual void placeCamera( FVector location ) const = 0 ; 
      virtual CameraState getState() const = 0 ; 
  };

  class Placed : public State  
  {
    private:
      SurveillanceCamera* camera_details ; 
    public: 

      void deactivate() override {
          std::cout << "Deactivating camera" << std::endl;
      }

      void activate() override
      {
        std::cout << "Activating camera" << std::endl ; 
      }

      bool getIsActive() const override
      {
        return true ;
      }
      void placeCamera( FVector location ) const override
      {
        std::cout << "Placing camera" ; 
      }

      CameraState getState() const override
      {
        return CameraState::Placed ; 
      }
  };
}

struct camera_config_t 
{
    Team owner_ ; 
    uint8_t players_in_vision_count_ ;
    std::unique_ptr<State::State> state_ ;
    std::unique_ptr<Battery> battery_ ;
};


class SurveillanceCamera
{
  private:
    Team owner_ ; 
    uint8_t players_in_vision_count_ ;
    std::unique_ptr<State::State> current_state_  ; 
    std::unique_ptr<Battery> battery_ ;
  public:

    // This is not needed .
    /*SurveillanceCamera( const SurveillanceCamera& ) = delete ; */ 
    /*SurveillanceCamera& operator=( const SurveillanceCamera& ) = delete ; */

    SurveillanceCamera( camera_config_t configuration ) : 
      owner_(configuration.owner_),
      players_in_vision_count_(configuration.players_in_vision_count_),
      current_state_(std::move(configuration.state_)),
      battery_(std::move(configuration.battery_))
  {}
};



int main (int argc, char *argv[]) 
{
  struct camera_config_t testconfig{ .owner_ = Team::Unassigned, .players_in_vision_count_ = 8, .state_ = std::unique_ptr<State::Placed>(new State::Placed())} ;
  return 0;
}
