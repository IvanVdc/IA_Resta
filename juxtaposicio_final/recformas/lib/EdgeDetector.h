#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <assert.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "CImg.h"
#include "Point2D.h"

#include "segment/segment-image.h"
#include "segment/pnmfile.h"

using namespace std;
using namespace cimg_library;

class EdgeDetector
{
private:
	//vector<Point2D> borderPts;
  CImg<float> * in;
	CImg<float> inGS, out, outS, outG, outO, outT, outNMS;
  int wdt, hgt;
  float sigma, threshold;
  int support;

public:
	EdgeDetector(void);
	//~EdgeDetector(void);
  void clear(void);
  void setSrcImg(CImg<float> * srcImg);
  vector<Point2D> Detect(int ea = 0);
  int Canny(vector<Point2D> * borderPts);
  int Felzenswalb(float sigma, int k, int min, vector<vector<Point2D> > * v);
  void GaussianSmoothing(void);
  void CannyDiscrete(vector<Point2D> * borderPts);
  void findBorders(image<rgb> * img, vector<vector<Point2D> > * v);
};
