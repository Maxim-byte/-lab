#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <iosfwd>
#include <functional>
#include <map>
#include "telephone-interface.hpp"

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> printInvalid();

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> add(std::istream& sin);

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> store(std::istream& sin);

std::function<void(TelephoneInterface& phoneBook, std::ostream& ou)> insert(std::istream& sin);

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> deleteBookmark(std::istream& sin);

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> showBookmark(std::istream& sin);

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> move(std::istream& sin);

std::istream& operator >>(std::istream& in, std::function<void(TelephoneInterface& phoneBook, std::ostream& out)>& function);

static const std::map<std::string, std::function<std::function<void(TelephoneInterface& phoneBook, std::ostream& out)>(std::istream&)>>
  COMMANDS_TABLE = 
  {
    {"add", add},
    {"store", store}, 
    {"insert", insert},
    {"delete", deleteBookmark},
    {"show", showBookmark},
    {"move", move}
  };

#endif
