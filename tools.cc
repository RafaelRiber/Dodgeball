// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "tools.h"

Point::Point(double x_in, double y_in){
  x = x_in;
  y = y_in;
}

Point::Point(Cell c, unsigned int nbCells, unsigned int sideSize){
  //créer un point en haut à gauche de la case spécifiée
  int cellX(0);
  int cellY(0);
  c.getCoordinates(cellX, cellY);
  if(cellX == CELL_ERROR_COORDINATES && cellY == CELL_ERROR_COORDINATES){
    std::cout<<"ERROR : cannot convert cell (-1,-1) (CELL_ERROR) to a point";
    std::cout<<std::endl;
    exit(0);
  }
  x = (cellY *  ((double)sideSize/nbCells)) - (sideSize/2.);
  y = (cellX * (-(double)sideSize/nbCells)) + (sideSize/2.);
}

Point::Point(Point const& point) : x(point.x), y(point.y) {}

void Point::getCoordinates(double &x_out, double &y_out) const {
  x_out = x;
  y_out = y;
}

bool Point::inBoundary(double boundaryX, double boundaryY){
  if (x < -boundaryX or x > boundaryX or y < -boundaryY or y > boundaryY){
    return false;
  }
  else{
    return true;
  }
}

Point Point::operator+(Vector v){
  return Point(x+v.getX(), y+v.getY());
}

Point Point::operator-(Vector v){
  return Point(x-v.getX(), y-v.getY());
}

void Point::dump(){
  double x,y;
  getCoordinates(x,y);
  std::cout<<std::setprecision(2)<<std::fixed<<" ("<<x<<", "<<y<<") ";
}

///////////////////////////////////////////////////////////////////////

Cell::Cell(int x_in, int y_in): x(x_in), y(y_in){}

Cell::Cell(Point p, unsigned int nbCells, unsigned int sideSize){
  //créer une case ayant comme emplacement la case où le point est situé
  double pointX(0);
  double pointY(0);
  p.getCoordinates(pointX, pointY);
  x = floor((-(double)nbCells/sideSize) * (pointY - (sideSize/2.)));
  y = floor(( (double)nbCells/sideSize) * (pointX + (sideSize/2.)));
}


Point Cell::getCenterCell(int nbCells, double sideSize){
  return Point(*this, nbCells, sideSize) + Vector( sideSize/(2.*nbCells),
                                                  -sideSize/(2.*nbCells));
}

void Cell::getCoordinates(unsigned int &x_out, unsigned int &y_out){
  x_out = x;
  y_out = y;
}

void Cell::getCoordinates(int &x_out, int &y_out){
  x_out = x;
  y_out = y;
}

bool Cell::isAdjacentTo(const Cell c) const{
  return ( (x==c.x-1 || x==c.x+1)&& y==c.y ) ||
         ( (y==c.y-1 || y==c.y+1)&& x==c.x );
}

bool Cell::isDiagonalyAdjacentTo(const Cell c) const{
  return (x==c.x-1 || x==c.x+1) && (y==c.y-1 || y==c.y+1);
}

bool Cell::operator==(Cell c){
  unsigned int cX,cY;
  c.getCoordinates(cX,cY);
  return (cX == x && cY == y);
}
void reset_targets();

void Cell::dump(){
  int x,y;
  getCoordinates(x,y);
  std::cout<<" ("<<x<<", "<<y<<") ";
}

///////////////////////////////////////////////////////////////////////

Vector::Vector(double x_in, double y_in){
  x = x_in;
  y = y_in;
}


Vector::Vector(Point origin, Point end){
  double origin_x(0), origin_y(0);
  double end_x(0), end_y(0);
  origin.getCoordinates(origin_x, origin_y);
  end.getCoordinates(end_x, end_y);

  x = end_x - origin_x;
  y = end_y - origin_y;
}

double Vector::getX(){ return x;}
double Vector::getY(){ return y;}

double Vector::getNorm(){
  return sqrt(pow(x, 2) + pow(y, 2));
}

double Vector::getAngle(){
  if(x >= 0 && y >= 0){
    return atan(y/x);
  }else if(x >= 0 && y < 0){
    return atan(x/abs(y))+(3*M_PI)/2.;
  }else if(x < 0 && y >= 0){
    return atan(abs(x)/y) + M_PI/2;
  }else{
    return atan(y/x)+M_PI;
  }
}

void Vector::setNorm(double new_norm){
  double angle(0);

  if(x == 0){
    if(y > 0){
      angle = M_PI/2;
    }else if(y < 0){
      angle = -M_PI/2;
    }else if(y == 0){
      return;
    }
  }else{
    angle = atan(y/x);
}

  if(x>=0){
    x =   new_norm * cos(angle);
    y =   new_norm * sin(angle);
  }else{
    x = - new_norm * cos(angle);
    y = - new_norm * sin(angle);
  }
}

void Vector::dump(){
  double x = getX();
  double y = getY();
  std::cout<<" ("<<x<<", "<<y<<") ";
}

///////////////////////////////////////////////////////////////////////

Segment::Segment(Point start_in, Point end_in)
: start(start_in), end(end_in){}

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

Circle::Circle(Point center_in, double radius_in)
: center(center_in){
  radius = radius_in;
}

void Circle::getCenter(double &x_out, double &y_out) const {
  center.getCoordinates(x_out, y_out);
}

double Circle::getRadius() const{
  return radius;
}

bool Circle::isInCircle(Point p){
  double pointX, pointY;
  double centerX, centerY;
  p.getCoordinates(pointX, pointY);
  center.getCoordinates(centerX, centerY);
  Vector PolarCoord(pointX-centerX, pointY-centerY);

  if(PolarCoord.getNorm() <= radius){
    return true;
  }else{
    return false;
  }
}

bool Circle::circleCollision(Circle c){
  return Segment(center, c.center).getLength() < (radius + c.radius);
}

///////////////////////////////////////////////////////////////////////

Square::Square(double x_in, double y_in, double side_in){
  x = x_in;
  y = y_in;
  side = side_in;
}

///////////////////////////////////////////////////////////////////////

Rectangle::Rectangle (Point a_in, Point b_in, Point c_in, Point d_in)
: a(a_in), b(b_in), c(c_in), d(d_in) {}


Rectangle::Rectangle (Cell cell, unsigned int nbCells, unsigned int sideSize)
  : a(Point(0,0)), b(Point(0,0)), c(Point(0,0)), d(Point(0,0)) {
  double x(0) ,y(0);
  double cellSize = (double)sideSize/nbCells;
  Point(cell, nbCells, sideSize).getCoordinates(x,y);

  a = Point(x           , y);
  b = Point(x + cellSize, y);
  c = Point(x + cellSize, y + cellSize);
  d = Point(x           , y + cellSize);
  }

bool Rectangle::isInRectangle(Point p){
  double pointX,pointY;
  double upperleftX , upperleftY;
  double lowerRightX, lowerRightY;
  p.getCoordinates(pointX,pointY);
  a.getCoordinates(upperleftX, upperleftY);
  c.getCoordinates(lowerRightX, lowerRightY);

  if (pointX >= upperleftX  && pointX <= lowerRightX  &&
      pointY >= lowerRightY && pointY <= upperleftY)  {
      return true;
  }else{
      return false;
  }
}
