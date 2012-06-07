#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "Point2D.h"
#include "Image.h"
#include "Figure.h"
#include "QPoint.h"
#include "shapePt.h"


using namespace std;


class QualitativeDescriptor
{
private:
  bool dbg;
	int version;
  Image * img;

public:
  QualitativeDescriptor(void);
  //~QualitativeDescriptor(void);
  QualitativeDescriptor(Image * image);
  QualitativeDescriptor(Image * image, int vers);

  void clear(void);
  void setSourceImage(Image * image);
	void setVersion(int vers);
  void generateDescription(bool orientation = false, Image * im = NULL);
  QPoint describeStraight(shapePt prvPt, shapePt actPt, shapePt rearPt);
  QPoint describeCurve(shapePt prvPt, shapePt actPt, shapePt rearPt);
  string HSV2qColor(int * hsv);
  //bool pointInPolygon(Point2D * p, vector<Point2D> * pol);
};
