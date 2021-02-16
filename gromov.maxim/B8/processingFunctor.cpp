#include "processingFunctor.hpp"
#include <ostream>

ProcessingFunctor::ProcessingFunctor(size_t lineLength, std::ostream & out):
  lineLength_(lineLength),
  resultString_(),
  out_(out)
{}

ProcessingFunctor::~ProcessingFunctor()
{
  if(!resultString_.empty())
  {
    out_ << resultString_ << '\n';
  }
}

void ProcessingFunctor::operator()(token_t &token)
{
  if(token.part == token_t::WORD  || token.part == token_t::NUMBER)
  {
    if((resultString_.size() + token.line.size() + 1) > lineLength_)
    {
      out_ << resultString_ << '\n';
      resultString_.clear();
    }
    else if(!resultString_.empty())
    {
      resultString_ += " ";
    }
    resultString_ += token.line;
  }
  else
  {
    if((token.part == token_t::DASH && ((resultString_.size() + 4) > lineLength_))
       || (((resultString_.size() + 1) > lineLength_)))
    {
      size_t lastWhiteSpace = resultString_.find_last_of(' ');
      size_t amountOddChars = resultString_.size() - lastWhiteSpace;
      std::string temp = resultString_.substr(lastWhiteSpace, amountOddChars);
      resultString_.erase(lastWhiteSpace, amountOddChars);
      temp.erase(0, 1);
      out_ << resultString_ << '\n';
      resultString_ = temp;
    }
    if(token.part == token_t::DASH)
    {
      resultString_ += " ";
    }
    resultString_ += token.line;
  }
}
