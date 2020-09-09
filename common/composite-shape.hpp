#ifndef COMPOSITE_SHAPE
#define COMPOSITE_SHAPE

#include <memory>

#include "shape.hpp"

namespace lukina
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &other);
    CompositeShape(CompositeShape &&other);
    CompositeShape(Shape::ptr shape);

    ~CompositeShape() = default;

    CompositeShape &operator =(const CompositeShape &other);
    CompositeShape &operator =(CompositeShape &&other);
    Shape::ptr operator [](size_t index) const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &newPoint) override;
    void scale(double coefficient) override;
    void rotate(double degrees) override;
    void add(Shape::ptr shape);
    void remove(size_t index);
    size_t getCount() const;
    void printInfo() const override;

  private:
    size_t count_;
    Shape::arrayPtr figures_;
  };
}

#endif
