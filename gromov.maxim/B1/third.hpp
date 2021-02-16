#ifndef THIRD_HPP
#define THIRD_HPP

#include <iostream>
#include <vector>
#include "print.hpp"

void thirdTask()
{
  std::vector<int> vector;
  int num = -1;
  
  while(std::cin >> num)
  {
    if(num == 0)
    {
      break;
    }

    vector.push_back(num);
  }

  if(!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Fail with read number!");
  }

  if(vector.empty())
  {
    return;
  }

  if(num != 0)
  {
    throw std::ios_base::failure("Fail with read number!");
  }

  if(*(vector.rbegin()) == 1)
  {
    for(auto it = vector.begin(); it < vector.end();)
    {
      if((*it) % 2 == 0)
      {
        it = vector.erase(it);
        continue;
      }
      ++it;
    }
  }

  if(*(vector.rbegin()) == 2)
  {
    for(auto it = vector.begin(); it < vector.end();)
    {
      if((*it) % 3 == 0)
      {
        it = vector.insert(++it, 3, 1);
        it += 3;
        continue;
      }
      it++;
    }
  }
  print(vector);
}

#endif
