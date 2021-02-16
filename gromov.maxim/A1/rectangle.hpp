#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include"shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t& position, double width, double height);
  void move(const point_t& position) override;
  void move(const double x, const double y) override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  double getWidth() const;
  double getHeight() const;
  point_t getPosition() const;
private:
  double width_, height_;
  point_t position_;
};

#endif
