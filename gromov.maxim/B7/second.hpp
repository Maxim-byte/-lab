#ifndef SECOND_HPP
#define SECOND_HPP

#include <memory>
#include <list>
#include <iosfwd>
#include "shape.hpp"

std::istream & operator>>(std::istream & in, std::shared_ptr<Shape> & figure); 

std::ostream & operator<<(std::ostream & out, const std::shared_ptr<Shape> & shape);

void secondTask();

std::shared_ptr<Shape> shapeCreator(const std::string & typeOfShape, const point_t & point);

#endif
