#ifndef PROCESSING_DATA_HPP
#define PROCESSING_DATA_HPP

#include <vector>
#include <iosfwd>
#include "shape.hpp"

std::istream & operator>>(std::istream & in, Point & point);

std::istream & operator>>(std::istream & in, shape_t& shape);

void deletePentagon(std::vector<shape_t> & shapes);

void sort(std::vector<shape_t> & shapes);

bool isSquare(const std::vector<Point> & shape);

bool isRectangle(const std::vector<Point> & shape);

bool isTriangle(const std::vector<Point> & shape);

std::vector<Point> getPointsFromShapes(const std::vector<shape_t> & shapes);

std::ostream &  operator<< (std::ostream & out, const Point & point);

#endif
