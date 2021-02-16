#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>

template <class T> void print(T & container)
{
  for(const auto & el : container)
  {
    std::cout << el << ' ';
  }
  std::cout << std::endl;
}

#endif
