#include "istream-guard.hpp"

IstreamGuard::IstreamGuard(std::istream & in) :
  in_(in),
  flags_(in.flags())
{} 

IstreamGuard::~IstreamGuard()
{
  in_.flags(flags_);
}
