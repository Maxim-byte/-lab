#ifndef PROCESSINGFUNCTOR_HPP
#define PROCESSINGFUNCTOR_HPP

#include "token.hpp"
#include <iosfwd>
#include <string>

class ProcessingFunctor
{
public:
  ProcessingFunctor(size_t lineLength, std::ostream & out);

  ~ProcessingFunctor();

  void operator()(token_t & token);

private:
  const size_t lineLength_;
  std::string resultString_;
  std::ostream & out_;

};


#endif
