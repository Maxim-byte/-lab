#include "second.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <boost/algorithm/string/trim.hpp>
#include "square.hpp"
#include "triangle.hpp"
#include "circle.hpp"

std::istream & operator>>(std::istream & in, std::shared_ptr<Shape> & figure) 
{
  in >> std::ws;
  if(in.peek() == EOF)
  {
    in.setstate(std::ios::eofbit);
    return in;
  }
  std::string typeOfShape;
  getline(in, typeOfShape, '(');
  boost::trim(typeOfShape);
  in.unget();
  point_t point;
  in >> point;
  if(!in.good())
  {
    in.setstate(std::ios::badbit);
    return in;
  }
  figure = shapeCreator(typeOfShape, point);
  if(figure == nullptr)
  {
    in.setstate(std::ios::badbit);
  }
  return in;
}

std::ostream & operator<<(std::ostream & out, const std::shared_ptr<Shape> & shape)
{
  shape->draw(out);
  return out;
}

std::shared_ptr<Shape> shapeCreator(const std::string & typeOfShape, const point_t & point)
{
  if (typeOfShape == "TRIANGLE")
  {
    return std::make_shared<Triangle>(point);
  }
  if (typeOfShape == "CIRCLE")
  {
    return std::make_shared<Circle>(point);
  }
  if (typeOfShape == "SQUARE")
  {
    return std::make_shared<Square>(point);
  }
  return nullptr;
}

void secondTask()
{
  std::list<std::shared_ptr<Shape>> list{std::istream_iterator<std::shared_ptr<Shape>>(std::cin),
    std::istream_iterator<std::shared_ptr<Shape>>()};
  if(!std::cin.eof() && !std::cin.good())
  {
    throw std::ios::failure("Fail while reading!");
  }
  std::cout << "Original:" << '\n';
  std::copy(std::begin(list), std::end(list), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Left-Right:" << '\n';
  list.sort(std::bind(&Shape::isMoreLeft, std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_1), 
    std::placeholders::_2));
  std::copy(std::begin(list), std::end(list), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Right-Left:" << '\n';
  list.reverse();

  std::copy(std::begin(list), std::end(list), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Top-Bottom:" << '\n';
  list.sort(std::bind(&Shape::isUpper, std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_1), 
    std::placeholders::_2));

  std::copy(std::begin(list), std::end(list), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Bottom-Top:" << '\n';
  list.reverse();

  std::copy(std::begin(list), std::end(list), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));
}
