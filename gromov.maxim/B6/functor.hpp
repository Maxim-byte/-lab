#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <ctime>

class Functor
{
public:
  Functor();

  void operator()(int number);

  void print() const;
private:
  int max_;

  int min_;

  size_t counter_;

  size_t positive_;

  size_t negative_;

  long long oddSum_;

  long long evenSum_;

  int first_;
  
  int last_;
};

#endif
