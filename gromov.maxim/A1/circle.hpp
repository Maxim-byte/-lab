#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(double radius, const point_t& position);
  void move(const point_t& position) override;
  void move(const double x,const double y) override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  double getRadius() const;
  point_t getCentre() const;
private:
  double radius_;
  point_t position_;
};

#endif
