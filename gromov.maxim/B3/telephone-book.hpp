#ifndef TELEPHONE_BOOK_HPP
#define TELEPHONE_BOOK_HPP

#include <list>
#include <iosfwd>
#include <string>
#include <utility>

class TelephoneBook
{
public:
  struct PhoneNote_t
  {
    std::string number;
    std::string name;
  };
  using Iterator = std::list<PhoneNote_t>::iterator;

  void showCurrent(Iterator iterator);

  Iterator insertBefore(const std::string & name, const std::string & number, Iterator iterator);

  Iterator insertAfter(const std::string & name, const std::string & number, Iterator iterator);

  Iterator replace(const std::string & name, const std::string & number, Iterator iterator);

  void pushBack(const std::string & name, const std::string & number);

  Iterator deleteUser(Iterator iterator);

  Iterator advance(Iterator iterator, int step);

  Iterator begin();

  Iterator end();

private:
  std::list<PhoneNote_t> container_;
};

#endif
