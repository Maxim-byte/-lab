#ifndef INPUTITERATOR_HPP
#define INPUTITERATOR_HPP

#include <iterator>
#include <iosfwd>
#include "token.hpp"

class InputIterator : public std::iterator<std::input_iterator_tag, token_t>
{
public:
  explicit InputIterator(std::istream & in);

  InputIterator();

  token_t& operator*();

  token_t* operator->();

  InputIterator& operator++();

  InputIterator&  operator++(int);

  bool operator== (const InputIterator& it) const;

  bool operator!= (const InputIterator& it) const;

private:
  void read();

  void addValidateNumber();

  void addValidateWord();

  void addValidateDash();

  std::istream * in_;
  token_t token_;
  bool state_;
};


#endif
