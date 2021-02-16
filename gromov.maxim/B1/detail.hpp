#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <functional>
#include <cstring>

namespace detail
{
  enum class sortType
  {
    ascending,
    descending
  };

  template <typename T>
  std::function<bool(T, T)> getCompare(const char * sortingType)
  {
    sortType predicateSort;
  
    if(strcmp(sortingType, "descending") == 0)
    {
      predicateSort = sortType::descending;
    } else if(strcmp(sortingType, "ascending") == 0)
    {
      predicateSort = sortType::ascending;
    } else
    {
      throw std::invalid_argument("Invalid sort type!");
    }
    
    if(predicateSort == sortType::ascending)
    {
      return std::less<const T>();
    } else
    {
      return std::greater<const T>();
    }
  }

}

#endif
