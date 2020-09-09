#include <boost/test/auto_unit_test.hpp>

#include "matrix.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

BOOST_AUTO_TEST_SUITE(MatrixTestSuite)

BOOST_AUTO_TEST_CASE(MatrixCopyConstructor)
{
  lukina::Rectangle rec({10.0, 3.0}, 4.0, 2.0);
  lukina::Circle cir({4.0, 4.0}, 2.0);

  lukina::Matrix matrix;
  matrix.add(std::make_shared<lukina::Rectangle>(rec), 0);
  matrix.add(std::make_shared<lukina::Circle>(cir), 1);

  lukina::Matrix testMatrix(matrix);

  BOOST_CHECK_EQUAL(matrix.getRows(), testMatrix.getRows());
  BOOST_CHECK_EQUAL(matrix.getNumberOfFigures(), testMatrix.getNumberOfFigures());
}

BOOST_AUTO_TEST_CASE(MatrixCopyOperator)
{
  lukina::Rectangle rec({10.0, 3.0}, 4.0, 2.0);
  lukina::Circle cir({4.0, 4.0}, 2.0);

  lukina::Matrix matrix;
  matrix.add(std::make_shared<lukina::Rectangle>(rec), 0);
  matrix.add(std::make_shared<lukina::Circle>(cir), 1);

  lukina::Matrix testMatrix = matrix;

  BOOST_CHECK_EQUAL(matrix.getRows(), testMatrix.getRows());
  BOOST_CHECK_EQUAL(matrix.getNumberOfFigures(), testMatrix.getNumberOfFigures());
}

BOOST_AUTO_TEST_CASE(MatrixIndexingOperator)
{
  lukina::Rectangle rec({10.0, 3.0}, 4.0, 2.0);
  lukina::Circle cir({4.0, 4.0}, 2.0);

  lukina::Matrix matrix;
  matrix.add(std::make_shared<lukina::Rectangle>(rec), 0);
  matrix.add(std::make_shared<lukina::Circle>(cir), 1);

  BOOST_CHECK_EQUAL(matrix[0][0]->getArea(), rec.getArea());
  BOOST_CHECK_EQUAL(matrix[1][0]->getArea(), cir.getArea());
}

BOOST_AUTO_TEST_CASE(MatrixAfterAdd)
{
  lukina::Rectangle rec({10.0, 3.0}, 4.0, 2.0);
  lukina::Circle cir({4.0, 4.0}, 2.0);

  lukina::Matrix matrix;
  matrix.add(std::make_shared<lukina::Rectangle>(rec), 0);
  matrix.add(std::make_shared<lukina::Circle>(cir), 1);
  const double rowsBefore = matrix.getRows();
  const double numberBefore = matrix.getNumberOfFigures();

  lukina::CompositeShape composite(std::make_shared<lukina::Rectangle>(rec));
  composite.add(std::make_shared<lukina::Circle>(cir));
  matrix.add(std::make_shared<lukina::CompositeShape>(composite), 2);

  BOOST_CHECK_EQUAL(rowsBefore, matrix.getRows() - 1);
  BOOST_CHECK_EQUAL(numberBefore, matrix.getNumberOfFigures() - 1);
}

BOOST_AUTO_TEST_CASE(MatrixIncorrectParameters)
{
  lukina::Rectangle rec({10.0, 3.0}, 4.0, 2.0);
  lukina::Circle cir({4.0, 4.0}, 2.0);

  lukina::Matrix matrix;
  matrix.add(std::make_shared<lukina::Rectangle>(rec), 0);
  matrix.add(std::make_shared<lukina::Circle>(cir), 1);

  BOOST_CHECK_THROW(matrix[0][1], std::invalid_argument);
  BOOST_CHECK_THROW(matrix.add(nullptr, 0), std::invalid_argument);
  BOOST_CHECK_THROW(matrix.add(std::make_shared<lukina::Rectangle>(rec), 3), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
