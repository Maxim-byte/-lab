#include <iostream>
#include <vector>
#include <forward_list>
#include "sort.hpp"
#include "print.hpp"
#include "detail.hpp"

void firstTask(const char * sortingType)
{   
  auto compare = detail::getCompare<std::vector<int>::value_type>(sortingType);
  std::vector<int> vector;
  int integer;

  while(std::cin >> integer)
  {
    vector.push_back(integer);
  }

  if(!std::cin.eof() && !std::cin.good())
  {
    throw std::ios_base::failure("Fail with reading data!");
  }

  if(vector.empty())
  {
    return;
  }

  std::vector<int> vectorIndex = vector;

  collectionSort<IndexAccess>(vectorIndex, compare);
  print(vectorIndex);

  std::vector<int> vectorAt = vector;
  collectionSort<AtAccess>(vectorAt, compare);
  print(vectorAt);
  
  std::forward_list<int> listIt(vector.begin(), vector.end());
  collectionSort<Iterator>(listIt, compare);
  print(listIt);
}
