#include "figures.hpp"

Circle::Circle(const Point_t& center):
    Shape(center)
{ }

void Circle::draw()
{
  std::cout << "CIRCLE (" << getCenter().x << ";" << getCenter().y << ")\n";
}

Triangle::Triangle(const Point_t& center):
    Shape(center)
{ }

void Triangle::draw()
{
  std::cout << "TRIANGLE (" << getCenter().x << ";" << getCenter().y << ")\n";
}

Square::Square(const Point_t& center):
    Shape(center)
{ }

void Square::draw()
{
  std::cout << "SQUARE (" << getCenter().x << ";" << getCenter().y << ")\n";
}
