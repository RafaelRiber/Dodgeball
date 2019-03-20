#ifndef TOOLS_H
#define TOOLS_H

class Cell;

class Point {
public:
  Point(double x_in, double y_in);
  Point(Point const& point);
  Point(Cell c, unsigned int nbCells, unsigned int sideSize);
  void getCoordinates (double &x_out, double &y_out) const;
  bool inBoundary(double boundX, double boundY);
private:
  double x, y;
};

class Cell {
public:
  Cell(unsigned int x_in, unsigned int y_in);
  Cell(Point p, unsigned int nbCells, unsigned int sideSize);
  void getCoordinates(unsigned int & x_out, unsigned int & y_out);
private:
  unsigned int x;
  unsigned int y;
};

class Vector {
public:
  Vector(double x_in, double y_in);
  void getCoordinates (double &x_out, double &y_out) const;
  double getNorm();
private:
  double x, y;
};

class Segment {
public:
  Segment(Point start_in, Point end_in);
  double getLenght() const;

private:
  Point start, end;
};

class Circle{
public:
  Circle(double x, double y, double radius);
  void getCenter(double &x_out, double &y_out) const;
  double getRadius() const;

private:
  Point center;
  double radius;
};

class Square {
public:
  Square(double x_in, double y_in, double side_in);
private:
  double x, y, side;
};

class Rectangle {
public:
  Rectangle (Point a_in, Point b_in, Point c_in, Point d_in);
  Rectangle (Cell cell, unsigned int nbCells, unsigned int sideSize);
private:
  Point a;
  Point b;
  Point c;
  Point d;
};

#endif
