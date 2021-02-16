#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include <ctime>
#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace gromov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape() noexcept;

    CompositeShape(const size_t capacity_);

    CompositeShape(const CompositeShape &array);

    CompositeShape(CompositeShape &&array) noexcept;

    std::shared_ptr<Shape> &operator[](size_t index);

    CompositeShape &operator=(const CompositeShape &array);

    CompositeShape &operator=(CompositeShape &&array) noexcept;

    void addShape(const std::shared_ptr<Shape> &shape);

    void deleteShape(size_t index);

    double getArea() const noexcept override;

    point_t getCentre() const noexcept override;

    size_t getSize() const noexcept;

    size_t getCapacity() const noexcept;

    gromov::rectangle_t getFrameRect() const noexcept override;

    void move(const double x, const double y) noexcept override;

    void move(const point_t &center) noexcept override;

    void scale(const double coefficient) override;

    void rotate(const double angle = 0) noexcept override;

    Matrix makePartition() const;

  private:
    using arrayPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t size_;
    size_t capacity_;
    arrayPtr array_;
  };
}

#endif
