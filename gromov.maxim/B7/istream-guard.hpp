#ifndef ISTREAM_WRAPPER
#define ISTREAM_WRAPPER

#include <istream>

class IstreamGuard
{
  public:
  
  explicit IstreamGuard(std::istream & in);

  ~IstreamGuard();

  private:
  std::istream & in_;
  std::ios_base::fmtflags flags_;
};

#endif
