#include <cmath>
#include "tools.h"

///////////////////////////////////////////////////////////////////////

Point::Point(double x_in, double y_in){
  x = x_in;
  y = y_in;
}

Point::Point(Point const& point) : x(point.x), y(point.y) {}

void Point::getCoordinates(double &x_out, double &y_out) const {
  x_out = this->x;
  y_out = this->y;
}

bool Point::inBoundary(double boundaryX, double boundaryY){
  if (x < -boundaryX or x > boundaryX or y < -boundaryY or y > boundaryY){
    return false;
  }
  else{
    return true;
  }
}

///////////////////////////////////////////////////////////////////////

Vector::Vector(double x_in, double y_in){
  x = x_in;
  y = y_in;
}

double Vector::getNorm(){
  return sqrt(pow(x, 2) + pow(y, 2));
}

///////////////////////////////////////////////////////////////////////

Segment::Segment(Point start_in, Point end_in)
: start(start_in), end(end_in){
}

double Segment::getLength() const {
  double x_start, y_start, x_end, y_end;
  start.getCoordinates(x_start, y_start);
  end.getCoordinates(x_end, y_end);

  double deltaX = (x_end - x_start);
  double deltaY = (y_end - y_start);
  return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

///////////////////////////////////////////////////////////////////////

Circle::Circle(double x_in, double y_in, double radius_in)
: center(x_in, y_in){
  radius = radius_in;
}

void Circle::getCenter(double &x_out, double &y_out) const {
  center.getCoordinates(x_out, y_out);
}

double Circle::getRadius() const{
  return radius;
}

///////////////////////////////////////////////////////////////////////

Square::Square(double x_in, double y_in, double side_in){
  x = x_in;
  y = y_in;
  side = side_in;
}
