#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  lukina::Rectangle rec({1.0, 2.0}, 10.0, 5.0);
  lukina::Circle cir({2.0, 1.0}, 3.0);

  lukina::Shape *shape = &rec;
  std::cout << "Rectangle before changes:" << std::endl;
  shape->printInfo();
  shape->move(1.0, 2.0);
  shape->move({0.0, 0.0});
  shape->scale(2.0);
  std::cout << "Rectangle after changes:" << std::endl;
  shape->printInfo();

  shape = &cir;
  std::cout << "Circle before changes:" << std::endl;
  shape->printInfo();
  shape->move(3.0, 2.0);
  shape->move({1.0, 1.0});
  shape->scale(4.0);
  std::cout << "Circle after changes:" << std::endl;
  shape->printInfo();

  return 0;
}
