#ifndef TELEPHONE_INTERFACE_HPP
#define TELEPHONE_INTERFACE_HPP

#include <map>
#include <utility>
#include <memory>
#include <string>
#include "telephone-book.hpp"

class TelephoneInterface
{
public:

  enum class MovePosition
  {
    FIRST,
    LAST,
    UNDEFINED
  };

  TelephoneInterface(std::unique_ptr<TelephoneBook>&& telephoneBook);

  void add(const std::string & name, const std::string & number);

  void store(const std::string & markName, const std::string & newMarkName);

  void insertBefore(const std::string & name, const std::string & number, const std::string & markName);

  void insertAfter(const std::string & name, const std::string & number, const std::string & markName);

  void deleteMark(const std::string & markName);

  void showMarkName(const std::string & markName);

  void moveMark(const std::string & markName, int step, MovePosition position = MovePosition::UNDEFINED);

private:
  std::unique_ptr<TelephoneBook> telephoneBook_;
  std::map<std::string, TelephoneBook::Iterator> marks_;
};

#endif
