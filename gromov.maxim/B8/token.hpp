#ifndef LINE_HPP
#define LINE_HPP

#include <string>
#include <iostream>

struct token_t
{
  enum partOfText
  {
    WORD,
    NUMBER,
    DELIMITER,
    DASH,
    UNDEFINED
  };
  token_t(partOfText && partText, std::string && str):
    part(std::move(partText)),
    line(std::move(str))
  {}
  partOfText part;
  std::string line;
};

#endif
