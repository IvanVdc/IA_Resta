#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include "Point2D.h"
#include "shapePt.h"
#include "QPoint.h"
#include "utils.h"
#include "Slope.h"
#include "ComparedSize.h"
#include "FixedOrientation.h"
#include "RelativeOrientation.h"
#include "ComparedDistance.h"

#define	DISJOINT	0
#define	TOUCHING	1
#define INSIDE		2
#define CONTAINER	3
#define SAME		4

using namespace std;

enum QSize_wrt_Image_Type {none_size_wrt_image, small, medium, large};

class Figure
{
public:
  float RGB[3], RGBf[3];
  int HSV[3], HSL[3];
	Point2D centroid;//, centroid2;
  int id;
	double area;
  bool comp; //Determina si tiene elementos internos
  bool isIntern; //Determina si es un elemento interno
  int curves; //0: without_curves | 1: with_curves | 2: only_curves
  int ncomponents;
  int nvertices;
	int nqpts;
  bool regular; //Determina si es un poligono regular
  string color, description, name, VisualDescription, SpatialDescription;
  int convexity; //0: concave | 1: convex
  vector<Point2D> vertices, border;
	vector<shapePt> infoVertices;
  vector<Figure *> components, containers, neighbours;
  Figure * father;
	vector<QPoint> qualPtV;
  vector<Slope> slopesVector; //Vector de pendientes de cada figura para
															//encontrar lados paralelos

  //De momento sólo ids, después mirare si es necesario
  //incluir la figura entera
  //vector<Figure *> neighboursVector;

  //De momento dos vectores de identificadores, crearé una clase
  //cuando lo tenga implementado por niveles.
  vector<unsigned int> neighboursVector;
  vector<unsigned int> disjointsVector;

  vector<unsigned int> topologicalRelVector;
  vector<RS> vneighboursRS;

  QSize_wrt_Image_Type size_wrt_image;
  vector<ComparedSize> sizeVector_wrt_fig;

  vector<QFixed_Orientation_Type> VFixed_Orient_wrt_image;
  vector<FixedOrientation> VFixed_Orient_wrt_figures;

  //Nuevo enfoque: vector de orientaciones de todos los vértices con respecto al centroide de la figura. Esto es para detectar rotaciones.
  vector<QFixed_Orientation_Type> VFixed_Orient_vertices;

  vector<RelativeOrientation> VRelative_Orientations;

  //Vector de distancias entre la figura actual y todas las demás (fig_id = ind_vector).
  //Dichas distancias son la distancia euclídea entre los centroides.
  vector<float> distanceVector;
  vector<ComparedDistance> VCompared_distances;

	Figure(void);
	~Figure(void);
  Figure(vector<Point2D> v, int ident=0);
	void setArea(void);
	void setCentroid(void);
  void setCentroidAlt(void);
	void setAreaCentroid(void);
	Figure operator=(Figure f);
  void info2vertices(void);
  friend ostream& operator<<(ostream& os, Figure &f);
  //string stringDescription(void);
  //string stringDescriptionOriginal(void);
  void RGBtoHSV(void);
  void RGBtoHSL(void);

  string shapeStringDescription(void);
  string shapeStringDescriptionOriginal(void);
  string stringDescription_all(void);
  string stringVisualDescription(void);
  string stringSpatialDescription(void);
  string stringSpatialDescription_object_centred(void);

  void obtaining_all_RS_in_neighboursVector_without_inverses();
  void obtaining_all_RS_in_neighboursVector_with_inverses();
  void set_Size_wrt_Image(QSize_wrt_Image_Type size_tag);
  void set_slopesVector();
  void set_name();
  void set_regularity();
  int orientation_in_vector(QFixed_Orientation_Type fOrient);
  void adding_fixed_orient_wrt_image(QFixed_Orientation_Type fOrient);
  void simplifying_fixed_orient_wrt_image();
  void set_distance(unsigned int Fig_id, float distance);
};
