#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>

struct Point
{
  int x, y;
};

struct shape_t 
{
  enum TypeOfShape
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    POLYGON
  };
  TypeOfShape type;
  std::vector<Point> points;
};

#endif
