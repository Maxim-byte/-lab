#define BOOST_TEST_MODULE mytest

#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  BOOST_CHECK_THROW(gromov::Rectangle rect({1.0, 1.0}, -5.0, 5.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle_scale)
{
  gromov::Rectangle rect({1.0, 1.0}, 5.0, 5.0);
  BOOST_CHECK_THROW(rect.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(gromov::Circle circle(-5.0, {1.0, 1.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle_scale)
{
  gromov::Circle circle(5.0, {1.0, 1.0});
  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_permanency_move_rectange)
{
  gromov::Rectangle rect({1.0, 1.0}, 10.0, 10.0);
  const gromov::rectangle_t frameRect = rect.getFrameRect();
  const double area = rect.getArea();
  rect.move({20.0, 20.0});
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY_DOUBLE);
  rect.move(20.0, 20.0);
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_permanency_move_circle)
{
  gromov::Circle circle(10.0, {1.0, 1.0});
  const gromov::rectangle_t frameRect = circle.getFrameRect();
  const double area = circle.getArea();
  circle.move(15.0, 20.0);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY_DOUBLE);
  circle.move({20.0, 20.0});
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  gromov::Rectangle rect({1.0, 1.0}, 10.0, 10.0);
  const double x = 5.0,
    y = 5.0,
    oldX = rect.getCentre().x,
    oldY = rect.getCentre().y;
  rect.move(x, y);
  BOOST_CHECK_CLOSE(rect.getCentre().x, x + oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getCentre().y, y + oldY, ACCURACY_DOUBLE);
  rect.move({x,y});
  BOOST_CHECK_CLOSE(rect.getCentre().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getCentre().y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  gromov::Circle circle(10.0, {1.0, 1.0});
  const double x = 5.0,
    y = 5.0,
    oldX = circle.getCentre().x,
    oldY= circle.getCentre().y;
  circle.move(x, y);
  BOOST_CHECK_CLOSE(circle.getCentre().x, x + oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().y, y + oldY, ACCURACY_DOUBLE);
  circle.move({x, y});
  BOOST_CHECK_CLOSE(circle.getCentre().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().y, y,ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_rectangle_area)
{
  gromov::Rectangle rect({1.0, 1.0}, 10.0, 14.5);
  const double area_rect = rect.getArea(),
    scale = 2.0;
  rect.scale(scale);
  BOOST_CHECK_CLOSE(area_rect * scale * scale, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_circle_area)
{
  gromov::Circle circle(7.0, {1.0, 1.0});
  const double area_circle = circle.getArea(),
    scale = 0.3;
  circle.scale(scale);
  BOOST_CHECK_CLOSE(area_circle * scale * scale, circle.getArea(), ACCURACY_DOUBLE);
}
