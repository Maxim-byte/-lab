#include <iostream>
#include <string>
#include <cstring>
#include "first.hpp"
#include "second.hpp"
#include "third.hpp"
#include "fourth.hpp"

int main(int argc, char * argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::invalid_argument("Invalid count of args!");
    }

    for(const auto & ch : std::string(argv[1]))
    {
      if (ch < '0' || ch > '9')
      {
        throw std::invalid_argument("Invalid task number");
      }
    }
    
    int part = atoi(argv[1]);

    if(part < 1 || part > 4)
    {
      throw std::invalid_argument("Invalid task number");
    }

    if (part == 1)
    {
      if(argc != 3)
      {
        throw std::invalid_argument("Invalid arguments number");
      }
      firstTask(argv[2]);
    } else if (part == 2)
    {
      if(argc != 3)
      {
        throw std::invalid_argument("Invalid arguments number");
      }
      secondTask(argv[2]);
    } else if (part == 3)
    {
      if(argc != 2)
      {
        throw std::invalid_argument("Invalid arguments number");
      }
      thirdTask();
    } else if (part == 4)
    {
      if(argc != 4)
      {
        throw std::invalid_argument("Invalid arguments number");
      }
      for(const auto & ch : std::string(argv[3]))
      {
        if (ch < '0' || ch > '9')
        {
          throw std::invalid_argument("Invalid task number");
        }
      }
      fourthTask(argv[2], atoi(argv[3]));
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
