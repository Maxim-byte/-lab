#include "first.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <functional>
#include <algorithm>
#include <cmath>

void firstTask()
{
  auto functor = std::bind(std::multiplies<double>(), M_PI, std::placeholders::_1);
  std::transform(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), 
    std::ostream_iterator<double>(std::cout, " "), functor);
  if(!std::cin.good() && !std::cin.eof())
  {
    throw std::ios::failure("Error while reading data!");
  }
}
