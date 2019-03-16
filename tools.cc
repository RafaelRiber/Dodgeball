#include <cmath>
#include "tools.h"

///////////////////////////////////////////////////////////////////////

Point::Point(double x_in, double y_in){
  x = x_in;
  y = y_in;
}

void Point::getCoordinates(double &x_out, double &y_out) const {
  x_out = this->x;
  y_out = this->y;
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

Segment::Segment(double x_s_in, double y_s_in, double x_e_in, double y_e_in){
  x_start = x_s_in;
  y_start = y_s_in;
  x_end = x_e_in;
  y_end = y_e_in;
}

double Segment::getLenght() const {
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
