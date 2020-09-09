#include <iostream>
#include <algorithm>

#include "container.hpp"

void task2()
{
  Container cont;

  std::copy(cont.begin(), cont.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';

  std::reverse_copy(cont.begin(), cont.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
