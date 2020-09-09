#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "queue_with_priority.hpp"

void add(QueueWithPriority<std::string>& queue, std::stringstream& input)
{
  using ElementPriority = QueueWithPriority<std::string>::ElementPriority;

  std::map<const std::string, ElementPriority> priorities =
  {
    {"low", ElementPriority::LOW},
    {"normal", ElementPriority::NORMAL},
    {"high", ElementPriority::HIGH}
  };

  std::string priority;
  input >> priority;

  auto key = std::find_if(std::begin(priorities), std::end(priorities),
    [&](const std::pair<const std::string, ElementPriority>& pair){ return (pair.first == priority);});

  if (key == std::end(priorities))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  std::string data;
  getline(input >> std::ws, data);
  if (data.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  queue.PutElementToQueue(data, key->second);
}

void get(QueueWithPriority<std::string>& queue, std::stringstream& input)
{
  std::string data;
  input >> data;
  if (!data.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  if (queue.empty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }

  std::cout << queue.GetElementFromQueue() << '\n';
}

void accelerate(QueueWithPriority<std::string>& queue, std::stringstream& input)
{
  std::string data;
  input >> data;

  if (!data.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  queue.Accelerate();
}
