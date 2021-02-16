#include "shape.hpp"
#include <iostream>
#include "istream-guard.hpp"

Shape::Shape(const point_t &center):
  center_(center)
{}

bool Shape::isMoreLeft(const std::shared_ptr<Shape> & shape) const
{
  return center_.x < shape->center_.x;
}

bool Shape::isUpper(const std::shared_ptr<Shape> &shape) const
{
  return center_.y > shape->center_.y;
}

std::istream& skipBlank(std::istream& in)
{
  while(std::isblank(in.peek()))
  {
    in.get();
  }
  return in;
}

std::istream & operator>>(std::istream & in, point_t & point)
{
  IstreamGuard inStream(in);
  in.unsetf(std::ios_base::skipws);
  char openBracket = '\0', delimiter = '\0', closeBracket = '\0';
  in >> skipBlank >> openBracket >> skipBlank >> point.x >> skipBlank >> delimiter >> skipBlank >> point.y
      >> skipBlank >> closeBracket;
  if(openBracket != '(' || delimiter != ';' || closeBracket != ')' || !in.good())
  {
    in.clear();
    in.setstate(std::ios::badbit);
  }
  return in;
}
