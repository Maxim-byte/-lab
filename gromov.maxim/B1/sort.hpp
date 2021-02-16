#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <forward_list>
#include <functional>
#include <utility>
#include "iterator.hpp"
#include "detail.hpp"

template <template <typename> class options, typename T>
void collectionSort(T & collection, std::function<bool(typename T::value_type, typename T::value_type)> compare)
{
  const auto begin = options<T>::begin(collection);
  const auto end = options<T>::end(collection);

  for (auto i = begin; i != end; ++i)
  {
    auto temp = i;
    for (auto j = options<T>::next(i); j != end; ++j)
    {
      if (compare(options<T>::element(collection, j), options<T>::element(collection, temp)))
      {
        temp = j;
      }
    }
    if (temp != i)
    {
      std::swap(options<T>::element(collection, temp), options<T>::element(collection, i));
    }
  }
}

#endif
