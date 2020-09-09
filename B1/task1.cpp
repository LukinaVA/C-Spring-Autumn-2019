#include <vector>
#include <forward_list>

#include "strategy.hpp"
#include "sort.hpp"
#include "print.hpp"

void task1(const char* direction)
{
  std::vector<int> vectorBrackets;
  auto compare = comparison<int>(direction);

  int num = 0;
  while (std::cin && !(std::cin >> num).eof())
  {
    if (std::cin.fail())
    {
      throw std::invalid_argument("Incorrect input data");
    }

    vectorBrackets.push_back(num);
  }

  std::vector<int> vectorAt = vectorBrackets;
  std::forward_list<int> list(vectorBrackets.begin(), vectorBrackets.end());

  sort<OperatorAccess>(vectorBrackets, compare);
  std::cout << vectorBrackets << '\n';

  sort<MethodAccess>(vectorAt, compare);
  std::cout << vectorAt << '\n';

  sort<IteratorAccess>(list, compare);
  std::cout << list << '\n';
}
