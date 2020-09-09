#ifndef DATA_STRUCT_B4
#define DATA_STRUCT_B4

#include <string>
#include <vector>

struct DataStruct
{
    int key1;
    int key2;
    std::string str;
};

DataStruct read(std::istream& input);
void print(const std::vector<DataStruct>& vector);

#endif //DATA_STRUCT_B4
