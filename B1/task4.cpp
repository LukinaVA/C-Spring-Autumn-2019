#include <random>
#include <vector>

#include "print.hpp"
#include "sort.hpp"
#include "strategy.hpp"

void fillRandom(double* array, size_t size, std::mt19937 gen)
{
  std::uniform_real_distribution <> dis(-1.0, 1.0);
  for (size_t i = 0; i < size; ++i)
  {
    array[i] = dis(gen);
  }
}

void task4(const char* direction, size_t size, std::mt19937 generator)
{
  auto compare = comparison<double>(direction);

  if (!size)
  {
    return;
  }

  std::vector<double> vector(size, 0);

  fillRandom(&vector[0], size, generator);
  std::cout << vector << '\n';

  sort<OperatorAccess>(vector, compare);
  std::cout << vector << '\n';
}
