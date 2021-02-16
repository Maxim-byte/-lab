#ifndef SECOND_HPP
#define SECOND_HPP

#include <iostream>
#include <algorithm>
#include "factorial.hpp"

void secondTask()
{
  Factorial container;
  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n";
  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << std::endl;
}

#endif
