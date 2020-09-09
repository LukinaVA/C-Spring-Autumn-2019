#include "shape.hpp"

#include <cmath>

int lukina::Shape::intersection(const ptr shape) const
{
  rectangle_t frameRect1 = getFrameRect();
  rectangle_t frameRect2 = shape->getFrameRect();

  if (fabs(frameRect1.pos.x - frameRect2.pos.x) > ((frameRect1.width + frameRect2.width) / 2))
  {
    return 0;
  }

  if (fabs(frameRect1.pos.y - frameRect2.pos.y) > ((frameRect1.height + frameRect2.height) / 2))
  {
    return 0;
  }

  return 1;
}
