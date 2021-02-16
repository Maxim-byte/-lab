#ifndef SECOND_HPP
#define SECOND_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <exception>
#include <memory>

void secondTask(const char * file)
{
  const size_t size = 64;
  
  std::ifstream fin(file);

  if(!fin.is_open())
  {
    throw std::ios_base::failure("File cannot be open!");
  }

  if(fin.peek() == EOF)
  {
    return;
  }

  std::unique_ptr<char[], decltype(std::free) *> arr(static_cast<char *>(malloc(size)), std::free);

  size_t overSize = size;
  size_t count = 0;

  while(fin >> arr[count])
  {
    ++count;
    if(count == overSize)
    {
      overSize += size;
      std::unique_ptr<char[], decltype(std::free) *> temp(static_cast<char *>(realloc(arr.get(), overSize)), std::free);
      if(temp == nullptr) 
      {
        throw std::bad_alloc();
      }
      arr.release();
      std::swap(arr, temp);
    }
  }

  if(!fin.good() && !fin.eof())
  {
    throw std::ios_base::failure("Fail while reading");
  }

  fin.close();

  std::vector<char> vector(arr.get(), arr.get() + count);

  for(const auto & el :vector)
  {
    std::cout << el;
  }

  std::cout << '\n';

  if(fin.is_open())
  {
    throw std::ios_base::failure("Fail with closing!");
  }
}

#endif
