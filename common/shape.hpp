#ifndef ShapeHPP
#define ShapeHPP

#include <memory>

#include "base-types.hpp"

namespace lukina
{
  class Shape
  {
  public:
    using ptr = std::shared_ptr<Shape>;
    using arrayPtr = std::unique_ptr<ptr[]>;

    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t &newPoint) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void rotate(double degrees) = 0;
    virtual void printInfo() const = 0;

    int intersection(const ptr shape) const;
  };
}

#endif
