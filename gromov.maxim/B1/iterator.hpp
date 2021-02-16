#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <forward_list>
#include <vector>

template <class container> class IndexAccess
{
  public:
  static size_t begin(const container &)
  {
    return 0;
  }

  static size_t end(const container & collection)
  {
    return collection.size();
  }

  static typename container::reference element(container & collection, size_t index)
  {
    return collection[index];
  }

  static size_t next(size_t index)
  {
    return ++index;
  }
};

template <class container> class AtAccess
{
  public:
  static size_t begin(const container &)
  {
    return 0;
  }

  static size_t end(const container & collection)
  {
    return collection.size();
  }

  static typename container::reference element(container & collection, size_t index)
  {
    return collection.at(index);
  }

  static size_t next (size_t index)
  {
    return ++index;
  }
};

template <class container> class Iterator
{
public:
  using iterator = typename container::iterator;

  static iterator begin(container & collection)
  {
    return collection.begin();
  }

  static iterator end(container & collection)
  {
    return collection.end();
  }

  static typename container::reference element(container &, iterator & iterator)
  {
    return *iterator;
  }

  static iterator next(iterator & iterator)
  {
    return std::next(iterator);
  }
};

#endif
