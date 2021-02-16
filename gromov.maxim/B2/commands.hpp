#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <sstream>
#include "queueWithPriority.hpp"

template <class T>
void add(QueueWithPriority<T> & queue, std::stringstream & sin, std::ostream & out)
{
  std::string priority;
  sin >> priority;
  std::string element, buffer;
  sin >> element;
  
  if(!sin.eof())
  {
    std::getline(sin, buffer);
  }
  
  element += buffer;

  if(priority.empty() || element.empty())
  {
    out << "<INVALID COMMAND>" << '\n';
    return;
  }

  typename QueueWithPriority<T>::elementPriority elementPriority;

  if(priority == "high")
  {
    elementPriority = QueueWithPriority<T>::elementPriority::HIGH;
  } else if(priority == "normal")
  {
    elementPriority = QueueWithPriority<T>::elementPriority::NORMAL;
  } else if(priority == "low")
  {
    elementPriority = QueueWithPriority<T>::elementPriority::LOW;
  }
  else
  {
    out << "<INVALID COMMAND>" << '\n';;
    return;
  }
  
  queue.putElementToQueue(element, elementPriority);
}

template <class T>
void get(QueueWithPriority<T> & queue, std::ostream & out)
{
  if(queue.isEmpty())
  {
    out << "<EMPTY>" << '\n';
    return;
  }
  out << queue.getElementFromQueue() << '\n';
  queue.popElementFromQueue();
}

template <class T>
void accelerate(QueueWithPriority<T> & queue)
{
  queue.accelerate();
}

#endif
