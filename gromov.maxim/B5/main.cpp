#include <iostream>
#include "first.hpp"
#include "second.hpp"

int main(int argc, char * argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::invalid_argument("Invalid count of args!");
    }
    
    int part = atoi(argv[1]);

    if (part == 1)
    {
      firstTask();
    } else if (part == 2)
    {
      secondTask();
    }
    else
    {
      throw std::invalid_argument("Invalid task number!");
    }
    
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
