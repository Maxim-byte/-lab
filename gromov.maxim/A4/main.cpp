#include<iostream>
#include <memory>
#include"circle.hpp"
#include"rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  try
  {
    std::cout << "Circle test:\n";
    gromov::point_t point = {11.1, 11.2};
    gromov::Circle circle(10, point);

    std::cout << "Area of circle is " << circle.getArea() << "\n"
        << "Radius of circle is " << circle.getRadius() << "\n"
        << "Coordinates of circle before moving by changing coordinate x = " << circle.getCentre().x
        << ",  y = " << circle.getCentre().y << "\n";
    circle.move(100, 200);

    std::cout << "Coordinates of circle after moving by changing coordinate x = "
        << circle.getCentre().x << ",  y = " << circle.getCentre().y << "\n"
        << "Frame of circle is height x = " << circle.getFrameRect().height
        << ",  y = " << circle.getFrameRect().width << "\n"
        << "Coordinates of circle before moving by changing centre x = "
        << circle.getCentre().x << ",  y = " << circle.getCentre().y << "\n";

    gromov::point_t point1 = {75, 80};
    circle.move(point1);

    std::cout << "Coordinates of circle after moving by changing centre  x = "
        << circle.getCentre().x << ",  y = " << circle.getCentre().y << "\n"
        << "Rectangle test:" << "\n";

    gromov::Rectangle rect(point, 11.3, 11.3);

    std::cout << "Area of rectangle is " << rect.getArea() << "\n"
        << "Width is " << rect.getWidth() << "  Height is " << rect.getHeight() << "\n"
        << "Centre coordinate is x = " << rect.getCentre().x << ",  y = " << rect.getCentre().y << "\n"
        << "Frame of rectangle is height x = " << rect.getFrameRect().height
        << ",  y = " << rect.getFrameRect().width << "\n"
        << "Coordinates of rectangle before moving by changing coordinate x = "
        << rect.getCentre().x << ",  y = " << rect.getCentre().y << "\n";

    rect.move(1000, 200);

    std::cout << "Coordinates of rectangle after moving by changing coordinate x = "
        << rect.getCentre().x << ",  y = " << rect.getCentre().y << "\n"
        << "Coordinates of rectangle before moving by changing centre  x = "
        << rect.getCentre().x << ",  y = " << rect.getCentre().y << "\n";

    rect.move(point1);

    std::cout << "Coordinates of rectangle after moving by changing centre  x = "
        << rect.getCentre().x << ",  y = " << rect.getCentre().y << "\n"
        << "Polymorphism test:" << "\n";

    gromov::Shape *shape = &rect;

    std::cout << "Now in ptr of Shape is rectangle " << shape->getArea() << "\n";

    shape = &circle;
    
    std::cout << "Now in ptr of Shape is circle " << shape->getArea() << "\n"
        << "Scale test:\n" << "Circle radius before scaling " << circle.getRadius() << "\n";

    shape->scale(2.0);

    std::cout << "Circle radius after scaling with coefficient x2 " << circle.getRadius() << "\n"
        << "Rectangle height before scaling = " << rect.getHeight() << "\n"
        << "Rectangle width before scaling = " << rect.getWidth() << "\n";

    shape = &rect;
    shape->scale(2.0);

    std::cout << "Rectangle height after scaling = " << rect.getHeight() << "\n"
        << "Rectangle width after scaling = " << rect.getWidth() << "\n";

    std::cout << "CompositeShape test:" << "\n";

    gromov::CompositeShape array(2);
    gromov::CompositeShape array1;
    std::shared_ptr<gromov::Shape> rect1
      = std::make_shared<gromov::Rectangle>(gromov::Rectangle({1.0, 1.0}, 11.0, 10.0));
    std::shared_ptr<gromov::Shape> circle1 = std::make_shared<gromov::Circle>(circle);
    std::shared_ptr<gromov::Shape> rect2 = std::make_shared<gromov::Rectangle>(rect);
    array.addShape(circle1);
    array.addShape(rect2);
    array.addShape(rect1);
    array.scale(2.0);
    std::cout << "Zero element of array = " << array[0]->getArea() << "\n"
        << "First element of array = " << array[1]->getArea() << "\n"
        << "Second element of array = " << array[2]->getArea() << "\n";

    std::cout << "Common width of frame rect = " << array.getFrameRect().width << "\n"
        << "Common height of frame rect = " << array.getFrameRect().height << "\n"
        << "Array size = " << array.getSize() << "\n"
        << "Array capacity = " << array.getCapacity() << "\n";

    array1 = array;

    std::cout << "Copying array in array1\n" << "Array1 test:" << "\n"
        << "Capacity of array1 = " << array1.getCapacity() << "\n"
        << "Zero element of array1 = " << array1[0]->getArea() << "\n"
        << "First element of array = " << array1[1]->getArea() << "\n"
        << "Second element of array = " << array1[2]->getArea() << "\n";

    std::shared_ptr<gromov::Shape> rectangle = std::make_shared<gromov::Rectangle>(gromov::Rectangle({1,1},10,10));
    std::shared_ptr<gromov::Shape> rectangle1 = std::make_shared<gromov::Rectangle>(gromov::Rectangle({1,1},5,5));
    std::shared_ptr<gromov::Shape> rectangle2 = std::make_shared<gromov::Rectangle>(gromov::Rectangle({1000,1000},5,5));
    std::shared_ptr<gromov::Shape> rectangle3 = std::make_shared<gromov::Rectangle>(gromov::Rectangle({10000,10000},100,100));
    std::shared_ptr<gromov::Shape> compositeShape = std::make_shared<gromov::CompositeShape>(gromov::CompositeShape(array));

    array.addShape(rectangle);
    array.addShape(compositeShape);
    array.addShape(rectangle1);
    array.addShape(rectangle2);
    array.addShape(rectangle2);
    array.addShape(rectangle1);
    array.addShape(rectangle1);
    array.addShape(rectangle1);
    array.addShape(rectangle1);
    
    gromov::Matrix matrix = array.makePartition();
    matrix.printMatrixAreas(std::cout);
    std::cout << '\n' << matrix[0][0]->getArea() << '\n';
  }
  catch (const std::exception&exception)
  {
    std::cerr << exception.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
    return -2;
  }
  return 0;
}
