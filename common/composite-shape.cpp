#include "composite-shape.hpp"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <stdexcept>

lukina::CompositeShape::CompositeShape() :
  count_(0)
{ }

lukina::CompositeShape::CompositeShape(const CompositeShape &other) :
  count_(other.count_),
  figures_(std::make_unique<ptr[]>(other.count_))
{
  for (size_t i = 0; i < count_; i++)
  {
    figures_[i] = other.figures_[i];
  }
}

lukina::CompositeShape::CompositeShape(CompositeShape &&other) :
  count_(other.count_),
  figures_(std::move(other.figures_))
{ }

lukina::CompositeShape::CompositeShape(Shape::ptr shape) :
  count_(1),
  figures_(std::make_unique<Shape::ptr[]>(1))
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape can't be empty");
  }
  figures_[0] = shape;
}

lukina::CompositeShape &lukina::CompositeShape::operator =(const CompositeShape &other)
{
  if (this != &other)
  {
    count_ = other.count_;
    Shape::arrayPtr arr(std::make_unique<Shape::ptr[]>(other.count_));

    for (size_t i = 0; i < count_; i++)
    {
      arr[i] = other.figures_[i];
    }

    figures_.swap(arr);
  }

  return *this;
}

lukina::CompositeShape &lukina::CompositeShape::operator =(CompositeShape &&other)
{
  if (this != &other)
  {
    count_ = other.count_;
    figures_ = std::move(other.figures_);
  }

  return *this;
}

lukina::Shape::ptr lukina::CompositeShape::operator [](size_t index) const
{
  if (index >= count_)
  {
    throw std::invalid_argument("Index is out of array");
  }

  return (figures_[index]);
}

double lukina::CompositeShape::getArea() const
{
  double totalArea = 0;

  for (size_t i = 0; i < count_; i++)
  {
    totalArea += figures_[i]->getArea();
  }

  return totalArea;
}

lukina::rectangle_t lukina::CompositeShape::getFrameRect() const
{
  double maxX = 0;
  double maxY = 0;
  double minX = 0;
  double minY = 0;

  if (figures_ != nullptr)
  {
    rectangle_t rectangle = figures_[0]->getFrameRect();

    maxX = rectangle.pos.x + rectangle.width / 2;
    maxY = rectangle.pos.y + rectangle.height / 2;
    minX = rectangle.pos.x - rectangle.width / 2;
    minY = rectangle.pos.y - rectangle.height / 2;

    for (size_t i = 1; i < count_; i++)
    {
      rectangle = figures_[i]->getFrameRect();
      point_t position = rectangle.pos;

      maxX = std::max(position.x + rectangle.width / 2, maxX);
      maxY = std::max(position.y + rectangle.height / 2, maxY);
      minX = std::min(position.x - rectangle.width / 2, minX);
      minY = std::min(position.y - rectangle.height / 2, minY);
    }
  }

  return {{(maxX + minX) / 2, (maxY + minY) / 2}, maxX - minX, maxY - minY};
}

void lukina::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < count_; i++)
  {
    figures_[i]->move(dx, dy);
  }
}

void lukina::CompositeShape::move(const point_t &newPoint)
{
  double dx = newPoint.x - getFrameRect().pos.x;
  double dy = newPoint.y - getFrameRect().pos.y;
  move(dx, dy);
}

void lukina::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Coefficient should be positive!");
  }

  point_t position = getFrameRect().pos;
  for (size_t i = 0; i < count_; i++)
  {
    figures_[i]->move({position.x + (figures_[i]->getFrameRect().pos.x - position.x) * coefficient,
                       position.y + (figures_[i]->getFrameRect().pos.y - position.y) * coefficient});
    figures_[i]->scale(coefficient);
  }
}

void lukina::CompositeShape::rotate(double degrees)
{
  const double angleRadian = M_PI * degrees / 180;
  const double sin = std::sin(angleRadian);
  const double cos = std::cos(angleRadian);
  const point_t compositeShapeCenter = this->getFrameRect().pos;

  for (size_t i = 0; i < count_; i++)
  {
    const point_t figureCenter = figures_[i]->getFrameRect().pos;
    double newX = compositeShapeCenter.x + (figureCenter.x - compositeShapeCenter.x) * cos
                  - (figureCenter.y - compositeShapeCenter.y) * sin;
    double newY = compositeShapeCenter.y + (figureCenter.x - compositeShapeCenter.x) * sin
                  + (figureCenter.y - compositeShapeCenter.y) * cos;

    figures_[i]->move({newX, newY});
    figures_[i]->rotate(degrees);
  }
}

void lukina::CompositeShape::add(Shape::ptr shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Can't be empty");
  }

  Shape::arrayPtr arr(std::make_unique<Shape::ptr[]>(count_ + 1));
  for (size_t i = 0; i < count_; i++)
  {
    arr[i] = figures_[i];
  }

  arr[count_] = shape;
  count_++;
  figures_.swap(arr);
}

void lukina::CompositeShape::remove(size_t index)
{
  if (figures_ == nullptr)
  {
    throw std::invalid_argument("The Composite Shape is empty");
  }

  if (index >= count_)
  {
    throw std::invalid_argument("Index is out of array");
  }

  for (size_t i = index; i < count_ - 1; i++)
  {
    figures_[i] = figures_[i + 1];
  }

  count_--;
}

size_t lukina::CompositeShape::getCount() const
{
  return count_;
}

void lukina::CompositeShape::printInfo() const
{
  std::cout << "COMPOSITE SHAPE" << std::endl;
  std::cout << "Count: " << count_ << std::endl;
  std::cout << "Center: " << getFrameRect().pos.x << ", " << getFrameRect().pos.y << std::endl;
  std::cout << "Width: " << getFrameRect().width << std::endl;
  std::cout << "Height: " << getFrameRect().height << std::endl;
  std::cout << "Area: " << getArea() << std::endl;
  std::cout << std::endl;
}
