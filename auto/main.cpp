#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <memory>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/_types/_socklen_t.h>
#include <sys/socket.h>
#include <type_traits>
#include <fstream>
#include <unistd.h>

#define ERRNO(X){\
  static_assert(std::is_integral<decltype(X)>::value , "value must be of integral type");\
  if( X == -1 ){\
    fprintf( stderr , "[ LINE %i ]: %s\n", __LINE__ , strerror(X)) ;\
    exit(EXIT_FAILURE);\
  }\
}



struct Request 
{
  uint8_t bytecode ; 
  uint8_t x = {0xde}; 
  uint8_t y = {0xed}; 
  uint8_t z = {0xbe}; 
  uint8_t f = {0xef}; 
};

using request_handler = void (*)(Request) ; 


void foo( Request x )
{
  std::cout << "Hello" << std::endl ; 
}

static request_handler cb[2] =
{
  &foo,
  &foo,
};

int main()
{
  int sockfd , newfd, socklen , rv ; 
  struct sockaddr_in main_sock = { 
    .sin_addr = {inet_addr( "127.0.0.1" )},
    .sin_family = AF_INET,
    .sin_port = htons(4090),
    .sin_zero = { 0 } // What happens if this is blank ? 
  } ; 

  struct sockaddr_storage user_sock ;  // Junk values ? 
                                       
  sockfd = socket( AF_INET , SOCK_STREAM , 0 ) ; 

  rv = bind( sockfd , ( struct sockaddr* ) &main_sock , sizeof(sockaddr_in)) ; 

  rv = listen( sockfd , 20 ) ; 

  socklen_t x  = sizeof(struct sockaddr_storage); 
  newfd = accept( sockfd , (struct sockaddr*) &user_sock , &x) ; 
  /*newfd = accept( sockfd , (struct sockaddr*) &user_sock , (socklen_t*) (sizeof(struct sockaddr_storage)) ) ; */

  if(!fork())
  {
    close(sockfd);  // I get a copy here ? 
    char buffer[1024];

    int bytes = recv(newfd , &buffer , sizeof(buffer) , 0 ); 
    
    uint8_t bytecode ; 
    memcpy(&bytecode , &buffer , sizeof(bytecode)); 

    std::cout << ( bytecode == 0xde ) << "\n" ; 
    close(newfd); 
  }
  close(newfd); 
}

