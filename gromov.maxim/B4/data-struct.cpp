#include "data-struct.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "detail.hpp"

void read(const std::string & line, std::vector<DataStruct_t> & vector)
{
  std::stringstream sin(line);
  std::string key1, key2;
  std::string str;
  getline(sin, key1, ',');
  sin >> std::ws;
  getline(sin, key2, ',');
  sin >> std::ws;
  getline(sin, str);

  if(key1.empty() || key2.empty() || str.empty())
  {
    throw std::invalid_argument(std::string("Invalid data input") + "Key1 = " + key1 + " Key2 = " + key2);
  }

  vector.emplace_back(detail::getIntKeyAndCheckIt(key1), detail::getIntKeyAndCheckIt(key2), str);
}

std::ostream & operator <<(std::ostream & out, const DataStruct_t & dataStruct)
{
  return (out << dataStruct.key1 << ',' << dataStruct.key2 << ',' << dataStruct.str << '\n');
}

bool operator <(const DataStruct_t & dataStruct, const DataStruct_t & dataStruct1)
{
  if(dataStruct.key1 != dataStruct1.key1)
  {
    return dataStruct.key1 < dataStruct1.key1;
  }

  if(dataStruct.key2 != dataStruct1.key2)
  {
    return dataStruct.key2 < dataStruct1.key2;
  }
  
  return dataStruct.str.size() < dataStruct1.str.size();
}
