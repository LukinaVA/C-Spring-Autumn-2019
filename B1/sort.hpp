#ifndef SORT_B1
#define SORT_B1

#include <functional>
#include <cstring>

template <typename Argument>
std::function<bool(Argument, Argument)> comparison(const char* dir)
{
  if (std::strcmp(dir, "ascending") == 0)
  {
    return [] (Argument i, Argument j) { return i < j; };
  }

  if (std::strcmp(dir, "descending") == 0)
  {
    return [] (Argument i, Argument j) { return i > j; };
  }

  throw std::invalid_argument("Wrong direction. Must be ascending or descending!");
}

template <template <class> class Strategy, typename Container>
void sort(Container& collection, std::function<bool (typename Container::value_type, typename Container::reference)> compare)
{
  const auto begin = Strategy<Container>::begin(collection);
  const auto end = Strategy<Container>::end(collection);

  for (auto i = begin; i != end; ++i)
  {
    for (auto j = i; j != end; ++j)
    {
      typename Container::reference curr = Strategy<Container>::get(collection, i);
      typename Container::reference run = Strategy<Container>::get(collection, j);

      if (compare(run, curr))
      {
        std::swap(run, curr);
      }
    }
  }
}

#endif //SORT_B1
