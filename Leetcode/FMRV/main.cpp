#include <iostream> 
#include <vector> 
#include <algorithm>    

std::vector<int> findMissingAndRepeatingValues(std::vector<std::vector<int>>& grid){
  int SIZE = grid[0].size();
  int i , j ; 
  bool duplicateFound = false ; 
  bool missingFound   = false ; 

  std::vector<int> list ; 
  std::vector<int> retVal = { 0 , 0 } ; 


  for ( i = 0 ; i < SIZE ; ++i ) {
    for ( j = 0 ; j < SIZE ; ++j ) { 
      list.push_back(grid[i][j]) ; 
    }
  }

  std::sort( list.begin() , list.end() ) ; 

  for( i = 0 ; i <  ( SIZE*SIZE ) - 1  ; i++ ) { 
    if ( list[ i ] == list[ i + 1]) 
    {
      retVal[0] = list[i] ; 
    }
  }
  return retVal ; 
}


int main(){

  std::vector<std::vector<int>> grid = { 
    {9,1,7},
    {8,9,2},
    {3,4,6}

  } ; 

  std::vector<std::vector<int>> grid2 = {{1,3},{2,2}} ;
  std::vector<int> retVal = findMissingAndRepeatingValues(grid) ; 
  std::vector<int> retVal2 = findMissingAndRepeatingValues(grid2) ; 
  for ( auto i : retVal ) { 
    std::cout << i << " " ; 
  }

  std::cout << std::endl ; 
  for ( auto i : retVal2 ) { 
    std::cout << i << " " ; 
  }
  return EXIT_SUCCESS ; 
}
