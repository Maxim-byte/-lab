#define BOOST_TEST_MODULE mytest

#include <memory>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_composite_shape)
{
  gromov::CompositeShape array;
  BOOST_CHECK_THROW(array.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_index_operator_composite_shape)
{
  gromov::CompositeShape array;
  BOOST_CHECK_THROW(array[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_insert_composite_shape)
{
  gromov::CompositeShape array;
  std::shared_ptr<gromov::Shape> ptr = nullptr;
  BOOST_CHECK_THROW(array.addShape(ptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_delete_composite_shape)
{
  gromov::CompositeShape array;
  BOOST_CHECK_THROW(array.deleteShape(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_insert_composite_shape)
{
  gromov::CompositeShape array;
  std::shared_ptr<gromov::Shape> circle = std::make_shared<gromov::Circle>(gromov::Circle(10,{10,10}));
  array.addShape(circle);
  BOOST_CHECK(array[0] == circle);
}

BOOST_AUTO_TEST_CASE(test_delete_composite_shape)
{
  gromov::CompositeShape array;
  std::shared_ptr<gromov::Shape> circle = std::make_shared<gromov::Circle>(gromov::Circle(10,{10,10}));
  array.addShape(circle);
  BOOST_CHECK(array.getSize() == 1);
  array.deleteShape(0);
  BOOST_CHECK(array.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(test_get_capacity_composite_shape)
{
  const int capacity = 10;
  gromov::CompositeShape array(capacity);
  BOOST_CHECK(array.getCapacity() == capacity);
}

BOOST_AUTO_TEST_CASE(test_get_size_composite_shape)
{
  gromov::CompositeShape array;
   std::shared_ptr<gromov::Shape> circle = std::make_shared<gromov::Circle>(gromov::Circle(10,{10,10}));
  array.addShape(circle);
  BOOST_CHECK(array.getSize() == 1);
}

BOOST_AUTO_TEST_CASE(test_get_frame_composite_shape)
{
  gromov::CompositeShape array(1);
   std::shared_ptr<gromov::Shape> rect
      = std::make_shared<gromov::Rectangle>(gromov::Rectangle({1.0, 1.0}, 11.0, 10.0));
   std::shared_ptr<gromov::Shape> rect1
      = std::make_shared<gromov::Rectangle>(gromov::Rectangle({2.0, 2.0}, 12.0, 12.0));   
  array.addShape(rect);
  array.addShape(rect1);
  const double height = 12.0,
      width = 12.5;
  BOOST_CHECK_CLOSE(array.getFrameRect().height, height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(array.getFrameRect().width, width, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_area_composite_shape)
{
  std::shared_ptr<gromov::Shape> rect
      = std::make_shared<gromov::Rectangle>(gromov::Rectangle({1.0, 1.0}, 11.0, 10.0));
    std::shared_ptr<gromov::Shape> circle = std::make_shared<gromov::Circle>(gromov::Circle(10,{10,10}));
  gromov::CompositeShape array;
  array.addShape(circle);
  array.addShape(rect);
  const double sum_area = circle->getArea() + rect->getArea();
  BOOST_CHECK_CLOSE(array.getArea(), sum_area, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_move_composite_shape)
{
  std::shared_ptr<gromov::Shape> rect
      = std::make_shared<gromov::Rectangle>(gromov::Rectangle({1.0, 1.0}, 11.0, 10.0));
    std::shared_ptr<gromov::Shape> circle = std::make_shared<gromov::Circle>(gromov::Circle(10,{10,10}));
  gromov::CompositeShape array;
  array.addShape(circle);
  array.addShape(rect);
  const double x = 5.0,
      y = 5.0,
      rect_oldX = rect->getCentre().x,
      rect_oldY = rect->getCentre().y,
      circle_oldX = circle->getCentre().x,
      circle_oldY = circle->getCentre().y;
  array.move(x, y);
  BOOST_CHECK_CLOSE(circle->getCentre().x, x + circle_oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle->getCentre().y, y + circle_oldY, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect->getCentre().x, x + rect_oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect->getCentre().y, y + rect_oldY, ACCURACY_DOUBLE);
  array.move({x, y});
  BOOST_CHECK_CLOSE(array.getFrameRect().width, 24.5, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(array.getFrameRect().height, 24, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_composite_shape)
{
  std::shared_ptr<gromov::Shape> rect
      = std::make_shared<gromov::Rectangle>(gromov::Rectangle({1.0, 1.0}, 11.0, 10.0));
    std::shared_ptr<gromov::Shape> circle = std::make_shared<gromov::Circle>(gromov::Circle(10,{10,10}));
  gromov::CompositeShape array;
  array.addShape(circle);
  array.addShape(rect);
  const double area_rect = rect->getArea(),
      scale = 2.0,
      area_circle = circle->getArea();
  array.scale(scale);
  BOOST_CHECK_CLOSE(area_circle * scale * scale, circle->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area_rect * scale * scale, rect->getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_copy_composite_shape)
{
   std::shared_ptr<gromov::Shape> circle = std::make_shared<gromov::Circle>(gromov::Circle(10,{10,10}));
  gromov::CompositeShape array;
  array.addShape(circle);
  gromov::CompositeShape array1 = array;
  BOOST_CHECK_CLOSE(array[0]->getArea(), array[0]->getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_semantics_move_composite_shape)
{
   std::shared_ptr<gromov::Shape> circle = std::make_shared<gromov::Circle>(gromov::Circle(10,{10,10}));
  gromov::CompositeShape array;
  array.addShape(circle);
  const double area_circle = circle->getArea();
  gromov::CompositeShape array1(std::move(array));
  BOOST_CHECK_CLOSE(array1[0]->getArea(), area_circle, ACCURACY_DOUBLE);
  BOOST_CHECK_THROW(array[0], std::out_of_range);
}
