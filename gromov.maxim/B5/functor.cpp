#include "functor.hpp"
#include <algorithm>
#include <iostream>
#include "processing-data.hpp"

SumShapesCategories::SumShapesCategories():
  triangleAmount_(0),
  squareAmount_(0),
  rectangleAmount_(0),
  amountOfTops_(0)
{}

void SumShapesCategories::operator()(const std::vector<shape_t> & shapes)
{
  std::for_each(shapes.begin(), shapes.end(), [&](const shape_t & shape)
  {
    if (shape.type == shape_t::TRIANGLE)
    {
      ++triangleAmount_;
    }
    if (shape.type == shape_t::SQUARE)
    {
      ++squareAmount_;
    }
    if (shape.type == shape_t::RECTANGLE)
    {
      ++rectangleAmount_;
    }
    amountOfTops_ += shape.points.size();
  });
  rectangleAmount_ += squareAmount_;
}

void SumShapesCategories::print(std::ostream & out)
{
  out << "Vertices: " << amountOfTops_ << '\n' << "Triangles: " << triangleAmount_ 
    << '\n' << "Squares: " << squareAmount_ << '\n'
      << "Rectangles: " << rectangleAmount_ << '\n' << "Points: ";
}

size_t SumShapesCategories::getTriangleAmount()
{
  return triangleAmount_;
}

size_t SumShapesCategories::getSquareAmount()
{
  return squareAmount_;
}

size_t SumShapesCategories::getRectangleAmount()
{
  return rectangleAmount_;
}

size_t SumShapesCategories::getAmountOfTops()
{
  return amountOfTops_;
}
