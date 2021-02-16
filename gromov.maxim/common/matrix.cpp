#include "matrix.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>
#include <numeric>

namespace gromov
{

  Matrix::Layer::Layer(layer_ptr *layer, size_t size):
    layer_(layer),
    size_(size)
  {}

  std::shared_ptr<Shape> &Matrix::Layer::operator[](size_t index)
  {
    if (index >= size_ || size_ == 0)
    {
      throw std::out_of_range(std::string("Layer index out of range,index = " + std::to_string(index)));
    }
    return layer_[index];
  }

  Matrix::Matrix() noexcept:
    matrix_(nullptr),
    layerSize_(0),
    layerCapacity_(0),
    size_(nullptr),
    capacity_(0)
  {}

  Matrix::Matrix(const Matrix &matrix) :
    matrix_(std::make_unique<std::shared_ptr<Shape>[]>(matrix.layerCapacity_)),
    layerSize_(matrix.layerSize_),
    layerCapacity_(matrix.layerCapacity_),
    size_(std::make_unique<size_t[]>(matrix.layerSize_)),
    capacity_(matrix.capacity_)
  {
    for (size_t i = 0; i < matrix.layerSize_; ++i)
    {
      size_[i] = matrix.size_[i];
    }
    for(size_t i = 0; i < capacity_ * layerSize_; ++i)
    {
      matrix_[i] = matrix.matrix_[i];
    }
  }

  Matrix &Matrix::operator=(const Matrix &matrix)
  {
    if (&matrix == this)
    {
      return *this;
    }
    matrix_ptr temp = std::make_unique<std::shared_ptr<Shape>[]>(matrix.layerCapacity_);
    std::unique_ptr<size_t[]> tempSize = std::make_unique<size_t[]>(matrix.layerCapacity_);
    for (size_t i = 0; i < matrix.layerSize_ * capacity_; i++)
    {
      temp[i] = matrix.matrix_[i];
    }
    for (size_t i = 0; i < layerSize_; ++i)
    {
      tempSize[i] = matrix.size_[i];
    }
    capacity_ = matrix.capacity_;
    matrix_ = std::move(temp);
    size_ = std::move(tempSize);
    layerSize_ = matrix.layerSize_;
    layerCapacity_ = matrix.layerCapacity_;
    return *this;
  }

  Matrix::Layer Matrix::operator[](size_t index)
  {
    if (index >= layerSize_)
    {
      throw std::out_of_range(std::string("Matrix index out of range,index = " + std::to_string(index)));
    }
    return Layer(&matrix_[capacity_ * index], size_[index]);
  }

  void Matrix::add(const std::shared_ptr<Shape> &shape)
  {
    if (!shape)
    {
      throw std::invalid_argument("Shape is nullptr!");
    }
    if (layerSize_ == 0)
    {
      addLayer();
      size_[layerSize_]++;
      matrix_[layerSize_] = shape;
      layerSize_++;
      return;
    }
    int lastObscured = -1;
    size_t count = 0;
    for (size_t i = 0; i < layerSize_; i++)
    {
      for (size_t j = 0; j < size_[i]; ++j)
      {
        if (isObscured(shape, matrix_[j + count]))
        {
          lastObscured = i;
        }
      }
      count += capacity_;
    }
    if (lastObscured < static_cast<int>(layerSize_ - 1))
    {
      if (size_[lastObscured + 1] == capacity_)
      {
        increaseLayerSize();
      }
      size_t sum = capacity_ * (lastObscured + 1);
      matrix_[sum + size_[lastObscured + 1]] = shape;
      ++size_[lastObscured + 1];
    } else
    {
      if (layerCapacity_ == layerSize_)
      {
        addLayer();
      }
      size_t sum = capacity_ * layerSize_;
      matrix_[sum] = shape;
      size_[layerSize_]++;
      ++layerSize_;
    }
  }

  size_t Matrix::getLayerSize() const noexcept
  {
    return layerSize_;
  }

  size_t Matrix::getLayerCapacity() const noexcept
  {
    return layerCapacity_;
  }

  size_t Matrix::getShapeCount(size_t layerNumber) const
  {
    if (layerNumber >= layerSize_)
    {
      throw std::out_of_range(
        std::string("Matrix invalid layer number ,layer number = " + std::to_string(layerNumber)));
    }
    return size_[layerNumber];
  }

  void Matrix::printMatrixAreas(std::ostream &out)
  {
    size_t count = 0;
    for (size_t i = 0; i < layerSize_; ++i)
    {
      for (size_t j = 0; j < size_[i]; ++j)
      {
        out << matrix_[j + count]->getArea() << ' ';
      }
      count += capacity_;
      out << '\n';
    }
  }

  void Matrix::increaseLayerSize()
  {
    const size_t coefficient = 2;
    matrix_ptr temp = std::make_unique<std::shared_ptr<Shape>[]>(capacity_ * layerCapacity_ * coefficient);
    size_t tempCount = 0, matrixCount = 0;
    for (size_t i = 0; i < layerSize_; i++)
    {
      for (size_t j = 0; j < capacity_; ++j)
      {
        temp[tempCount] = matrix_[matrixCount];
        ++tempCount;
        ++matrixCount;
      }
      tempCount += capacity_;
    }
    matrix_ = std::move(temp);
    capacity_ *= coefficient;
  }

  void Matrix::addLayer()
  {
    if (layerCapacity_ == 0)
    {
      std::unique_ptr<size_t[]> tempSize = std::make_unique<size_t[]>(1);
      matrix_ptr temp = std::make_unique<std::shared_ptr<Shape>[]>(1);
      matrix_ = std::move(temp);
      size_ = std::move(tempSize);
      capacity_ = 1;
      layerCapacity_ = 1;
      return;
    }
    const int coefficient = 2;
    matrix_ptr temp = std::make_unique<std::shared_ptr<Shape>[]>(capacity_ * layerCapacity_ * coefficient);
    std::unique_ptr<size_t[]> tempSize = std::make_unique<size_t[]>(layerCapacity_ * coefficient);
    for (size_t i = 0; i < layerSize_; ++i)
    {
      tempSize[i] = size_[i];
    }
    for(size_t i = 0; i < layerSize_ * capacity_; ++i)
    {
      temp[i] = matrix_[i];
    }
    layerCapacity_ *= coefficient;
    size_ = std::move(tempSize);
    matrix_ = std::move(temp);
  }

  bool Matrix::isObscured(const std::shared_ptr<Shape> &shape, const std::shared_ptr<Shape> &shape1)
  {
    if (shape == nullptr || shape1 == nullptr)
    {
      return false;
    }
    return ((abs(shape->getFrameRect().pos.x - shape1->getFrameRect().pos.x)
           < ((shape->getFrameRect().width / 2) + (shape1->getFrameRect().width / 2)))
             && ((abs(shape->getFrameRect().pos.y - shape1->getFrameRect().pos.y)
                 < ((shape->getFrameRect().height / 2) + (shape->getFrameRect().height / 2)))));
  }

}
