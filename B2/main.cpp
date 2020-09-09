#include <iostream>

void task1();
void task2();

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Invalid number of arguments.";
      return 1;
    }

    char* str_end = nullptr;
    const int base = 10;
    const int task = std::strtol(argv[1], &str_end, base);
    if (*str_end)
    {
      std::cerr << "Invalid task number!";
      return 1;
    }

    switch (task)
    {
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    default:
      std::cerr << "Invalid task number!";
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
