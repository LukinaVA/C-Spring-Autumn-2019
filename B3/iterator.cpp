#include "iterator.hpp"
#include "container.hpp"

Iterator::Iterator() :
    Iterator(1)
{}

Iterator::Iterator(size_t position) :
    index_(position),
    factorial_(getFactorial(position))
{}

Iterator::pointer Iterator::operator ->()
{
  return &factorial_;
}

Iterator::reference Iterator::operator *()
{
  return factorial_;
}

Iterator& Iterator::operator ++()
{
  if (index_ < Container::MAX)
  {
    ++index_;
    factorial_ *= index_;
  }
  return *this;
}

Iterator Iterator::operator ++(int)
{
  Iterator iterator = *this;
  ++(iterator);
  return iterator;
}

Iterator& Iterator::operator --()
{
  if (index_ > Container::MIN)
  {
    factorial_ /= index_;
    --index_;
  }
  return *this;
}

Iterator Iterator::operator --(int)
{
  Iterator iterator = *this;
  --(iterator);
  return iterator;
}

bool Iterator::operator ==(const Iterator& iterator)
{
  return (index_ == iterator.index_);
}

bool Iterator::operator !=(const Iterator& iterator)
{
  return !(*this == iterator);
}

size_t Iterator::getFactorial(size_t index) const
{
  size_t res = 1;
  for (size_t i = 1; i <= index; ++i)
  {
    res *= i;
  }
  return res;
}
