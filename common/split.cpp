#include "split.hpp"
#include "shape.hpp"

lukina::Matrix lukina::split(const CompositeShape &listOfFigures)
{
  lukina::Matrix matrix;
  matrix.add(listOfFigures[0], 0);

  for (size_t i = 1; i < listOfFigures.getCount(); i++)
  {
    bool nextRow = true;

    for (size_t row = 0; row < matrix.getRows(); row++)
    {
      int counter = 0;
      for (size_t column = 0; column < matrix[row].getSize(); column++)
      {
        counter += matrix[row][column]->intersection(listOfFigures[i]);
      }

      if (counter == 0)
      {
        matrix.add(listOfFigures[i], row);
        nextRow = false;
        break;
      }
    }

    if (nextRow)
    {
      matrix.add(listOfFigures[i], matrix.getRows());
    }
  }

  return matrix;
}
