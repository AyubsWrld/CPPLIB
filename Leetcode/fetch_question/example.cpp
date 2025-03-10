#include <iostream>
#include <curl/curl.h>
#include <filesystem>
#include <regex>
#include <cstring>
#include <vector>
#include <fstream>

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
  return 0 ; 
}

size_t set_acronym( HTML* html )
{
  std::string acronym ; 
  std::string::iterator itr_b = html->title.begin() ; 
  std::string::iterator itr_e = html->title.end() ; 
  while ( itr_b != itr_e ) {
    if ( *itr_b == ' ' ) {
      acronym += *++itr_b ;
    }else {
      ++itr_b ;
    }
  }
  if(acronym.empty()){
    return -1 ; 
  }
  html->acronym = acronym ; 
  return 0  ;
}

size_t makedir( std::string& directory ) 
{
  if ( std::filesystem::exists( directory ) ) {
    std::cout << "directory exists" << std::endl ;
    return -1 ;
  }

  if ( !std::filesystem::create_directory( directory ) ) {
    std::cout << "Failed to create directory" << std::endl ;
    return -1 ;
  }
  std::cout << "Directory Successfully Created " << std::endl ;
  return 0  ; 
}  

/*size_t parse_body( HTML* html ){*/
/*  std::regex regex("<p>(.*?)</p>");*/
/*  std::smatch match;*/
/*  std::string description;*/
/**/
/*  auto it = html.cbegin();*/
/*  while (std::regex_search(it, html.cend(), match, regex)) {*/
/*      description += match[1].str() + "\n";*/
/*      it = match.suffix().first;*/
/*  }*/
/*  return 0 ;*/
/**/
/*}*/


size_t  parse_html( HTML* html ) {

  size_t parse_code = parse_title( html ) ; 
  if ( parse_code ) {
    return -1 ; 
  }

  parse_code = set_acronym( html ) ; 

  if ( parse_code ) {
    return -1 ; 
  }

  parse_code = set_acronym( html ) ; 

  if ( parse_code ) {
    return -1 ; 
  }

  /*parse_code = parse_body( html )  ; */
  return 0 ; 
}


// Needs work 

size_t create_file( HTML* html )
{
  std::string path = static_cast<std::string>( std::filesystem::current_path() )  + "/"  + html->acronym + "/outline.md" ;
  std::ofstream ofs(path) ; 
  ofs << "# " << html->title ; 
  if( !ofs ) {
    return -1 ; 
  }
  ofs.close() ; 
  return 0 ;  
}

int main (int argc, char *argv[]) {


  // ========================================================= CURL setup ======================================================================
  
  HTML html ; 
  CURL* curl = curl_easy_init() ; 
  CURLcode res = curl_easy_setopt( curl , CURLOPT_URL , "https://leetcode.ca/all/30.html") ; 
  res = curl_easy_setopt( curl , CURLOPT_WRITEFUNCTION , write_callback ) ;
  res = curl_easy_setopt( curl , CURLOPT_WRITEDATA , (HTML* )&html )  ; 
  curl_easy_perform( curl ) ;
  curl_easy_cleanup(curl) ; 

  // ========================================================= CURL setup ======================================================================


  // ========================================================= HTML Parse ======================================================================

  parse_html( &html ) ; 
  makedir( html.acronym ) ;
  create_file( &html ) ;  

  // ========================================================= HTML Parse ======================================================================
  

  return EXIT_SUCCESS;
}
