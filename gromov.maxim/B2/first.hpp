#ifndef FIRST_HPP
#define FIRST_HPP

#include <iostream>
#include <stdexcept>
#include <sstream>
#include "queueWithPriority.hpp"
#include "commands.hpp"

void firstTask()
{
  std::string line;
  QueueWithPriority<std::string> queue;
  
  while(getline(std::cin, line))
  {
    if(!std::cin.good() && !std::cin.eof())
    {
      throw std::ios_base::failure("Fail with reading data!");
    }

    std::stringstream sin(line);
    std::string command;
    sin >> command;

    if(command == "add")
    {
      add(queue, sin, std::cout);
    } else if(command == "get")
    {
      get(queue, std::cout);
    } else if(command == "accelerate")
    {
      accelerate(queue);
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << "\n";
    }
    
  }
}

#endif
