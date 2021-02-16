#ifndef FOURTH_HPP
#define FOURTH_HPP

#include <stdexcept>
#include <vector>
#include <random>
#include "print.hpp"
#include "sort.hpp"
#include "detail.hpp"

void fillRandom(double * array, int size)
{
  std::uniform_real_distribution<double> distr(-1, 1);
  std::default_random_engine re;
  for(auto i = 0; i < size; ++i)
  {
    array[i] = distr(re);
  }
}

void fourthTask(const char * sortingType, size_t size)
{
  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  print(vector);
  collectionSort<IndexAccess>(vector, detail::getCompare<std::vector<double>::value_type>(sortingType));
  print(vector);
}

#endif
