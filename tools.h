#ifndef TOOLS_H
#define TOOLS_H

class Point {
public:
  Point(double x_in, double y_in);
  void getCoordinates (double &xOut, double &yOut) const;
private:
  double x, y;
};

class Vector {
public:

private:
  double x, y;
};

class Circle {
public:

private:
  double center, radius;
};

class Square {
public:

private:

};

#endif
