#include "circle.hpp"
#include <iostream>

Circle::Circle(const point_t & center):
  Shape(center)
{}

void Circle::draw(std::ostream & out)
{
  out << "CIRCLE " << "(" << center_.x << "; " <<  center_.y << ")" << '\n';
}
