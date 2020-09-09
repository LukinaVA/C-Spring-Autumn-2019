#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  Rectangle rec({1.0, 2.0}, 10.0, 5.0);
  std::cout << "Rectangle area: " << rec.getArea() << std::endl;
  std::cout << "Bounding box options:\n";
  std::cout << "Width: " << rec.getFrameRect().width << std::endl;
  std::cout << "Height: " << rec.getFrameRect().height << std::endl;
  std::cout << "Center: " << rec.getFrameRect().pos.x << " , " << rec.getFrameRect().pos.y << std::endl;
  rec.move({0.0, 0.0});

  Circle cir({2.0, 1.0}, 3.0);
  std::cout << "Area of a circle: " << cir.getArea() << std::endl;
  std::cout << "Bounding box options:\n";
  std::cout << "Width: " << cir.getFrameRect().width << std::endl;
  std::cout << "Height: " << cir.getFrameRect().height << std::endl;
  std::cout << "Center: " << cir.getFrameRect().pos.x << " , " << cir.getFrameRect().pos.y << std::endl;
  cir.move(-2.0, -1.0);

  std::cout << "Polymorphism:\n";
  Shape * figures[] = {&rec, &cir};
  const int SIZE = sizeof(figures) / sizeof(Shape);
  for (int i = 0; i < SIZE; i++)
  {
    std::cout << figures[i]->getArea() << std::endl;
  }
  return 0;
}
