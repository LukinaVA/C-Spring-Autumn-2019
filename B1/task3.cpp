#include <vector>
#include "print.hpp"

void task3()
{
  std::vector<int> vector;

  int num = 0;
  while (std::cin >> num)
  {
    if (num == 0)
    {
      break;
    }

    vector.push_back(num);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::invalid_argument("Wrong input data");
  }

  if (vector.empty())
  {
    return;
  }

  if (num != 0)
  {
    throw std::runtime_error("Last number must be zero.");
  }

  switch (vector.back())
  {
    case 1:
      for (auto i = vector.begin(); i != vector.end();)
      {
        if (*i % 2 == 0)
        {
          vector.erase(i);
        }
        else
        {
          ++i;
        }
      }
      break;

    case 2:
      for (auto i = vector.begin(); i != vector.end();)
      {
        if (*i % 3 == 0)
        {
          i = vector.insert(++i, 3, 1);
        }
        else
        {
          ++i;
        }
      }
      break;
  }
  std::cout << vector << '\n';
}
