#include <iostream>
#include <random>
#include <ctime>

#include "tasks.hpp"

std::mt19937 gen(time(0));

int main(int argc, char* argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      std::cerr << "Invalid number of arguments.";
      return 1;
    }

    char* str_end = nullptr;
    const int base = 10;
    const int task = std::strtol(argv[1], &str_end, base);
    if (*str_end)
    {
      std::cerr << "Invalid task number.";
      return 1;
    }

    switch (task)
    {
    case 1:
      if (argc != 3)
      {
        std::cerr << "Must be 3 parameters!";
        return 1;
      }
      task1(argv[2]);
      break;
    case 2:
      if (argc != 3)
      {
        std::cerr << "Must be 3 parameters!";
        return 1;
      }
      task2(argv[2]);
      break;
    case 3:
      if (argc != 2)
      {
        std::cerr << "Must be 2 parameters!";
        return 1;
      }
      task3();
      break;
    case 4:
    {
      if (argc != 4)
      {
        std::cerr << "Must be 4 parameters!";
        return 1;
      }
      const size_t vectorSize = std::strtol(argv[3], &str_end, base);
      if (*str_end)
      {
        std::cerr << "Invalid vector size.";
        return 1;
      }

      task4(argv[2], vectorSize, gen);
      break;
    }
    default:
      std::cerr << "Invalid task number.";
      return 1;
    }
  }

  catch (const std::exception& exception)
  {
    std::cerr << exception.what();
    return 1;
  }

  return 0;
}
