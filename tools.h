#ifndef TOOLS_H
#define TOOLS_H

class Point {
public:
  Point(double x_in, double y_in);
  Point(Point const& point);
  void getCoordinates (double &x_out, double &y_out) const;
  bool inBoundary(double boundaryX, double boundaryY);
private:
  double x, y;
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

#endif
