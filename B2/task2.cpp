#include <list>
#include <iostream>
#include <stdexcept>

void print(std::list<int>::iterator begin, std::list<int>::iterator end)
{
  if (begin == end)
  {
    std::cout << '\n';
    return;
  }

  if (begin == std::prev(end))
  {
    std::cout << *begin << '\n';
    return;
  }

  std::cout << *begin << " " << *std::prev(end) << " ";
  ++begin;
  --end;

  print(begin, end);
}

void task2()
{
  const int minValue = 1;
  const int maxValue = 20;
  const size_t maxSize = 20;

  std::list<int> intList;
  std::size_t currSize = 0;

  int num;
  while (std::cin && !(std::cin >> num).eof())
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("Incorrect input data!");
    }

    if ((num < minValue) || (num > maxValue))
    {
      throw std::invalid_argument("The number must be from 1 to 20!");
    }

    if (currSize < maxSize)
    {
      intList.push_back(num);
      ++currSize;
    }
    else
    {
      throw std::invalid_argument("The list can contain from 0 to 20 values!");
    }
  }

  print(intList.begin(), intList.end());
}
