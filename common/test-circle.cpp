#include <boost/test/auto_unit_test.hpp>

#include "circle.hpp"

const double ALLOWABLE_ERROR = 0.001;

BOOST_AUTO_TEST_SUITE(CircleTestSuite)

BOOST_AUTO_TEST_CASE(ImmutabilityofCircleParameters)
{
  lukina::Circle cir({0.1, 0.1}, 5.0);
  const lukina::rectangle_t cirBefore = cir.getFrameRect();
  const double areaBefore = cir.getArea();

  cir.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(cirBefore.width, cir.getFrameRect().width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(cirBefore.height, cir.getFrameRect().height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(areaBefore, cir.getArea(), ALLOWABLE_ERROR);


  cir.move({-1.0, -1.0});
  BOOST_CHECK_CLOSE(cirBefore.width, cir.getFrameRect().width, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(cirBefore.height, cir.getFrameRect().height, ALLOWABLE_ERROR);
  BOOST_CHECK_CLOSE(areaBefore, cir.getArea(), ALLOWABLE_ERROR);
}

BOOST_AUTO_TEST_CASE(CircleAreaAfterScale)
{
  lukina::Circle cir({2.0, 2.0}, 3.0);
  const double areaBefore = cir.getArea();
  const double scaleFactor = 2.0;

  cir.scale(scaleFactor);
  BOOST_CHECK_CLOSE(areaBefore * scaleFactor * scaleFactor, cir.getArea(), ALLOWABLE_ERROR);
}

BOOST_AUTO_TEST_CASE(CircleIncorrectParameters)
{
  BOOST_CHECK_THROW(lukina::Circle({0.0, 0.0}, -1.0), std::invalid_argument);

  lukina::Circle cir({0.0, 0.1}, 2.0);
  BOOST_CHECK_THROW(cir.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
