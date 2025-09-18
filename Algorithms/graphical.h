#pragma once

#include <vector>
#include <cmath>
#include <utility>


namespace Xtren
{

  template<typename T, std::size_t N, std::size_t M> 
  std::vector<std::pair<std::size_t, std::size_t>> distance_to(
      const T(&graph)[N][M],
      std::pair<std::size_t, std::size_t> location,
      double dist )
  {
    std::vector<std::pair<std::size_t,std::size_t>> V;
    for(std::size_t i{} ; i < N ; i++)
      for(std::size_t j{} ; j < M ; j++)
      {
        auto dx = static_cast<double>(location.first) - i;
        auto dy = static_cast<double>(location.second) - j;
        if(std::sqrt(dx * dx + dy * dy) <= dist) V.push_back(std::pair<std::size_t, std::size_t>{i,j});
      }
    return V; 
  }
}



