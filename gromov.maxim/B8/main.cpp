#include <exception>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include "inputIterator.hpp"
#include "processingFunctor.hpp"

int main(int argc, char * argv[])
{
  try
  {
    if ((argc < 1) || (argc > 4))
    {
      throw std::invalid_argument("Invalid count of args!");
    }
    size_t lineLength = 40;
    if(argv[1] != nullptr)
    {
      if(strcmp(argv[1], "--line-width") != 0)
      {
        throw std::invalid_argument("Invalid format of args!");
      }
      lineLength = atoi(argv[2]);
      if(lineLength < 25)
      {
        throw std::invalid_argument("Invalid line length!");
      }
    }
    ProcessingFunctor functor(lineLength, std::cout);
    std::for_each(InputIterator(std::cin), InputIterator(), std::ref(functor));
    return 0;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown problem\n";
    return 2;
  }
}
