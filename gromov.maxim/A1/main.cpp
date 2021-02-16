#include<iostream>
#include"circle.hpp"
#include"rectangle.hpp"

int main()
{
  try
  {
    std::cout << "Circle test:" << std::endl;
    point_t point = {11.1,11.2};
    Circle circle(100.1, point);
    std::cout << "Area of circle is " << circle.getArea() << std::endl
      << "Radius of circle is " << circle.getRadius() << std::endl
      << "Coordinates of circle before moving by changing coordinate x = " << circle.getCentre().x
      << ",  y = " << circle.getCentre().y << std::endl;
    circle.move(100,200);
    std::cout << "Coordinates of circle after moving by changing coordinate x = "
      << circle.getCentre().x << ",  y = " << circle.getCentre().y << std::endl
      << "Frame of circle is height x = " << circle.getFrameRect().height
      << ",  y = " << circle.getFrameRect().width << std::endl
      << "Coordinates of circle before moving by changing centre x = "
      << circle.getCentre().x << ",  y = " << circle.getCentre().y << std::endl;
    point_t point1 = {75,80};
    circle.move(point1);
    std::cout << "Coordinates of circle after moving by changing centre  x = "
      << circle.getCentre().x << ",  y = " << circle.getCentre().y << std::endl
      << "Rectangle test:" << std::endl;
    Rectangle rect(point, 11.5, 11.3);
    std::cout << "Area of rectangle is " << rect.getArea() << std::endl
       << "Width is " << rect.getWidth() << "  Height is " << rect.getHeight() << std::endl
       << "Centre coordinate is x = " << rect.getPosition().x << ",  y = " << rect.getPosition().y << std::endl
       <<  "Frame of rectangle is height x = " << rect.getFrameRect().height
       << ",  y = " << rect.getFrameRect().width << std::endl
       << "Coordinates of rectangle before moving by changing coordinate x = "
       << rect.getPosition().x << ",  y = " << rect.getPosition().y << std::endl;
    rect.move(1000, 200);
    std::cout << "Coordinates of rectangle after moving by changing coordinate x = "
      << rect.getPosition().x << ",  y = " << rect.getPosition().y << std::endl
      << "Coordinates of rectangle before moving by changing centre  x = "
      << rect.getPosition().x << ",  y = " << rect.getPosition().y << std::endl;
    rect.move(point1);
    std::cout << "Coordinates of rectangle after moving by changing centre  x = "
      << rect.getPosition().x << ",  y = " << rect.getPosition().y << std::endl
        << "Polymorphism test:" << std::endl;
    Shape* shape = &rect;
    std::cout << "Now in ptr of Shape is rectangle " << shape->getArea() << std::endl;
    shape = &circle;
    std::cout << "Now in ptr of Shape is circle " << shape->getArea() << std::endl;
  }
  catch(const std::invalid_argument&)
  {
    std::cerr << "Error:invalid data" << std::endl;
    return 1;
  }
  catch(...)
  {
    std::cerr << "Error:Unknown problem" << std::endl;
    return 2;
  }
  return 0;
}
