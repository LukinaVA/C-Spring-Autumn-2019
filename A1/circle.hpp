#ifndef CircleHPP
#define CircleHPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &center, double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t &newPoint) override;

private:
  point_t center_;
  double radius_;
};

#endif
