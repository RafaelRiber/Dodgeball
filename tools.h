// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include "define.h"

class Cell;
class Vector;

class Point {
public:
  Point(double x_in, double y_in);
  Point(Point const& point);
  Point(Cell c, unsigned int nbCells, unsigned int sideSize);

  void getCoordinates (double &x_out, double &y_out) const;
  bool inBoundary(double boundaryX, double boundaryY);
  Point operator+(Vector v);
  Point operator-(Vector v);

  void dump();
private:
  double x, y;
};

class Cell {
public:
  Cell(int x_in, int y_in);
  Cell(Point p, unsigned int nbCells, unsigned int sideSize);
  Point getCenterCell(int nbCells, double sideSize);
  void getCoordinates(unsigned int & x_out, unsigned int & y_out);
  void getCoordinates(int & x_out, int & y_out);

  bool isAdjacentTo(const Cell c) const;
  bool isDiagonalyAdjacentTo(const Cell c)const;
  bool operator==(Cell c);
  void dump();
private:
  unsigned int x;
  unsigned int y;
};

class Vector {
public:
  Vector(double x_in, double y_in);
  Vector(Point origin, Point end);
  void getCoordinates (double &x_out, double &y_out) const;
  double getX();
  double getY();
  double getNorm();
  double getAngle();
  void setNorm(double new_norm);
  void dump();
private:
  double x, y;
};

class Segment {
public:
  Segment(Point start_in, Point end_in);
  double getLength() const;

private:
  Point start, end;
};

class Circle{
public:
  Circle(double x, double y, double radius);
  Circle(Point center_in, double radius_in);
  void getCenter(double &x_out, double &y_out) const;
  double getRadius() const;
  bool isInCircle(Point p);
  bool circleCollision(Circle c);

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
  Rectangle(Point a_in, Point b_in, Point c_in, Point d_in);
  Rectangle(Cell cell, unsigned int nbCells, unsigned int sideSize);
  bool isInRectangle(Point p);
private:
  Point a;
  Point b;
  Point c;
  Point d;
};

#endif
