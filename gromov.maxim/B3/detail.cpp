#include <string>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "detail.hpp"

std::string detail::readCheckedNumber(std::istream &sin)
{
  std::string number;
  sin >> number;
  if (number.empty())
  {
    throw std::logic_error("<INVALID NUMBER>");
  }

  for (const auto &num : number)
  {
    if (!isdigit(num))
    {
      throw std::logic_error("<INVALID NUMBER>");
    }
  }
  return number;
}

std::string detail::readCheckedName(std::istream &sin)
{
  std::string name;
  getline(sin, name);
  if (name.empty())
  {
    throw std::logic_error("<INVALID NAME>");
  }

  name.erase(0, 1);

  if ((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::logic_error("<INVALID NAME>");
  }

  name.erase(std::remove(name.begin(), name.end(), '\\'), name.end());
  name.erase(0, 1);
  name.pop_back();
  return name;
}

std::string detail::readCheckedMarkName(std::istream &sin)
{
  std::string markName;
  sin >> markName;
  if (markName.empty())
  {
    throw std::logic_error("<INVALID MARKNAME>");
  }

  for (const auto &ch : markName)
  {
    if (!isalnum(ch) && ch != '-')
    {
      throw std::logic_error("<INVALID MARKNAME>");
    }
  }
  return markName;
}

int detail::getIntFromStepByModificationStep(std::string &step)
{
  int sign = 1;
  if (step[0] == '+')
  {
    step.erase(0, 1);
  }
  if (step[0] == '-')
  {
    step.erase(0, 1);
    sign = -1;
  }
  if (step.empty())
  {
    throw std::logic_error("<INVALID STEP>");
  }
  for (const auto &num : step)
  {
    if (!isdigit(num))
    {
      throw std::logic_error("<INVALID STEP>");
    }
  }
  return std::stoi(step) * sign;;
}

void detail::print(const std::string& str)
{
  std::cout << str;
}
