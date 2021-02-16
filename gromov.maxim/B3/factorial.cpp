#include "factorial.hpp"
#include <string>
#include <stdexcept>

const size_t MIN = 1;
const size_t MAX = 10;

Factorial::Iterator::Iterator() :
  value_(MIN),
  index_(MIN)
{}

Factorial::Iterator::Iterator(size_t index):
  value_(getValue(index)),
  index_(index)
{
  if(index < MIN || index > MAX + 1)
  {
    std::invalid_argument(std::string("Invalid index!") + std::to_string(index_));
  }
}

size_t &Factorial::Iterator::operator*()
{
  return value_;
}

size_t *Factorial::Iterator::operator->()
{
  return &value_;
}

Factorial::Iterator Factorial::Iterator::operator++()
{
  if(index_ > MAX)
  {
    throw std::out_of_range("Index out_of_range!");
  }
  ++index_;
  value_ *= index_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator++(int)
{
  if(index_ > MAX)
  {
    throw std::out_of_range("Index out_of_range!");
  }
  auto temp = Iterator(*this);
  ++(*this);
  return temp;
}

Factorial::Iterator Factorial::Iterator::operator--()
{
  if(index_ <= MIN)
  {
    throw std::out_of_range("Index out_of_range!");
  }
  value_ /= index_;
  --index_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator--(int)
{
  if(index_ <= MIN)
  {
    throw std::out_of_range("Index out_of_range!");
  }
  auto temp = Iterator(*this);
  --(*this);
  return temp;
}

bool Factorial::Iterator::operator==(Iterator &it) const
{
  return index_ == it.index_;
}

bool Factorial::Iterator::operator!=(Iterator &it) const
{
  return index_ != it.index_;
}

size_t Factorial::Iterator::getValue(size_t index)
{
  if(index > MAX + 1)
  {
    return 1;
  }
  auto temp = 1;
  for(size_t i = 1; i <= index; ++i)
  {
    temp *= i;
  }
  return temp;
}


Factorial::Iterator Factorial::begin()
{
  return Iterator(MIN);
}

Factorial::Iterator Factorial::end()
{
  return Iterator(MAX + 1);
}
