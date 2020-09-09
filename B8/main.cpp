#include <iostream>
#include "handler.hpp"

const int MAX_WIDTH = 25;

int main(int argc, char* argv[])
{
  try
  {
    if ((argc > 3) || (argc == 2))
    {
      throw std::invalid_argument("Invalid arguments!");
    }

    size_t lineWidth = 40;

    if (argc == 3)
    {
      if (std::string(argv[1]) != "--line-width")
      {
        throw std::invalid_argument("Invalid arguments!");
      }

      char* str_end = nullptr;
      lineWidth = std::strtol(argv[2], &str_end, 10);
      if ((*str_end) || (lineWidth < MAX_WIDTH))
      {
        throw std::invalid_argument("Invalid arguments!");
      }
    }

    Handler handler(lineWidth);
    handler.inputAndCheckText();
    handler.formatAndPrintText();
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what() << "\n";
    return 1;
  }

  return 0;
}
