#include <cmath>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

void task1()
{
  std::vector< double > numbers((std::istream_iterator< double >(std::cin)), std::istream_iterator< double >());

  if (!std::cin.eof())
  {
    throw std::invalid_argument("Wrong input data!\n");
  }

  std::vector< double > newNumbers(numbers.size());
  std::transform(numbers.begin(), numbers.end(), newNumbers.begin(), std::bind1st(std::multiplies< double >(), M_PI));

  for (double& num : newNumbers)
  {
    std::cout << num << " ";
  }
  std::cout << "\n";
}
