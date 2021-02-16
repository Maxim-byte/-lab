#include <iostream>
#include <iterator>
#include <algorithm>
#include "shape.hpp"
#include "processing-data.hpp"
#include "functor.hpp"

void secondTask()
{
  std::vector<shape_t> shapes{std::istream_iterator<shape_t>(std::cin), std::istream_iterator<shape_t>()};
  if(!std::cin.eof() && !std::cin.good())
  {
    throw std::ios::failure("Fail while reading");
  }
  SumShapesCategories sumShapesCategories;
  sumShapesCategories(shapes);
  deletePentagon(shapes);
  std::vector<Point> points = getPointsFromShapes(shapes);
  sort(shapes);

  sumShapesCategories.print(std::cout);
  
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout));

  std::cout << "\nShapes:\n";
  
  for (const auto &shape : shapes)
  {
    std::cout << shape.points.size() << " ";
    std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<Point>(std::cout));
    std::cout << '\n';
  }
}
