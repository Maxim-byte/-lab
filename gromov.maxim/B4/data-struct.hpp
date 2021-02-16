#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iosfwd>
#include <vector>
#include <string>

struct DataStruct_t
{
  DataStruct_t(int key, int secondKey, const std::string & string):
    key1(key),
    key2(secondKey),
    str(string)
  {}
  int key1;
  int key2;
  std::string str;
};

void read(const std::string & line, std::vector<DataStruct_t> & vector);

std::ostream & operator <<(std::ostream & out, const DataStruct_t & dataStruct);

bool operator <(const DataStruct_t & dataStruct, const DataStruct_t & dataStruct1);

int checkKey(std::string & key);

#endif
