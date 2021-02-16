#include <cmath>
#include "base-types.hpp"
 
namespace detail
{
  inline double getDistance(const gromov::point_t &top, const gromov::point_t &top1)
  {
    return std::sqrt((top1.x - top.x) * (top1.x - top.x) + (top1.y - top.y) * (top1.y - top.y));
  }
}
