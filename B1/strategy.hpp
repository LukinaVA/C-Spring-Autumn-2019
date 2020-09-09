#ifndef STRATEGY_B1
#define STRATEGY_B1

#include <iterator>

template <typename Container>
struct OperatorAccess
{
  static typename Container::reference get(Container& vector, size_t index)
  {
    return vector[index];
  }

  static size_t begin(const Container&)
  {
    return 0;
  }

  static size_t end(const Container& vector)
  {
    return vector.size();
  }
};

template <typename Container>
struct MethodAccess
{
  static typename Container::reference get(Container& vector, size_t index)
  {
    return vector.at(index);
  }

  static size_t begin(Container&)
  {
    return 0;
  }

  static size_t end(Container& vector)
  {
    return vector.size();
  }
};

template <typename Container>
struct IteratorAccess
{
  using iterator = typename Container::iterator;

  static typename Container::reference get(Container&, iterator iter)
  {
    return *iter;
  }

  static iterator begin(Container& list)
  {
    return list.begin();
  }

  static iterator end(Container& list)
  {
    return list.end();
  }
};

#endif //STRATEGY_B1
