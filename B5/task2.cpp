#include <vector>
#include <sstream>
#include <numeric>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "shape.hpp"

Shape readShapeData(const std::string& string)
{
  std::stringstream strStream(string);

  int verticesCount;
  strStream >> verticesCount;

  Shape shape;
  const size_t strLength = string.length();
  for(int i = 0; i < verticesCount; ++i)
  {
    Point point{0, 0};
    strStream.ignore(strLength, '(');
    strStream >> point.x;

    strStream.ignore(strLength, ';');
    strStream >> point.y;

    strStream.ignore(strLength, ')');
    shape.push_back(point);
  }

  if(strStream.fail())
  {
    throw std::invalid_argument("Invalid value of points!");
  }

  std::string extraPoints;
  getline (strStream >> std::ws, extraPoints);

  if(!extraPoints.empty())
  {
    throw std::invalid_argument("Invalid number of points!");
  }

  return shape;
}

size_t countVertices(const std::vector<Shape>& vector)
{
  size_t count = 0;
  auto iter = vector.begin();
  while(iter != vector.end())
  {
    count += (*iter).size();
    ++iter;
  }

  return count;
}

bool isRectangle(const Shape& shape)
{
  return (shape.size() == 4);
}

bool isTriangle(const Shape& shape)
{
  return (shape.size() == 3);
}

size_t countTriangles(const std::vector < Shape >& vector)
{
  size_t count = 0;
  auto iter = vector.begin();
  while(iter != vector.end())
  {
    if (isTriangle(*iter))
    {
      ++count;
    }
    ++iter;
  }

  return count;
}

size_t countRectangles(const std::vector < Shape >& vector)
{
  size_t count = 0;
  auto iter = vector.begin();
  while(iter != vector.end())
  {
    if (isRectangle(*iter))
    {
      ++count;
    }
    ++iter;
  }

  return count;
}

bool compareX(const Point& point1, const Point& point2)
{
  return point1.x < point2.x;
}

bool compareY(const Point& point1, const Point& point2)
{
  return point1.y < point2.y;
}

bool isSquare(const Shape& shape)
{
  bool isSquare = false;
  if (shape.size() == 4)
  {
    const int maxX = (std::max_element(shape.begin(), shape.end(), compareX))->x;
    const int minX = (std::min_element(shape.begin(), shape.end(), compareX))->x;

    const int maxY = (std::max_element(shape.begin(), shape.end(), compareY))->y;
    const int minY = (std::min_element(shape.begin(), shape.end(), compareY))->y;

    if ((maxX - minX) == (maxY - minY))
    {
      isSquare = true;
    }
  }

  return isSquare;
}

size_t countSquares(const std::vector < Shape >& vector)
{
  size_t count = 0;
  auto iter = vector.begin();
  while(iter != vector.end())
  {
    if (isSquare(*iter))
    {
      ++count;
    }
    ++iter;
  }

  return count;
}

void deletePentagon(std::vector < Shape >& vector)
{
  vector.erase(std::remove_if(vector.begin(), vector.end(), [] (const Shape &shape)
    {
      return shape.size() == 5;
    }), vector.end());
}

std::vector< Point > createPointVector(const std::vector < Shape >& vector)
{
  std::vector< Point > pointVector;

  for (const auto& it : vector)
  {
    pointVector.push_back(it.at(0));
  }

  return pointVector;
}

void task2()
{
  std::vector < Shape > vector;

  std::string str;
  while (std::getline(std::cin >> std::ws, str))
  {
    if (str.empty())
    {
      continue;
    }

    vector.push_back(readShapeData(str));
  }

  std::cout << "Vertices: " << countVertices(vector) << "\n";
  std::cout << "Triangles: " << countTriangles(vector) << "\n";
  std::cout << "Squares: " << countSquares(vector) << "\n";
  std::cout << "Rectangles: " << countRectangles(vector) << "\n";

  deletePentagon(vector);

  const std::vector< Point > pointVector = createPointVector(vector);
  std::cout << "Points:";
  for (auto it : pointVector)
  {
    std::cout << " (" << it.x << ";" << it.y << ")";
  }

  auto triangleEnd = std::partition(vector.begin(), vector.end(), isTriangle);
  auto squareEnd = std::partition(triangleEnd, vector.end(), isSquare);
  std::partition(squareEnd, vector.end(), isRectangle);

  std::cout << "\nShapes:\n";
  for (auto& it : vector)
  {
    std::cout << it.size() ;
    for (auto& sIt : it)
    {
      std::cout << " (" << sIt.x << ";" << sIt.y << ")";
    }
    std::cout << "\n";
  }
}
