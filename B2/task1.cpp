#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

#include "queue_with_priority.hpp"

void add(QueueWithPriority<std::string>& queue, std::stringstream& input);
void get(QueueWithPriority<std::string>& queue, std::stringstream& input);
void accelerate(QueueWithPriority<std::string>& queue, std::stringstream& input);

void task1()
{
  using command = std::function<void (QueueWithPriority<std::string>&, std::stringstream&)>;

  std::map<const std::string, command> commands =
  {
    {"add", add},
    {"get", get},
    {"accelerate", accelerate}
  };

  QueueWithPriority<std::string> queue;
  std::string input;

  while (getline(std::cin, input))
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("Read error");
    }

    std::stringstream strStream(input);
    std::string readCommand;
    strStream >> std::ws >> readCommand;

    auto key = std::find_if(std::begin(commands), std::end(commands),
      [&](const std::pair<const std::string, command>& pair) { return (pair.first == readCommand); });

    if (key != std::end(commands))
    {
      key->second(queue, strStream);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
