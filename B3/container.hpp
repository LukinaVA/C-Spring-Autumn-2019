#ifndef CONTAINER_B3
#define CONTAINER_B3

#include "iterator.hpp"

class Container
{
public:
  static const int MAX = 11;
  static const int MIN = 1;

  Container() = default;
  Iterator begin();
  Iterator end();
};


#endif //CONTAINER_B3
