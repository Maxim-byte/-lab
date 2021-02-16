#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <algorithm>
#include "data-struct.hpp"

int main()
{
  try
  {
    std::string line;
    std::vector<DataStruct_t> vector;
    while (getline(std::cin, line))
    {
      if (!std::cin.eof() && !std::cin.good())
      {
        throw std::ios_base::failure("Fail while reading data");
      }
      read(line, vector);
    }
    std::sort(vector.begin(), vector.end());
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct_t>(std::cout));
    return 0;
  }
  catch (std::exception & exception)
  {
    std::cerr << exception.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
    return 2;
  }
}
