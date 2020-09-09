#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "data_struct.hpp"

void task()
{
  std::vector<DataStruct> vector;

  std::string string;
  while (getline(std::cin, string))
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("Input failed!");
    }

    std::stringstream strStream(string);
    DataStruct dataStruct = read(strStream);
    vector.push_back(dataStruct);
  }

  std::sort(vector.begin(), vector.end(), [&](DataStruct& tmp, DataStruct& next)
  {
    if (tmp.key1 == next.key1 && tmp.key2 == next.key2)
    {
      return (tmp.str.length() < next.str.length());
    }
    else if (tmp.key1 == next.key1)
    {
      return (tmp.key2 < next.key2);
    }
    else
    {
      return (tmp.key1 < next.key1);
    }
  });

  print(vector);
}
