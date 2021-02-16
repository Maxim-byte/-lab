#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <iterator>
#include "functor.hpp"

int main()
{
  try
  {
    Functor functor;
    std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::ref(functor));
    if (!std::cin.good() && !std::cin.eof())
    {
      throw std::ios_base::failure("Fail while reading data!");
    }
    functor.print();
    return 0;
  }
  catch (std::exception & exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem" << '\n';
    return 2;
  }
}
