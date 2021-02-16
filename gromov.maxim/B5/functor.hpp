#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <vector>
#include <iosfwd>
#include "shape.hpp"

class SumShapesCategories 
{
  public:

    SumShapesCategories();

    size_t getTriangleAmount();

    size_t getSquareAmount();

    size_t getRectangleAmount();

    size_t getAmountOfTops();

    void operator()(const std::vector<shape_t> & shapes);

    void print(std::ostream & out);
  private:
    size_t triangleAmount_;
    size_t squareAmount_;
    size_t rectangleAmount_; 
    size_t amountOfTops_;
};

#endif
