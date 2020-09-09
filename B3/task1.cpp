#include <sstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

#include "bookmark_handler.hpp"

void commandAdd(BookmarkHandler& handler, std::stringstream& strStream);
void commandStore(BookmarkHandler& handler, std::stringstream& strStream);
void commandInsert(BookmarkHandler& handler, std::stringstream& strStream);
void commandDelete(BookmarkHandler& handler, std::stringstream& strStream);
void commandShow(BookmarkHandler& handler, std::stringstream& strStream);
void commandMove(BookmarkHandler& handler, std::stringstream& strStream);

struct command_t
{
    const char* name;
    std::function<void(BookmarkHandler&, std::stringstream&)> execute;
};

void task1()
{
  BookmarkHandler handler;
  std::string str;

  while (getline(std::cin, str))
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("Input failed!");
    }

    std::stringstream strStream(str);
    std::string commandName;
    strStream >> commandName;

    const command_t commands[] =
    {
      {"add", &commandAdd},
      {"store", &commandStore},
      {"insert", &commandInsert},
      {"delete", &commandDelete},
      {"show", &commandShow},
      {"move", &commandMove}
    };

    auto predicate = [&](const command_t& com) { return com.name == commandName; };
    auto command = std::find_if(std::begin(commands), std::end(commands), predicate);

    if (command != std::end(commands))
    {
      command->execute(handler, strStream);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
  }
}
