#include <iostream>
#include <curl/curl.h>
#include <regex>



typedef struct {
  std::string title    ; 
  std::string acronym  ;
  std::string body     ;
  std::string unparsed ;
} HTML ;


// How does this work ? 

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
  size_t realsize = size * nmemb;
  HTML* pointer_to_data = (HTML *)userdata ; 
  pointer_to_data->unparsed = pointer_to_data->unparsed + ptr ; 
  return realsize ; 
}

size_t parse_title( HTML* html )
{
  std::smatch m ; 
  std::regex_search( html->unparsed , m , std::regex("(<title>)")) ; 

  if ( m.empty()) {
    std::cout << "Match not found" << std::endl ;
    return -1 ; 
  }

  html->unparsed = m.suffix() ; 
  std::regex_search( html->unparsed , m , std::regex("(</title>)")) ; 
  if ( m.empty()) {
    std::cout << "Match not found" << std::endl ;
    return -1 ; 
  }
  html->title = m.prefix() ; 
  std::cout << html->title << std::endl ;
  return 0 ; 
}

size_t  parse_html( HTML* html ) {

  size_t parse_code = parse_title( html ) ; 
  if ( parse_code ) {
    return -1 ; 
  }
  return 0 ; 
}

size_t make_directory() { 
  system("mkdir test") ;
  return 0 ; 
}

int main (int argc, char *argv[]) {


  // ========================================================= CURL setup ======================================================================
  
  HTML html ; 
  CURL* curl = curl_easy_init() ; 
  CURLcode res = curl_easy_setopt( curl , CURLOPT_URL , "https://leetcode.ca/all/1.html") ; 
  res = curl_easy_setopt( curl , CURLOPT_WRITEFUNCTION , write_callback ) ;
  res = curl_easy_setopt( curl , CURLOPT_WRITEDATA , (HTML* )&html )  ; 
  curl_easy_perform( curl ) ;
  curl_easy_cleanup(curl) ; 

  // ========================================================= CURL setup ======================================================================


  // ========================================================= HTML Parse ======================================================================

  parse_html( &html ) ; 
  make_directory() ; 

  // ========================================================= HTML Parse ======================================================================
  

  return EXIT_SUCCESS;
}
