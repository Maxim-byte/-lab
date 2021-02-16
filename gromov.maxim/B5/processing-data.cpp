#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include "processing-data.hpp"

const size_t TRIANGLE_TOPS = 3;
const size_t SQUARE_TOPS = 4;
const size_t PENTAGON_TOPS = 5;

std::istream & operator>>(std::istream & in, shape_t & shape)
{
  size_t tops = 0;
  in >> std::ws >> tops;
  if(in.eof())
  {
    return in;
  }
  if(!in.good())
  {
    throw std::ios::failure("Fail while reading!");
  }  
  if(tops < TRIANGLE_TOPS)
  {
    throw std::invalid_argument("Invalid count of shapes!");
  }
  std::string str;
  getline(in, str);
  std::istringstream sin(str);
  shape.points = {std::istream_iterator<Point>(sin), std::istream_iterator<Point>()};
  if(shape.points.size() != tops)
  {
    throw std::invalid_argument("Invalid count of shapes!");
  }
  if (isTriangle(shape.points))
  {
    shape.type = shape_t::TRIANGLE;
  } else if (isSquare(shape.points))
  {
    shape.type = shape_t::SQUARE;
  } else if (isRectangle(shape.points))
  {
    shape.type = shape_t::RECTANGLE;
  }
  else
  {
    shape.type = shape_t::POLYGON;
  }
  return in;
}

std::istream & operator>>(std::istream & in, Point & point)
{
  char openBracket = '\0', delimiter = '\0', closeBracket = '\0';
  in >> std::ws >> openBracket >> point.x >> delimiter >> point.y >> closeBracket;
  if(in.eof())
  {
    return in;
  }
  if(openBracket != '(' || delimiter != ';' || closeBracket != ')')
  {
    throw std::invalid_argument("Invalid format");
  }
  if(!in.eof() && !in.good())
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool isSquare(const std::vector<Point> & shape)
{
  if (shape.size() == SQUARE_TOPS)
  {
    return (sqrt(pow((shape[0].x - shape[1].x), 2) + pow(((shape[0].y - shape[1].y)), 2)) ==
        sqrt(pow((shape[0].x - shape[3].x), 2) + pow(((shape[0].y - shape[3].y)), 2)));
  }
  return false;
} 

bool isRectangle(const std::vector<Point> & shape)
{
  if (shape.size() == SQUARE_TOPS)
  {
    return (sqrt(pow((shape[0].x - shape[2].x), 2) + pow(((shape[0].y - shape[2].y)), 2)) ==
        sqrt(pow((shape[1].x - shape[3].x), 2) + pow(((shape[1].y - shape[3].y)), 2)));
  }
  return false;
}

bool isTriangle(const std::vector<Point> & shape)
{
  return shape.size() == TRIANGLE_TOPS;
}

void deletePentagon(std::vector<shape_t> & shapes)
{
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](const shape_t & shape){
    return shape.points.size() == PENTAGON_TOPS;
  }), shapes.end());
}

void sort(std::vector<shape_t> & shapes)
{
  std::sort(shapes.begin(), shapes.end(), [](const shape_t &shape, const shape_t &shape1)
  {
    if(shape.type == shape1.type)
    {
      return shape.points[0].x < shape1.points[0].x;
    }
    return shape.type < shape1.type;
  });
}

std::vector<Point> getPointsFromShapes(const std::vector<shape_t> & shapes)
{
  std::vector<Point> points;
  points.reserve(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(), [](const shape_t & shape)
  {
    return shape.points[0];
  });
  return points;
}

std::ostream & operator<< (std::ostream & out, const Point & point)
{
  return out << " (" << point.x << ';' << point.y << ')';
}

