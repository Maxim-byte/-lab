#include<iostream>
#include"circle.hpp"
#include"rectangle.hpp"

int main()
{
  try
  {
    std::cout << "Circle test:" << std::endl;
    gromov::point_t point = {11.1, 11.2};
    gromov::Circle circle(10, point);

    std::cout << "Area of circle is " << circle.getArea() << std::endl
      << "Radius of circle is " << circle.getRadius() << std::endl
      << "Coordinates of circle before moving by changing coordinate x = " << circle.getCentre().x
      << ",  y = " << circle.getCentre().y << std::endl;
    circle.move(100, 200);

    std::cout << "Coordinates of circle after moving by changing coordinate x = "
      << circle.getCentre().x << ",  y = " << circle.getCentre().y << std::endl
      << "Frame of circle is height x = " << circle.getFrameRect().height
      << ",  y = " << circle.getFrameRect().width << std::endl
      << "Coordinates of circle before moving by changing centre x = "
      << circle.getCentre().x << ",  y = " << circle.getCentre().y << std::endl;
    gromov::point_t point1 = {75, 80};
    circle.move(point1);

    std::cout << "Coordinates of circle after moving by changing centre  x = "
      << circle.getCentre().x << ",  y = " << circle.getCentre().y << std::endl
      << "Rectangle test:" << std::endl;

    gromov::Rectangle rect(point, 11.3, 11.3);

    std::cout << "Area of rectangle is " << rect.getArea() << std::endl
      << "Width is " << rect.getWidth() << "  Height is " << rect.getHeight() << std::endl
      << "Centre coordinate is x = " << rect.getCentre().x << ",  y = " << rect.getCentre().y << std::endl
      <<  "Frame of rectangle is height x = " << rect.getFrameRect().height
      << ",  y = " << rect.getFrameRect().width << std::endl
      << "Coordinates of rectangle before moving by changing coordinate x = "
      << rect.getCentre().x << ",  y = " << rect.getCentre().y << std::endl;

    rect.move(1000, 200);

    std::cout << "Coordinates of rectangle after moving by changing coordinate x = "
      << rect.getCentre().x << ",  y = " << rect.getCentre().y << std::endl
      << "Coordinates of rectangle before moving by changing centre  x = "
      << rect.getCentre().x << ",  y = " << rect.getCentre().y << std::endl;

    rect.move(point1);

    std::cout << "Coordinates of rectangle after moving by changing centre  x = "
      << rect.getCentre().x << ",  y = " << rect.getCentre().y << std::endl
      << "Polymorphism test:" << std::endl;

    gromov::Shape* shape = &rect;

    std::cout << "Now in ptr of Shape is rectangle " << shape->getArea() << std::endl;
    
    shape = &circle;

    std::cout << "Now in ptr of Shape is circle " << shape->getArea() << std::endl
      << "Scale test:" << std::endl << "Circle radius before scaling " << circle.getRadius() << std::endl;

    shape->scale(2.0);

    std::cout << "Circle radius after scaling with coefficient x2 " << circle.getRadius() << std::endl
      << "Rectangle height before scaling = " << rect.getHeight() << std::endl
      << "Rectangle width before scaling = " << rect.getWidth() << std::endl;

    shape = &rect;

    shape->scale(2.0);

    std::cout << "Rectangle height after scaling = " << rect.getHeight() << std::endl
      << "Rectangle width after scaling = " << rect.getWidth() << std::endl;
  }
  catch(const std::invalid_argument&exception)
  {
    std::cerr << exception.what() << std::endl;
    return 1;
  }
  catch(...)
  {
    std::cerr << "Error:Unknown problem" << std::endl;
    return 2;
  }
  return 0;
}
