#include <iostream> 

template <typename T>
bool isSmallEnough( T x){
   return sizeof(x) <= sizeof(void*) * 2;
}

class Shape {
public:
  virtual void getName() const = 0 ; 
  virtual void getDimensions() const = 0 ; 
  virtual Shape* copy() const = 0 ; 
}; 

class Triangle : public Shape {
private:
  int height ;
  int width  ;
  std::string name = "Triangle" ; 
public:
  Triangle( int h , int w ) : height(h) , width(w) {
    std::cout << "Triangle created" << std::endl  ; 
  }
  void getName() const override {
    std::cout << this->name << std::endl ;
  }
  void getDimensions() const override {
    std::cout << this->height << std::endl ;
  }
  Shape* copy() const override {
    /*return new Triangle(this*) ; */
    return new Triangle(*this) ;  // Why does this work and not this* 
  }

}; 

typedef struct{
  int x   ;
  short y ;
}Value; 

int main (int argc, char *argv[]) {
  Triangle* triangle1 = new Triangle( 4 , 3 ) ; 
  Triangle* triangle2 = (Triangle*) triangle1->copy() ; 
  Triangle triangle3 = Triangle( 7 , 8 ) ; 
  return 0;
}
