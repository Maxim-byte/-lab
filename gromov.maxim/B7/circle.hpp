#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  explicit Circle(const point_t & center);
  
  void draw(std::ostream & out) override;
};

#endif
