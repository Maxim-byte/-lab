#ifndef FIRST_HPP
#define FIRST_HPP

#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "telephone-interface.hpp"
#include "commands.hpp"

void firstTask()
{
  TelephoneBook book;
  TelephoneInterface phoneBook(std::make_unique<TelephoneBook>(book));
  std::for_each(std::istream_iterator<std::function<void(TelephoneInterface & book, std::ostream & output)>>(std::cin),
    std::istream_iterator<std::function<void(TelephoneInterface& book, std::ostream& output)>>(),
      [&](auto& function)
      {
          function(phoneBook, std::cout);
      });
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading in task 1");
  }
}
#endif
