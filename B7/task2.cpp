#include <list>
#include <memory>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

#include "shape.hpp"
#include "figures.hpp"

using shapePtr = std::shared_ptr< Shape >;

shapePtr getShapePtr(const std::string& shapeName, const Point_t& point)
{
  if (shapeName == "CIRCLE")
  {
    return std::make_shared< Circle >(Circle(point));
  }
  else if (shapeName == "SQUARE")
  {
    return std::make_shared< Square >(Square(point));
  }
  else if (shapeName == "TRIANGLE")
  {
    return std::make_shared< Triangle >(Triangle(point));
  }
  else
  {
    throw std::invalid_argument("Invalid shape name!");
  }
}

Point_t getCenter(std::stringstream& strStream, const size_t& lineLength)
{
  strStream.ignore(lineLength, '(');
  int x = 0;
  strStream >> x;

  strStream.ignore(lineLength, ';');
  int y = 0;
  strStream >> y;

  strStream.ignore(lineLength, ')');

  if (strStream.fail())
  {
    throw std::invalid_argument("Invalid point data!");
  }

  return {x, y};
}

std::string getShapeName(std::stringstream& strStream)
{
  std::string shapeName;
  std::getline(strStream, shapeName, '(');
  strStream.unget();
  shapeName.erase(std::remove_if(shapeName.begin(), shapeName.end(), isspace), shapeName.end());

  if ((shapeName != "CIRCLE") && (shapeName != "SQUARE") && (shapeName != "TRIANGLE"))
  {
    throw std::invalid_argument("Invalid shape name!");
  }

  return shapeName;
}

void print(const std::list< shapePtr >& shapeList)
{
  for (const auto& shape : shapeList)
  {
    shape->draw();
  }
}

void  task2()
{
  std::list< shapePtr > shapes;

  std::string tmpString;
  while (std::getline(std::cin >> std::ws, tmpString))
  {
    if (tmpString.empty())
    {
      continue;
    }

    std::stringstream stringStream(tmpString);

    const std::string shapeName = getShapeName(stringStream);
    const Point_t center = getCenter(stringStream, tmpString.length());
    shapes.push_back(getShapePtr(shapeName, center));
  }

  std::cout << "Original:\n";
  print(shapes);

  std::cout << "Left-Right:\n";
  shapes.sort([](const shapePtr& tmp, const shapePtr& next) { return tmp->isMoreLeft(*next); });
  print(shapes);

  std::cout << "Right-Left:\n";
  shapes.sort([](const shapePtr& tmp, const shapePtr& next) { return !tmp->isMoreLeft(*next); });
  print(shapes);

  std::cout << "Top-Bottom:\n";
  shapes.sort([](const shapePtr& tmp, const shapePtr& next) { return tmp->isUpper(*next); });
  print(shapes);

  std::cout << "Bottom-Top:\n";
  shapes.sort([](const shapePtr& tmp, const shapePtr& next) { return !tmp->isUpper(*next); });
  print(shapes);
}
