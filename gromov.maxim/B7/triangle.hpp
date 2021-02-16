#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  explicit Triangle(const point_t & center);
  
  void draw(std::ostream & out) override;
};

#endif
