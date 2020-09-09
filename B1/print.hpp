#ifndef PRINT_B1
#define PRINT_B1

#include <iostream>

template <typename Container, typename = typename Container::iterator>
std::ostream& operator<<(std::ostream& out, const Container& collection)
{
  for (const auto& i : collection)
  {
    out << i << ' ';
  }

  return out;
}

#endif //PRINT_B1
