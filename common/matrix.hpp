#ifndef MATRIX_A4
#define MATRIX_A4

#include <memory>
#include "shape.hpp"

namespace lukina
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      Layer(Shape::ptr *arr, size_t size);
      Shape::ptr operator [](size_t index) const;
      size_t getSize() const;

    private:
      size_t size_;
      Shape::arrayPtr figures_;
    };

    Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other);

    ~Matrix() = default;

    Matrix &operator =(const Matrix &other);
    Matrix &operator =(Matrix &&other);
    Layer operator [](size_t row) const;

    void add(Shape::ptr shape, size_t row);
    size_t getRows() const;
    size_t getNumberOfFigures() const;
    void printInfo() const;

  private:
    size_t rows_;
    std::unique_ptr<size_t[]> columns_;
    Shape::arrayPtr figures_;
    size_t numberOfFigures;
  };
}

#endif
