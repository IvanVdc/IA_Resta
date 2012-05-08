#pragma once

#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>

//#define ROUND(fp) (long)((fp) >= 0 ? (fp) + 0.5 : (fp) - 0.5)

using namespace std;

class  Point2D {
public:

  double x, y;


  Point2D(void);
  Point2D(double ix, double iy);
  
  Point2D operator=(Point2D p);
  Point2D operator+(Point2D &p);
  Point2D operator-(Point2D &p);
  Point2D operator*(Point2D &p);
  Point2D operator+=(Point2D &p);
  Point2D operator-=(Point2D &p);
  Point2D operator*=(Point2D &p);
  bool operator==(Point2D &p);
  bool operator!=(Point2D &p);
  friend ostream& operator<<(ostream& os, Point2D &p);
  //bool operator==(Point2D p);
  //Point2D menos(Point2D &p);
  //Point2D mas(Point2D &p);
  //Point2D producto(Point2D &p);
  Point2D productoEscalar(double p);
  Point2D vectorUnitario();
  //Point2D round();
  double modulo();
  //bool equals(Point2D &c);
  double moduloProductoVectorial(Point2D &p);
  
  int getX();
  int getY();
  
};
