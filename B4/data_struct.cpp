#include "data_struct.hpp"

#include <iostream>

DataStruct read(std::istream& input)
{
  if (input.eof())
  {
    throw std::invalid_argument("Empty line!");
  }

  DataStruct dataStruct;

  int key1;
  input >> key1;
  if (input.fail())
  {
    throw std::invalid_argument("Failed while reading data!");
  }
  if ((abs(key1) > 5) || input.get() != ',' || input.eof() || input.peek() == '\n')
  {
    throw std::invalid_argument("Invalid argument!");
  }

  int key2;
  input >> key2;
  if (input.fail())
  {
    throw std::invalid_argument("Failed while reading data!");
  }
  if ((abs(key2) > 5) || input.get() != ',' || input.eof() || input.peek() == '\n')
  {
    throw std::invalid_argument("Invalid argument!");
  }

  std::string str;
  std::getline(input >> std::ws, str);
  if (input.fail())
  {
    throw std::invalid_argument("Failed while reading data!");
  }

  dataStruct.key1 = key1;
  dataStruct.key2 = key2;
  dataStruct.str = str;

  return dataStruct;
}

void print(const std::vector<DataStruct>& vector)
{
  for (const auto& dataStruct : vector)
  {
    std::cout << dataStruct.key1 << "," << dataStruct.key2 << "," << dataStruct.str << '\n';
  }
}
