#include <string>
#include <stdexcept>

namespace detail
{
  int getIntKeyAndCheckIt(const std::string & key)
  {
    for (const auto &ch : key)
    {
      if(!isdigit(ch) && ch != '-')
      {
        throw std::invalid_argument(std::string("Invalid key, not only digit, key = ") + key);
      }
    }

    int keyInt = stoi(key);
    
    if(keyInt < -5 || keyInt > 5)
    {
      throw std::out_of_range(std::string("Invalid key, key = ") + key);
    }
    return keyInt;
  }
}
