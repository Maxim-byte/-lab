#ifndef FIRST_HPP
#define FIRST_HPP

#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_set>

void firstTask()
{
  std::unordered_set<std::string> set{std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>()};
  
  if(!std::cin.eof() && !std::cin.good())
  {
    throw std::ios_base::failure("Fail while reading data!");
  }
  std::copy(set.begin(), set.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

#endif
