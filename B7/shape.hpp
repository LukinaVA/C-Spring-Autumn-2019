#ifndef SHAPE_B8
#define SHAPE_B8

struct Point_t
{
    int x;
    int y;
};

class Shape
{
public:
  Shape(const Point_t& center);
  ~Shape() = default;

  bool isMoreLeft(const Shape& shape) const;
  bool isUpper(const Shape& shape) const;
  virtual void draw() = 0;

  Point_t getCenter();

private:
  Point_t center_;
};

#endif //SHAPE_B8
