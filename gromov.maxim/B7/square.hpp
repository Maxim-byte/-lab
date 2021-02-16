#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "shape.hpp"

class Square : public Shape
{
public:
  explicit Square(const point_t & point);
    
  void draw(std::ostream & out) override;
};

#endif
