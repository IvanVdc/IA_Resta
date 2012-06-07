#pragma once

#include <string>
#include <iostream>

#include "Point2D.h"
//#include "FiguresExtractor.h"


using namespace std;

float MIN(float * v);
float MAX(float * v);

inline bool operator==(const Point2D &p1, const Point2D &p2) {
  return ((p1.x == p2.x) && (p1.y == p2.y));}

//inline bool operator==(const ptInd &p1, const Point2D &p2) {
//  return ((p1.pt.x == p2.x) && (p1.pt.y == p2.y));}
