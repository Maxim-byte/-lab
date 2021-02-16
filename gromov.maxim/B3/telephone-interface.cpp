#include "telephone-interface.hpp"
#include <ostream>
#include <algorithm>
#include "detail.hpp"

TelephoneInterface::TelephoneInterface(std::unique_ptr<TelephoneBook>&& telephoneBook)
{
  telephoneBook_ = std::move(telephoneBook);
  marks_.insert(std::make_pair("current", telephoneBook_->begin()));
}

void TelephoneInterface::add(const std::string & name, const std::string & number)
{
  telephoneBook_->pushBack(name, number);
  if (telephoneBook_->begin() == --telephoneBook_->end())
  {
    marks_["current"] = telephoneBook_->begin();
  }
}

void TelephoneInterface::store(const std::string &markName, const std::string &newMarkName)
{
  auto it = marks_.find(markName);
  if (it != marks_.end())
  {
    marks_.insert(std::make_pair(newMarkName, it->second));
    return;
  }
  detail::print("<INVALID BOOKMARK>\n");
}

void TelephoneInterface::insertBefore(const std::string & name, const std::string & number, const std::string &markName)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    detail::print("<INVALID BOOKMARK>\n");
    return;
  }
  it->second = telephoneBook_->insertBefore(name, number, it->second);
}

void TelephoneInterface::insertAfter(const std::string & name, const std::string & number, const std::string &markName)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    detail::print("<INVALID BOOKMARK>\n");
    return;
  }
  it->second = telephoneBook_->insertAfter(name, number, it->second);
}

void TelephoneInterface::deleteMark(const std::string &markName)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    detail::print("<INVALID BOOKMARK>\n");
    return;
  }
  if(it->second == telephoneBook_->end())
  {
    return;
  }
  auto deleteIt = it->second;
  for (auto i = marks_.begin(); i != marks_.end(); ++i)
  {
    if (i->second == deleteIt)
    {
      if (std::next(i->second) == telephoneBook_->end())
      {
        i->second = std::prev(deleteIt);
      } else
      {
        i->second = std::next(deleteIt);
      }
    }
  }
  telephoneBook_->deleteUser(deleteIt);
}

void TelephoneInterface::showMarkName(const std::string &name)
{
  if (marks_.empty())
  {
    detail::print("<EMPTY>\n");
    return;
  }
  auto it = marks_.find(name);
  if (it == marks_.end())
  {
    detail::print("<INVALID BOOKMARK>\n");
    return;
  }
  if(it->second == telephoneBook_->end())
  {
    detail::print("<EMPTY>\n");
  }
  telephoneBook_->showCurrent(it->second);
}

void TelephoneInterface::moveMark(const std::string &markName, int step, MovePosition position)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    detail::print("<INVALID BOOKMARK>\n");
    return;
  }
  if (position == MovePosition::LAST)
  {
    it->second = std::prev(telephoneBook_->end());
    return;
  }
  if (position == MovePosition::FIRST)
  {
    it->second = telephoneBook_->begin();
    return;
  }
  it->second = telephoneBook_->advance(it->second, step);
}
