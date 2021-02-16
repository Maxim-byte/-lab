#include "inputIterator.hpp"
#include <istream>

const size_t DASH_LENGTH = 3;
const size_t MAX_LENGTH = 20;

InputIterator::InputIterator(std::istream &in) :
  in_(&in),
  token_({token_t::UNDEFINED, ""}),
  state_(true)
{
  read();
}

InputIterator::InputIterator() :
  in_(nullptr),
  token_({token_t::UNDEFINED, ""}),
  state_(false)
{}


token_t &InputIterator::operator*()
{
  return token_;
}

token_t *InputIterator::operator->()
{
  return &token_;
}

InputIterator &InputIterator::operator++()
{
  read();
  return *this;
}

InputIterator &InputIterator::operator++(int)
{
  auto returnValue = this;
  read();
  return *returnValue;
}

bool InputIterator::operator==(const InputIterator &it) const
{
  return (state_ == it.state_) && (!state_ || in_ == it.in_);
}

bool InputIterator::operator!=(const InputIterator &it) const
{
  return !((state_ == it.state_) && (!state_ || in_ == it.in_));
}

void InputIterator::read()
{
  (*in_) >> std::ws;
  char first = in_->get();
  char second = in_->peek();
  if ((*in_).fail())
  {
    state_ = false;
    return;
  }

  if (isalpha(first))
  {
    in_->unget();
    addValidateWord();
  } else if (isdigit(first) || ((first == '-' || first == '+') && isdigit(second)))
  {
    in_->unget();
    addValidateNumber();
  } else if (std::ispunct(first))
  {
    if (token_.line.empty())
    {
      throw std::invalid_argument("With punctuation begin");
    }
    if (token_.part == token_t::DELIMITER || token_.part == token_t::DASH)
    {
      if (token_.line == "," && first == '-')
      {
        in_->unget();
        addValidateDash();
        token_ = std::move(token_t(token_t::DASH, "---"));
        return;
      }
      else
      {
        throw std::invalid_argument("Punctuation nearly");
      }
    }
    if (first == '-')
    {
      in_->unget();
      addValidateDash();
      token_ = std::move(token_t(token_t::DASH, "---"));
    } else
    {
      std::string temp;
      temp.push_back(first);
      token_ = std::move(token_t(token_t::DELIMITER, std::move(temp)));
    }
  }
}

void InputIterator::addValidateNumber()
{
  std::string tmp;
  size_t dotCount = 0;
  tmp.push_back(in_->get());
  while (isdigit(in_->peek()) || in_->peek() == '.')
  {
    if (tmp.length() >= MAX_LENGTH)
    {
      throw std::invalid_argument("Invalid digit length");
    }
    char ch = in_->get();
    if (ch == '.')
    {
      ++dotCount;
      if (dotCount > 1)
      {
        throw std::invalid_argument("Invalid double");
      }
    }
    tmp.push_back(ch);
  }
  token_ = std::move(token_t(token_t::NUMBER, std::move(tmp)));
}

void InputIterator::addValidateWord()
{
  std::string tmp;
  tmp.push_back(in_->get());
  while (isalpha(in_->peek()) || in_->peek() == '-')
  {
    char ch = in_->get();
    if (tmp.length() >= MAX_LENGTH)
    {
      throw std::invalid_argument("Invalid length of word");
    }
    if (ch == '-' && in_->peek() == '-')
    {
      throw std::invalid_argument("Invalid word -");
    }
    tmp.push_back(ch);
  }
  token_ = std::move(token_t{token_t::WORD, std::move(tmp)});
}

void InputIterator::addValidateDash()
{
  size_t dashCount = 0;
  while (in_->peek() == '-')
  {
    in_->get();
    ++dashCount;
  }
  if (dashCount != DASH_LENGTH)
  {
    throw std::invalid_argument("Invalid count of dash");
  }
}
