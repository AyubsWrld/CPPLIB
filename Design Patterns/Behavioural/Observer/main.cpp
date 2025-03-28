#include <iostream> 
#include <vector> 
#include <string> 

class Object {
public: 
    virtual void update() const = 0 ; 
    virtual std::string getName() const = 0 ; 
};

class Subject { 
  public: 
    /*virtual ~Subject() = 0 ; */
    virtual void addObject( Object* user ) = 0 ; 
    virtual void removeObject( Object* user ) = 0 ; 
    virtual void emit() const = 0 ; 
};

class Guardian : public Subject {
  public: 
    Guardian() {
      std::cout << "Guardian Created" << std::endl ; 
    }
    void addObject( Object* user ) override {
      this->users.push_back( user ) ;
    }

    void removeObject( Object* user ) override  {
      std::cout << " Removing : "  << user->getName() << std::endl ;
    }

    void emit() const override {
      for( auto user : this->users ){
        user->update() ; 
      }
    }

    const std::vector<Object*>& getUsers() const { 
      return this->users ; 
    }

    Object* getLast()
    {
      return this->users[ this->users.size() - 1 ] ; 
    }
  private: 
    std::vector<Object*> users ; 
};

class User : public Object { 
  public: 
    User( std::string name ) : name_(name) 
    { 
    }
    void update() const override {
      std::cout << "Updating" << std::endl ;
    }
    std::string getName() const override { 
      std::cout << this->name_ << std::endl ; 
      return this->name_ ;
    }
  private: 
    std::string name_  ; 
};

int main (int argc, char *argv[]) 
{
  Guardian Teacher = Guardian() ; 
  for (size_t i = 0; i < 5 ; i++) {
    Teacher.addObject( new User("Ayub") );
  }

  Object* lastUser = Teacher.getLast() ; 
  lastUser->getName() ;
  delete lastUser ; 

  for( Object* user : Teacher.getUsers() ){
    user->update() ; 
  }
  return EXIT_SUCCESS;
}
