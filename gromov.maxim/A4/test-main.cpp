#define BOOST_TEST_MODULE mytest

#include <memory>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "matrix.hpp"
#include "composite-shape.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_rotate_circle)
{
  gromov::Circle circle(5,{0,0});
  const double height = circle.getFrameRect().height;
  const double width = circle.getFrameRect().width;
  circle.rotate(90);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, height, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_rotate_rectangle)
{
  gromov::Rectangle rectangle({0,0},5,10);
  const double height = rectangle.getFrameRect().height;
  const double width = rectangle.getFrameRect().width;
  rectangle.rotate(90);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, width, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_rotate_composite_shape)
{
  gromov::CompositeShape array;
  std::shared_ptr<gromov::Shape> rect = std::make_shared<gromov::Rectangle>(gromov::Rectangle({-3, -5}, 4, 4));
  std::shared_ptr<gromov::Shape> rect1 = std::make_shared<gromov::Rectangle>(gromov::Rectangle({4, 2}, 4, 4));
  array.addShape(rect);
  array.addShape(rect1);
  gromov::rectangle_t frameRect = array.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.pos.x, 0.5, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.pos.y, -1.5, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, 11, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.height, 11, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_layering)
{
  std::shared_ptr<gromov::Shape> rect = std::make_shared<gromov::Rectangle>(gromov::Rectangle({1.0, 1.0}, 10.0, 10.0));
  std::shared_ptr<gromov::Shape> rect1 = std::make_shared<gromov::Rectangle>(gromov::Rectangle({20.0, 20.0}, 10.0, 10.0));
  std::shared_ptr<gromov::Shape> circle = std::make_shared<gromov::Circle>(gromov::Circle(10, {10,10}));
  gromov::CompositeShape cs;
  cs.addShape(rect);
  cs.addShape(rect1);
  cs.addShape(circle);
  gromov::Matrix matrix = cs.makePartition();
  BOOST_CHECK(matrix.getShapeCount(0) == 2);
  BOOST_CHECK(matrix.getShapeCount(1) == 1);
}
