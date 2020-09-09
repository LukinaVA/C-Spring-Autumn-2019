#ifndef RectangleHPP
#define RectangleHPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &center, double width, double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t &newPoint) override;

private:
  point_t center_;
  double width_;
  double height_;
};

#endif
