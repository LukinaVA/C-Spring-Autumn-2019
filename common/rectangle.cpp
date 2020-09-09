#include "rectangle.hpp"

#include <iostream>
#include <cmath>
#include <stdexcept>

lukina::Rectangle::Rectangle(const point_t &center, double width, double height) :
  center_(center),
  width_(width),
  height_(height),
  corners_{{center.x - width / 2, center.y + height / 2},
           {center.x + width / 2, center.y + height / 2},
           {center.x + width / 2, center.y - height / 2},
           {center.x - width / 2, center.y - height / 2}}
{
  if ((width_ <= 0.0) || (height_ <= 0.0))
  {
    throw std::invalid_argument("Rectangle parameters must be positive!");
  }
}

double lukina::Rectangle::getArea() const
{
  return (width_ * height_);
}

lukina::rectangle_t lukina::Rectangle::getFrameRect() const
{
  point_t topLeft = corners_[0];
  point_t bottomRight = corners_[2];

  for (size_t i = 0; i < 4; i++)
  {
    topLeft.x = std::min(corners_[i].x, topLeft.x);
    topLeft.y = std::max(corners_[i].y, topLeft.y);
    bottomRight.x = std::max(corners_[i].x, bottomRight.x);
    bottomRight.y = std::min(corners_[i].y, bottomRight.y);
  }

  point_t center = {(topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2};

  return {center, bottomRight.x - topLeft.x, topLeft.y - bottomRight.y};
}

void lukina::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;

  for (size_t i = 0; i < 4; i++)
  {
    corners_[i].x += dx;
    corners_[i].y += dy;
  }
}

void lukina::Rectangle::move(const point_t &newPoint)
{
  for (size_t i = 0; i < 4; i++)
  {
    corners_[i] = {newPoint.x + corners_[i].x - center_.x, newPoint.y + corners_[i].y - center_.y};
  }

  center_ = newPoint;
}

void lukina::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Coefficient should be positive!");
  }

  width_ *= coefficient;
  height_ *= coefficient;

  for (size_t i = 0; i < 4; i++)
  {
    corners_[i] = {center_.x + (corners_[i].x - center_.x) * coefficient,
                   center_.y + (corners_[i].y - center_.y) * coefficient};
  }
}

void lukina::Rectangle::rotate(double degrees)
{
  const double angleRadian = M_PI * degrees / 180;
  const double sin = std::sin(angleRadian);
  const double cos = std::cos(angleRadian);

  for (size_t i =0; i < 4; i++)
  {
    corners_[i] = {center_.x + (corners_[i].x - center_.x) * cos - (corners_[i].y - center_.y) * sin,
                   center_.y + (corners_[i].y - center_.y) * cos + (corners_[i].x - center_.x) * sin};
  }
}

void lukina::Rectangle::printInfo() const
{
  std::cout << "RECTANGLE" << std::endl;
  std::cout << "Center: " << center_.x << ", " << center_.y << std::endl;
  std::cout << "Width: " << width_ << std::endl;
  std::cout << "Height: " << height_ << std::endl;
  std::cout << "Rectangle area: " << getArea() << std::endl;
  std::cout << "Frame rectangle:" << std::endl;
  std::cout << "-Center: " << getFrameRect().pos.x << ", " << getFrameRect().pos.y << std::endl;
  std::cout << "-Width: " << getFrameRect().width << std::endl;
  std::cout << "-Height: " << getFrameRect().height << std::endl;
  std::cout << std::endl;
  std::cout << "Coordinates of the corners of the rectangle" << std::endl;
  std::cout << "Top left: " << corners_[0].x << ", " << corners_[0].y << std::endl;
  std::cout << "Top right: " << corners_[1].x << ", " << corners_[1].y << std::endl;
  std::cout << "Bottom right: " << corners_[2].x << ", " << corners_[2].y << std::endl;
  std::cout << "Bottom left: " << corners_[3].x << ", " << corners_[3].y << std::endl;
  std::cout << std::endl;
}
