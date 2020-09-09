#ifndef FIGURES_B8
#define FIGURES_B8

#include <iostream>

#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const Point_t& center);
  void draw() override;
};


class Triangle: public Shape
{
public:
  Triangle(const Point_t& center);
  void draw() override;
};


class Square: public Shape
{
public:
  Square(const Point_t& center);
  void draw() override;
};

#endif //FIGURES_B8
