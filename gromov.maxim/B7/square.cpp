#include "square.hpp"
#include <iostream>

Square::Square(const point_t &point) :
  Shape(point)
{}

void Square::draw(std::ostream & out)
{
  out << "SQUARE " << "(" << center_.x << "; " << center_.y << ")" << '\n';
}
