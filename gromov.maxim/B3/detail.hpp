#include <string>
#include <iosfwd>

namespace detail
{
  std::string readCheckedNumber(std::istream & sin);

  std::string readCheckedName(std::istream & sin);

  std::string readCheckedMarkName(std::istream & sin);

  int getIntFromStepByModificationStep(std::string & step);

  void print(const std::string& str);
}
