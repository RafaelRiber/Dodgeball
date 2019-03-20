#include <cmath>
#include "tools.h"

///////////////////////////////////////////////////////////////////////

Point::Point(double x_in, double y_in){
  x = x_in;
  y = y_in;
}

Point::Point(Cell c, unsigned int nbCells, unsigned int sideSize){
  //créer un point en haut à gauche de la case spécifiée
  unsigned int cellX(0);
  unsigned int cellY(0);
  c.getCoordinates(cellX, cellY);
  x = (cellX * ((double)sideSize/nbCells)) - (sideSize/2.);
  y = (cellY * ((double)sideSize/nbCells)) - (sideSize/2.);
}

Point::Point(Point const& point) : x(point.x), y(point.y) {}

void Point::getCoordinates(double &x_out, double &y_out) const {
  x_out = x;
  y_out = y;
}

bool Point::inBoundary(double boundX, double boundY){
  if (x < -boundX or x > boundX or y < -boundY or y > boundY){
    return false;
  }
  else{
    return true;
  }
}

///////////////////////////////////////////////////////////////////////

Cell::Cell(unsigned int x_in, unsigned int y_in)
  : x(x_in), y(y_in)
  {}

Cell::Cell(Point p, unsigned int nbCells, unsigned int sideSize){
  //créer une case ayant comme emplacement la case où le point est situé
  double pointX(0);
  double pointY(0);
  p.getCoordinates(pointX, pointY);
  x = floor(((double)nbCells/sideSize) * (pointX + (sideSize/2.)));
  y = floor(((double)nbCells/sideSize) * (pointY + (sideSize/2.)));
}

void Cell::getCoordinates(unsigned int &x_out, unsigned int &y_out){
  x_out = x;
  y_out = y;
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

double Segment::getLenght() const {
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

///////////////////////////////////////////////////////////////////////

Rectangle::Rectangle (Point a_in, Point b_in, Point c_in, Point d_in)
  : a(a_in), b(b_in), c(c_in), d(d_in)
  {}


Rectangle::Rectangle (Cell cell, unsigned int nbCells, unsigned int sideSize)
  : a(Point(0,0)), b(Point(0,0)), c(Point(0,0)), d(Point(0,0))
{
  double x(0) ,y(0);
  double cellSize = (double)sideSize/nbCells;
  Point(cell, nbCells, sideSize).getCoordinates(x,y);

  a = Point(x           , y);
  b = Point(x + cellSize, y);
  c = Point(x + cellSize, y + cellSize);
  d = Point(x           , y + cellSize);
}
