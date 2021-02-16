#include "triangle.hpp"
#include <iostream>

Triangle::Triangle(const point_t &center) :
  Shape(center)
{}

void Triangle::draw(std::ostream & out)
{
  out << "TRIANGLE " << "(" << center_.x << "; " << center_.y << ")" << '\n';
}
