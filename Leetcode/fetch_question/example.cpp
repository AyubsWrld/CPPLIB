#include <iostream>
#include <curl/curl.h>
#include <regex>



typedef struct {
  std::string title ; 
  std::string body  ;
} HTML ;


// How does this work ? 

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
  size_t realsize = size * nmemb;
  HTML* pointer_to_data = (HTML *)userdata ; 
  pointer_to_data->title = pointer_to_data->title + ptr ; 
  std::cout << pointer_to_data->title;
  return realsize ; 
}


int main (int argc, char *argv[]) {

  HTML html ; 
  CURL* curl = curl_easy_init() ; 
  CURLcode res = curl_easy_setopt( curl , CURLOPT_URL , "https://leetcode.ca/all/1.html") ; 
  if ( res ) { 
    return EXIT_FAILURE ; 
  }

  res = curl_easy_setopt( curl , CURLOPT_WRITEFUNCTION , write_callback ) ;

  if ( res ) { 
    return EXIT_FAILURE ; 
  }

  res = curl_easy_setopt( curl , CURLOPT_WRITEDATA , (HTML* )&html )  ; 

  curl_easy_perform( curl ) ;

  std::cout << html.title << std::endl ;
  curl_easy_cleanup(curl) ; 

  return EXIT_SUCCESS;
}
