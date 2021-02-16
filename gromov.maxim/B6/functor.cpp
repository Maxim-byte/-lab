#include "functor.hpp"
#include <numeric>
#include <limits>
#include <iomanip>
#include <iostream>

Functor::Functor():
  max_(std::numeric_limits<int>::min()),
  min_(std::numeric_limits<int>::max()),
  counter_(),
  positive_(),
  negative_(),
  oddSum_(),
  evenSum_(),
  first_(),
  last_()
{}

void Functor::operator()(int number)
{
  if(counter_ == 0)
  {
    first_ = number;
  }
  if(number > max_)
  {
    max_ = number;
  }
  if(number < min_)
  {
    min_ = number;
  }
  ++counter_;
  if(number > 0)
  {
    ++positive_;
  } else if(number < 0)
  {
    ++negative_;
  }
  number % 2 != 0 ? oddSum_ += number : evenSum_ += number;
  last_ = number;
}

void Functor::print() const
{
  if(counter_ == 0)
  {
    std::cout << "No Data" << std::endl;
    return;
  }
  std::cout << "Max: " << max_ << '\n'
      << "Min: " << min_ << '\n'
      << "Mean: " << std::fixed << static_cast<double>(oddSum_ + evenSum_) / counter_ << '\n'
      << "Positive: " << positive_ << '\n'
      << "Negative: " << negative_ << '\n'
      << "Odd Sum: " << oddSum_ << '\n'
      << "Even Sum: " << evenSum_ << '\n'
      << "First/Last Equal: " << (first_ == last_ ? "yes" : "no") << std::endl;
}
