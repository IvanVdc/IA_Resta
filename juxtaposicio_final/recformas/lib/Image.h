#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Figure.h"
#include "CImg.h"
#include "Point2D.h"
#include "RS.h"

using namespace std;
using namespace cimg_library;

class Image
{
public:
  string fName, fResName;
  vector<Figure> figV;
  int nfigures;
  int hgt, wdt;
  int centroid_x;
  int centroid_y;
  double area;
  CImg<float> img;
  CImg<float> imgRes;
  vector<vector<Point2D> > borderPtFgV;
  vector<RS> vRS;

  Image() {}
  Image(string f, CImg<float> srcImg);
  void setSourceImg(string f, CImg<float> srcImg);
  string fileName();
	void drawID(void);

  //Slopes
  void obtaining_all_slopes_for_each_figure(void);

  //Topology
  void obtaining_neighbours_of_all_figures(void);
  void obtaining_topological_relations(void);

  //Size
  void obtaining_compared_size_wrt_image();
  void obtaining_compared_size_wrt_figures();
  void obtaining_compared_size_wrt_neighbours();

  //Fixed Orientation
  void obtaining_fixed_orientation_wrt_image();
  void obtaining_fixed_orientation_of_all_vertices();
  void obtaining_fixed_orientation_wrt_image_centroid_version();
  void obtaining_fixed_orientation_wrt_figures();
  void obtaining_fixed_orientation_wrt_figures_object_centred();
  void obtaining_fixed_orientation_wrt_figures_centroid_version();
  void obtaining_fixed_orientation_of_vertices_wrt_centroid();
  void obtaining_fixed_orientation_wrt_neighbours();

  //Compared distance
  void obtaining_numerical_distances();
  void obtaining_qualitative_distances();
  void obtaining_compared_distances();

  //Relative Orientation
  QRelative_Orientation_Type obtaining_relative_orientation_of_a_vertex(Point2D vertex, Point2D fig_a_centroid, Point2D fig_b_centroid);
  void obtaining_relative_orientation_of_a_figure(unsigned int fig_id, unsigned int id_fig_a, unsigned int id_fig_b);
  void obtaining_all_RS_in_the_image();
  void obtaining_all_RS_in_the_image_without_inverses();
  void obtaining_all_relative_orientations();
  void obtaining_all_relative_orientations_wrt_neighbours();

  void printFile_Qdescription();
};
