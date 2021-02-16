#include "telephone-book.hpp"
#include <ostream>
#include "detail.hpp"

void TelephoneBook::showCurrent(Iterator iterator)
{
  if(iterator != container_.end())
  {
    detail::print(iterator->number + ' ' + iterator->name + "\n");
  }
}

TelephoneBook::Iterator TelephoneBook::replace(const std::string & name, const std::string & number, Iterator iterator)
{
  iterator->name = name;
  iterator->number = number;
  return iterator;
}

void TelephoneBook::pushBack(const std::string & name, const std::string & number)
{
  container_.push_back(TelephoneBook::PhoneNote_t{number, name});
}

TelephoneBook::Iterator TelephoneBook::deleteUser(Iterator iterator)
{
  if(container_.empty())
  {
    return container_.end();
  }
  return container_.erase(iterator);
}

TelephoneBook::Iterator TelephoneBook::advance(Iterator iterator, int step)
{
  int counter = 0;
  if(step > 0)
  {
    while(counter != step && iterator != std::prev(container_.end()))
    {
      iterator = std::next(iterator);
      ++counter;
    }
  } else if (step < 0)
  {
    while(counter != step && iterator != container_.begin())
    {
      iterator = std::prev(iterator);
      --counter;
    }
  }
  return iterator;
}

TelephoneBook::Iterator TelephoneBook::insertBefore(const std::string & name, const std::string & number, Iterator iterator)
{
  return container_.insert(iterator, TelephoneBook::PhoneNote_t{number, name});
}

TelephoneBook::Iterator TelephoneBook::insertAfter(const std::string & name, const std::string & number, Iterator iterator)
{
  return container_.insert(++iterator, TelephoneBook::PhoneNote_t{number, name});
}

TelephoneBook::Iterator TelephoneBook::begin()
{
  return container_.begin();
}

TelephoneBook::Iterator TelephoneBook::end()
{
  return container_.end();
}
