#include "container.hpp"

Iterator Container::begin()
{
  return Iterator(Container::MIN);
}

Iterator Container::end()
{
  return Iterator(Container::MAX);
}
