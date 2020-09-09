#include "circle.hpp"

#include <iostream>
#include <cmath>
#include <stdexcept>

lukina::Circle::Circle(const point_t &center, double radius) :
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("Radius must be positive!");
  }
}

double lukina::Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

lukina::rectangle_t lukina::Circle::getFrameRect() const
{
  return {center_, radius_ * 2, radius_ * 2};
}

void lukina::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void lukina::Circle::move(const point_t &newPoint)
{
  center_ = newPoint;
}

void lukina::Circle::scale(double coefficient)
{
  if (coefficient <= 0.0)
  {
      throw std::invalid_argument("Coefficient should be positive!");
  }
  else
  {
    radius_ *= coefficient;
  }
}

void lukina::Circle::rotate(double)
{ }

void lukina::Circle::printInfo() const
{
  std::cout << "CIRCLE" << std::endl;
  std::cout << "Center: " << center_.x << ", " << center_.y << std::endl;
  std::cout << "Radius: " << radius_ << std::endl;
  std::cout << "Circle area: " << getArea() << std::endl;
  std::cout << "Frame rectangle:" << std::endl;
  std::cout << "-Center: " << getFrameRect().pos.x << ", " << getFrameRect().pos.y << std::endl;
  std::cout << "-Width: " << getFrameRect().width << std::endl;
  std::cout << "-Height: " << getFrameRect().height << std::endl;
  std::cout << std::endl;
}
