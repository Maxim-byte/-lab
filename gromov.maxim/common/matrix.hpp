#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <ctime>
#include <iostream>
#include <memory>
#include "shape.hpp"

namespace gromov
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      friend class Matrix;

      ~Layer() = default;

      std::shared_ptr<Shape> &operator[](size_t index);

    private:

      using layer_ptr = std::shared_ptr<Shape>;

      Layer(layer_ptr *layer, size_t size);

      Layer(const Layer & layer) = default;

      Layer(Layer && layer) = default;

      Layer &operator=(Layer && layer) = default;

      Layer &operator=(Layer & layer) = default;

      layer_ptr *layer_;
      size_t size_;
    };

    Matrix() noexcept;

    Matrix(const Matrix &matrix);

    Matrix(Matrix &&matrix) = default;

    ~Matrix() = default;

    Matrix &operator=(const Matrix &matrix);

    Matrix &operator=(Matrix &&matrix) = default;

    Layer operator[](size_t index);

    void add(const std::shared_ptr<Shape> &shape);

    size_t getLayerSize() const noexcept;

    size_t getLayerCapacity() const noexcept;

    size_t getShapeCount(size_t layerNumber) const;

    void printMatrixAreas(std::ostream &out);

  private:
    void increaseLayerSize();

    void addLayer();

    using matrix_ptr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    matrix_ptr matrix_;
    size_t layerSize_;
    size_t layerCapacity_;
    std::unique_ptr<size_t[]> size_;
    size_t capacity_;
    static bool isObscured(const std::shared_ptr<Shape> &shape, const std::shared_ptr<Shape> &shape1);
  };
}

#endif
