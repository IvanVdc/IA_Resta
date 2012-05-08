#pragma once

#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>
#include <string>
#include "Point2D.h"

//Zfalomir
#define LINE_LINE 	11
#define POINT_CURVATURE	2
#define	LINE_CURVE	12
#define	CURVE_LINE	21
#define	CURVE_CURVE	22

#define VERY_ACUTE_ANGLE	-2
#define ACUTE_ANGLE		-1
#define	RIGHT_ANGLE		0
#define OBTUSE_ANGLE		1
#define VERY_OBTUSE_ANGLE	2

#define VERY_PLANE_CURVE	-2
#define	PLANE_CURVE		-1
#define	SEMICIRCULAR_CURVE	0
#define	ACUTE_CURVE		1
#define	VERY_ACUTE_CURVE	2

#define CONCAVE		0
#define	CONVEX		1

#define STH_EDGE	-3
#define	H_EDGE		-2
#define	LTH_EDGE	-1
#define E_EDGE		0
#define	STD_EDGE	1
#define	D_EDGE		2
#define	LTD_EDGE	3


using namespace std;

class  QPoint {
public:

  Point2D pt;
  //Point2D maxC;
  int shape; //line-line: 11
             //curvature-point: 2
             //line-curve: 12
             //curve-line: 21
             //curve-curve: 22
  int angle;  //STRAIGHT - acute: -1, right-angled: 0, obtuse: 1
              //CURVE - very-plane: -2, plane: -1, semicircular: 0, 
								//acute: 1, very-acute: 2
  int convexity; //concave: 0, convex: 1
  int size; //sth: -3, h: -2, lth: -1, e: 0, std: 1, d: 2, ltd: 3 
  //vector<int> QDesc; /* De tamaño 3 que incluye [angle,convexity,size] */

  QPoint(void);
  QPoint(Point2D p, int sp=101, int a=101, int c=101, int sz=101);
  
  QPoint operator=(QPoint p);
  bool operator==(QPoint &p);
  friend ostream& operator<<(ostream& os, QPoint &p);
  bool QComparision(QPoint *p);
};
