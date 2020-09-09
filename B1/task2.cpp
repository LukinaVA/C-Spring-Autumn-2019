#include <fstream>
#include <memory>
#include <vector>

#include "print.hpp"

void task2(const char* filename)
{
  const size_t memorySize = 128;
  using array = std::unique_ptr<char[], decltype(&free)>;

  std::ifstream file(filename);
  if (!file)
  {
    throw std::runtime_error("Could not open file");
  }

  size_t size = memorySize;

  array arr(static_cast<char*>(malloc(size)), &free);

  size_t num = 0;
  while (file)
  {
    file.read(&arr[num], memorySize);

    if (file.gcount() == memorySize)
    {
      size += memorySize;
      array temp(static_cast<char*>(realloc(arr.get(), size)), &free);

      if (temp)
      {
        arr.release();
        std::swap(arr, temp);
      }
      else
      {
        throw std::runtime_error("Failed to reallocate memory");
      }
    }
    num += file.gcount();
  }
  file.close();

  std::vector<char> vector(&arr[0], &arr[num]);

  for (const char& i: vector)
  {
    std::cout << i;
  }
}
