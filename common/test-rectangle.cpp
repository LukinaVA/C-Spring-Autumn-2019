#include <boost/test/auto_unit_test.hpp>

#include "rectangle.hpp"
#include "base-types.hpp"

const double ALLOWABLE_ERROR = 0.001;

BOOST_AUTO_TEST_SUITE(RectangleTestSuite)

BOOST_AUTO_TEST_CASE(ImmutabilityofRectangleParameters)
{
  lukina::Rectangle rec({0.0, 0.0}, 2.0, 4.0);
  const lukina::rectangle_t recBefore = rec.getFrameRect();
  const double areaBefore = rec.getArea();

  rec.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(recBefore.width, rec.getFrameRect().width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(recBefore.height, rec.getFrameRect().height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(areaBefore, rec.getArea(), ALLOWABLE_ERROR);

  rec.move({3.0, 6.0});
  BOOST_CHECK_CLOSE(recBefore.width, rec.getFrameRect().width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(recBefore.height, rec.getFrameRect().height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(areaBefore, rec.getArea(), ALLOWABLE_ERROR);
}

BOOST_AUTO_TEST_CASE(RectangleAreaAfterScale)
{
  lukina::Rectangle rec({2.0, 2.0}, 4.0, 5.0);
  const double areaBefore = rec.getArea();
  const double scaleFactor = 2.0;

  rec.scale(scaleFactor);
  BOOST_CHECK_CLOSE(areaBefore * scaleFactor * scaleFactor, rec.getArea(), ALLOWABLE_ERROR);
}

BOOST_AUTO_TEST_CASE(RectangleAreaAfterRotate)
{
  lukina::Rectangle rec({2.0, 2.0}, 4.0, 5.0);
  const double areaBefore = rec.getArea();
  const double widthBefore = rec.getFrameRect().width;
  const double heightBefore = rec.getFrameRect().height;

  rec.rotate(90);
  BOOST_CHECK_CLOSE(areaBefore, rec.getArea(), ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(widthBefore, rec.getFrameRect().height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(heightBefore, rec.getFrameRect().width, ALLOWABLE_ERROR);
}


BOOST_AUTO_TEST_CASE(RectangleIncorrectParameters)
{
  BOOST_CHECK_THROW(lukina::Rectangle({0.0, 0.0}, -1.0, 2.0), std::invalid_argument);
  BOOST_CHECK_THROW(lukina::Rectangle({0.0, 0.0}, 1.0, -2.0), std::invalid_argument);

  lukina::Rectangle rec({0.0, 0.1}, 2.0, 3.0);
  BOOST_CHECK_THROW(rec.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
