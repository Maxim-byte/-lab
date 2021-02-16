#include "composite-shape.hpp"
#include <stdexcept>
#include <string>
#include <cmath>

namespace gromov
{
  CompositeShape::CompositeShape() noexcept:
    size_(0),
    capacity_(0),
    array_(nullptr)
  {}

  CompositeShape::CompositeShape(const size_t capacity_):
    size_(0),
    capacity_(capacity_),
    array_(std::make_unique<std::shared_ptr<Shape>[]>(capacity_))
  {}

  CompositeShape::CompositeShape(const CompositeShape &array):
    size_(array.size_),
    capacity_(array.capacity_),
    array_(std::make_unique<std::shared_ptr<Shape>[]>(array.capacity_))
  {
    for (size_t i = 0; i < size_; i++)
    {
      array_[i] = array.array_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape &&array) noexcept:
    size_(array.size_),
    capacity_(array.capacity_),
    array_(std::move(array.array_))
  {
    array.size_ = 0;
    array.capacity_ = 0;
  }
  
  std::shared_ptr<Shape> &CompositeShape::operator[](size_t index)
  {
    if (size_ == 0 || index > (size_ - 1))
    {
      throw std::out_of_range(std::string("CompositeShape index out of range,index = " + std::to_string(index)));
    }
    return array_[index];
  }

  CompositeShape &CompositeShape::operator=(const CompositeShape &array)
  {
    if (&array == this)
    {
      return *this;
    } 
    arrayPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(array.capacity_);
    for (size_t i = 0; i < array.size_; i++)
    {
      temp[i] = array.array_[i];
    }
    size_ = array.size_;
    capacity_ = array.capacity_;
    array_ = std::move(temp);
    return *this;
  }

  CompositeShape &CompositeShape::operator=(CompositeShape &&array) noexcept
  {
    if(&array == this)
    {
      return *this;
    }
    size_ = array.size_;
    capacity_ = array.capacity_;
    array_ = std::move(array.array_);
    array.size_ = 0;
    array.capacity_ = 0;
    return *this;
  }

  void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Shape is nullptr!");
    }
    if (capacity_ == 0)
    {
      capacity_ = 1;
      arrayPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(capacity_);
      array_ = std::move(temp);
    }
    if (capacity_ == size_)
    {
      const int coefficient = 2;
      arrayPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(capacity_ * coefficient);
      for (size_t i = 0; i < size_; i++)
      {
        temp[i] = array_[i];
      }
      capacity_ *= coefficient;
      array_ = std::move(temp);
    }
    array_[size_] = shape;
    size_++;
  }

  void CompositeShape::deleteShape(size_t index)
  {
    if (size_ == 0 || index > (size_ - 1))
    {
      throw std::out_of_range(std::string("Delete element index is wrong,index = " + std::to_string(index)));
    }
    for (size_t i = index; i < (size_ - 1); i++)
    {
      array_[i] = array_[i + 1];
    }
    array_[size_ - 1] = nullptr;
    --size_;
  }

  double CompositeShape::getArea() const noexcept
  {
    double sum_area = 0;
    for (size_t i = 0; i < size_; i++)
    {
      sum_area += array_[i]->getArea();
    }
    return sum_area;
  }

  gromov::point_t CompositeShape::getCentre() const noexcept
  {
    return getFrameRect().pos;
  }

  gromov::rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if(size_ == 0)
    {
      return rectangle_t{0, 0, {0, 0}};
    }
    rectangle_t frame = array_[0]->getFrameRect();
    double left = frame.pos.x - frame.width / 2;
    double right = frame.pos.x + frame.width / 2;
    double top = frame.pos.y + frame.height / 2;
    double lower = frame.pos.y - frame.height / 2;
    for (size_t i = 0; i < size_; i++)
    {
      frame = array_[i]->getFrameRect();
      if ((frame.pos.x - frame.width / 2) < left)
      {
        left = frame.pos.x - frame.width / 2;
      }
      if ((frame.pos.x + frame.width / 2) > right)
      {
        right = frame.pos.x + frame.width / 2;
      }
      if ((frame.pos.y + frame.height / 2) > top)
      {
        top = frame.pos.y + frame.height / 2;
      }
      if ((frame.pos.y - frame.height / 2) < lower)
      {
        lower = frame.pos.y - frame.height / 2;
      }
    }
    return {(right - left), (top - lower), {(left + (right - left) / 2), (lower + (top - lower) / 2)}};
  }

  void CompositeShape::move(const double x, const double y) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      array_[i]->move(x, y);
    }
  }

  void CompositeShape::move(const point_t &center) noexcept
  {
    const point_t currentCenter = getCentre();
    move(center.x - currentCenter.x, center.y - currentCenter.y);
  }

  void CompositeShape::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument(std::string("Coefficient must be positive,coefficient = " + std::to_string(coefficient)));
    }
    const point_t centre = getCentre(); 
    point_t shapeCentre;
    for (size_t i = 0; i < size_; i++) 
    {
      array_[i]->scale(coefficient);
      shapeCentre = array_[i]->getCentre();
      array_[i]->move((shapeCentre.x - centre.x) * (coefficient - 1), (shapeCentre.y - centre.y) * (coefficient - 1)); 
    }
  }

  size_t CompositeShape::getSize() const noexcept
  {
    return size_;
  }

  size_t CompositeShape::getCapacity() const noexcept
  {
    return capacity_;
  }

  void CompositeShape::rotate(double angle) noexcept
  {
    double angle_radian = (angle * M_PI) / 180;
    point_t center = getCentre();
    for (size_t i = 0; i < size_; i++)
    {
      point_t currentCenter = array_[i]->getCentre();
      double distanceX = currentCenter.x - center.x;
      double distanceY = currentCenter.y - center.y;
      const double dX = (distanceX * abs(cos(angle_radian))) - (distanceY * abs(sin(angle_radian)));
      const double dY = (distanceX * abs(sin(angle_radian))) + (distanceY * abs(cos(angle_radian)));
      array_[i]->move({center.x + dX,center.y + dY});
      array_[i]->rotate(angle);
    }

  }

  Matrix CompositeShape::makePartition() const
  {
    Matrix matrix;
    for(size_t i = 0; i < size_; ++i)
    {
      matrix.add(array_[i]);
    }
    return matrix;
  }

}
