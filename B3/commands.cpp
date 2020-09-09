#include <map>
#include <cctype>
#include <sstream>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "bookmark_handler.hpp"

std::string checkNumber(std::string& number)
{
  if (number.empty())
  {
    return "";
  }

  for (size_t i = 0; i < number.size(); ++i)
  {
    if (!std::isdigit(number[i]))
    {
      return "";
    }
  }

  return number;
}


std::string checkName(std::string& name)
{
  if (name.empty())
  {
    return "";
  }

  if (name.front() != '\"')
  {
    return "";
  }

  name.erase(name.begin());

  size_t i = 0;
  while ((i < name.size()) && (name[i] != '\"'))
  {
    if (name[i] == '\\')
    {
      if ((name[i + 1] == '\"') && (i + 2 < name.size()))
      {
        name.erase(i, 1);
      }
      else
      {
        return "";
      }
    }
    ++i;
  }

  if (i == name.size())
  {
    return "";
  }

  name.erase(i);

  if (name.empty())
  {
    return "";
  }

  return name;
}

std::string checkBookmarkName(std::string& bookmarkName)
{
  if (bookmarkName.empty())
  {
    return "";
  }

  for (size_t i = 0; i < bookmarkName.size(); ++i)
  {
    if (!isalnum(bookmarkName[i]) && (bookmarkName[i] != '-'))
    {
      return "";
    }
  }

  return bookmarkName;
}

void commandAdd(BookmarkHandler& handler, std::stringstream& strStream)
{
  std::string number;
  strStream >> std::ws >> number;
  number = checkNumber(number);

  std::string name;
  std::getline(strStream >> std::ws, name);
  name = checkName(name);

  if (name.empty() || number.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  handler.add({name, number});
}

void commandStore(BookmarkHandler& handler, std::stringstream& strStream)
{
  std::string markName;
  strStream >> std::ws >> markName;
  markName = checkBookmarkName(markName);

  std::string newMarkName;
  strStream >> std::ws >> newMarkName;
  newMarkName = checkBookmarkName(newMarkName);

  if (markName.empty() || newMarkName.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  handler.store(markName, newMarkName);
}

void commandInsert(BookmarkHandler& handler, std::stringstream& strStream)
{
  std::map<const char*, BookmarkHandler::InsertDirection> directions =
      {
          {"before", BookmarkHandler::InsertDirection::before},
          {"after", BookmarkHandler::InsertDirection::after}
      };

  std::string dir;
  strStream >> std::ws >> dir;

  auto predicate = [&](const std::pair<const char*, BookmarkHandler::InsertDirection>& pair) { return pair.first == dir; };
  auto direction = std::find_if(std::begin(directions), std::end(directions), predicate);

  if (direction == std::end(directions))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  std::string markName;
  strStream >> std::ws >> markName;
  markName = checkBookmarkName(markName);

  std::string number;
  strStream >> std::ws >> number;
  number = checkNumber(number);

  std::string name;
  std::getline(strStream >> std::ws, name);
  name = checkName(name);

  if (markName.empty() || number.empty() || name.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  handler.insert(direction->second, markName, {name, number});
}

void commandDelete(BookmarkHandler& handler, std::stringstream& strStream)
{
  std::string markName;
  strStream >> std::ws >> markName;
  markName = checkBookmarkName(markName);

  if (markName.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  handler.erase(markName);
}

void commandShow(BookmarkHandler& handler, std::stringstream& strStream)
{
  std::string markName;
  strStream >> std::ws >> markName;
  markName = checkBookmarkName(markName);

  if (markName.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  handler.show(markName);
}

void commandMove(BookmarkHandler& handler, std::stringstream& strStream)
{
  std::map<const char*, BookmarkHandler::MoveDirection> directions =
      {
          {"first", BookmarkHandler::MoveDirection::first},
          {"last", BookmarkHandler::MoveDirection::last}
      };

  std::string markName;
  strStream >> std::ws >> markName;
  markName = checkBookmarkName(markName);

  if (markName.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  std::string steps;
  strStream >> std::ws >> steps;

  auto predicate = [&](const std::pair<const char*, BookmarkHandler::MoveDirection>& pair) { return pair.first == steps; };
  auto direction = std::find_if(std::begin(directions), std::end(directions), predicate);

  int sign = 1;
  if (direction == std::end(directions))
  {
    if (steps.front() == '-')
    {
      sign = -1;
      steps.erase(steps.begin());
    }
    else if (steps.front() == '+')
    {
      steps.erase(steps.begin());
    }

    steps = checkNumber(steps);

    if (steps.empty())
    {
      std::cout << "<INVALID STEP>\n";
      return;
    }

    handler.move(markName, std::stoi(steps) * sign);
  }
  else
  {
    handler.move(markName, direction->second);
  }
}
