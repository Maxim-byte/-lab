#include "commands.hpp"
#include <string>
#include <stdexcept>
#include <iostream>
#include <limits>
#include "telephone-interface.hpp"
#include "detail.hpp"

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> printInvalid()
{
  return [](TelephoneInterface&, std::ostream& out)
  {
    out << "<INVALID COMMAND>" << '\n';
  };
}

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> add(std::istream& sin)
{
  std::string number = detail::readCheckedNumber(sin);
  std::string name = detail::readCheckedName(sin);
  return [name, number](TelephoneInterface& phoneBook, std::ostream&)
  {
    phoneBook.add(name, number);
  };
}

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> store(std::istream& sin)
{
  std::string mark = detail::readCheckedMarkName(sin);
  std::string newMark = detail::readCheckedMarkName(sin);
  return [mark, newMark](TelephoneInterface& phoneBook, std::ostream&)
  {
    phoneBook.store(mark, newMark);
  };
}

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> insert(std::istream& sin)
{
  std::string position;
  sin >> position;
  std::string mark = detail::readCheckedMarkName(sin);
  std::string number = detail::readCheckedNumber(sin);
  std::string name = detail::readCheckedName(sin);
  if (position == "before")
  {
    return [number, name, mark](TelephoneInterface& phoneBook, std::ostream&)
    {
      phoneBook.insertBefore(name, number, mark);
    };
  }
  else if (position == "after")
  {
    return [number, name, mark](TelephoneInterface& phoneBook, std::ostream&)
    {
      phoneBook.insertAfter(name, number, mark);
    };
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> deleteBookmark(std::istream& sin)
{
  std::string mark = detail::readCheckedMarkName(sin);
  return [mark](TelephoneInterface& phoneBook, std::ostream&)
  {
    phoneBook.deleteMark(mark);
  };
}

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> showBookmark(std::istream& sin)
{
  std::string mark = detail::readCheckedMarkName(sin);
  return [mark](TelephoneInterface& phoneBook, std::ostream&)
  {
    phoneBook.showMarkName(mark);
  };
}

std::function<void(TelephoneInterface& phoneBook, std::ostream& out)> move(std::istream& sin)
{
  std::string markName = detail::readCheckedMarkName(sin);
  std::string step;
  sin >> step;
  return [step, markName](TelephoneInterface& phoneBook, std::ostream& out)
  {
    if(step == "last" || step == "first")
    {
      phoneBook.moveMark(markName, 0, step == "last" ? TelephoneInterface::MovePosition::LAST
          : TelephoneInterface::MovePosition::FIRST);
    }
    else
    {
      int stepInt;
      try
      {
        stepInt = detail::getIntFromStepByModificationStep(const_cast<std::string &>(step));
      }
      catch(const std::logic_error&)
      {
        out << "<INVALID STEP>" << '\n';
        return;
      }
      phoneBook.moveMark(markName, stepInt);
    }
  };
}

std::istream& operator >>(std::istream& in, std::function<void(TelephoneInterface& phoneBook, std::ostream& out)>& function)
{
  try
  {
    std::string command;
    in >> command;

    auto it =  COMMANDS_TABLE.find(command);

    if(it == COMMANDS_TABLE.end())
    {
      function = printInvalid();
      return in;
    }
    function = (*it).second(in);
  }
  catch (std::logic_error& error)
  {
    if(char(in.unget().peek()) != '\n')
    {
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    function = printInvalid();
  }

  return in;
}
