#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <math.h>

#include "CImg.h"
#include "Figure.h"
#include "Image.h"
#include "EdgeDetector.h"
#include "Point2D.h"
#include "shapePt.h"

#define MILLION (float) 1000000
#define SLOPE(p1, p2) (double)((p2.y-p1.y)/(p2.x-p1.x))
#define NORM(coord, sz) (float) coord*1000000 / (float) sz

//#ifndef
#define DISTANCE(x1, y1, x2, y2) (double) sqrt(pow(x1-x2, 2) + pow(y1-y2, 2))
//#endif

using namespace std;
using namespace cimg_library;

struct ptOr
{
  Point2D pt;
  int orientation;
  unsigned int index;
};


struct ptInd
{
  Point2D pt;
  int index;
};

inline bool operator==(const ptInd &p1, const Point2D &p2) {
  return ((p1.pt.x == p2.x) && (p1.pt.y == p2.y));}


class FiguresExtractor
{
private:
	int hgt, wdt, edgesAlgorithm;
	EdgeDetector ed;
  vector<Point2D> borderPts, tempV;
  Image * image;
  //vector<vector<Point2D> > borderPtFgV;
  bool curDetection, dbg;

public:
	FiguresExtractor(bool c=true, int h=0, int w=0);
  //~FiguresExtractor();
	FiguresExtractor(Image * img);
  void setSourceImage(Image *img);
  void clear(void);
	void Extract(void);
	vector<Point2D> extractPoints(void);
  vector<ptOr> getNeighbours(Point2D pt);
  vector<ptOr> getNeighbours(ptOr po);
  int findClosedBorder(vector<vector<Point2D> > * completed, int prvInd, ptInd pi, vector<Point2D> rest, Point2D initialPt);
  void arrangeBordersBT(vector<vector<Point2D> > *v);
  void arrangeBorders(vector<vector<Point2D> > *v);
	vector<int> findVertices(vector<Point2D> iv);
  vector<int> findVerticesAlt(vector<Point2D> iv);
  vector<ptInd> improveVertices(vector<Point2D> vec_ordXY, vector<int> indices);
  vector<shapePt> findSegments(vector<ptInd> vert_final, vector<Point2D> vec_ordXY);
  bool pointInPolygon(Point2D * p, vector<Point2D> * pol);
  bool pointInPolygon(shapePt * p, vector<shapePt> * pol);
  float pixelLightness(float * crgb);
  double slope(Point2D p1, Point2D p2);
  void setEdgeAlgorithm(int ea = 0);
  //float[] rgb2hsv(float * crgb);
	//X refinaTramos(X, X, X);
	//vPt2D image2pixels(void);
};

