#ifndef QUEUEWITHPRIORITY_HPP
#define QUEUEWITHPRIORITY_HPP

#include <list>
#include <stdexcept>

template <typename T>
class QueueWithPriority
{
public:

  using elementPriority = enum {LOW, NORMAL, HIGH};

  void putElementToQueue(const T & element, elementPriority priority);

  T getElementFromQueue();

  void popElementFromQueue();
  
  bool isEmpty() noexcept;

  void accelerate();

private:
  std::list<T> highPriority_;
  std::list<T> normalPriority_;
  std::list<T> lowPriority_;
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T &element, elementPriority priority)
{
  if(priority == LOW)
  {
    lowPriority_.push_front(element);
  }
  if(priority == HIGH)
  {
    highPriority_.push_front(element);
  }
  if(priority == NORMAL)
  {
    normalPriority_.push_front(element);
  }
}

template<typename T>
void QueueWithPriority<T>::popElementFromQueue() 
{
  if(!highPriority_.empty())
  {
    highPriority_.pop_back();
    return;
  }

  if(!normalPriority_.empty())
  {
    normalPriority_.pop_back();
    return;
  }
  
  if(!lowPriority_.empty())
  {
    lowPriority_.pop_back();
    return;
  }
  throw std::logic_error("Queue underflow!");
}

template<typename T>
T QueueWithPriority<T>::getElementFromQueue()
{
  if(!highPriority_.empty())
  {
    return highPriority_.back();
  }

  if(!normalPriority_.empty())
  {
    return normalPriority_.back();
  }
  
  if(!lowPriority_.empty())
  {
    return lowPriority_.back();
  }
  throw std::logic_error("Queue underflow!");
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  if(!lowPriority_.empty())
  {
    highPriority_.splice(highPriority_.begin(), lowPriority_);
  }
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() noexcept
{
  return lowPriority_.empty() && highPriority_.empty() && normalPriority_.empty();
}

#endif
