#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include <iosfwd>

struct point_t
{
  double x, y;
};

std::istream & operator>>(std::istream & in, point_t & point);

class Shape
{
public:
  explicit Shape(const point_t & center);

  virtual ~Shape() = default;

  bool isMoreLeft(const std::shared_ptr<Shape> & shape) const;

  bool isUpper(const std::shared_ptr<Shape> & shape) const;

  virtual void draw(std::ostream & out) = 0;
  
protected:
  point_t center_;
};

#endif
