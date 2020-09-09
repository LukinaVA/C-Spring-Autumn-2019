#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void task1()
{
  std::string string;
  std::set<std::string> set;

  while (std::getline(std::cin, string))
  {
    std::stringstream strStream(string);
    std::string word;
    while (strStream >> word)
    {
      set.insert(word);
    }
  }

  for (const auto& word : set)
  {
    std::cout << word << "\n";
  }
}
