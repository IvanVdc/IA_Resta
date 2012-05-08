#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Image.h"

#define POINT_CURVATURE 2
#define EMPTY 101 //Usado para comparar con el conjunto vacio
#define LIMIT(n, szf, szv) (szf-(szv - n)+1)


//tablas
#define TABLE_KEC			1
#define TABLE_ANGLE_3			2
#define TABLE_CURVATURE_OR_ANGLE_5	3
#define TABLE_LENGTH			4
#define TABLE_CONVEXITY			5

//distancias maximas
#define MAX_DIST_KEC		3
#define MAX_DIST_A_OR_TC	4
#define MAX_DIST_L		6
#define MAX_DIST_C		1

//pesos
#define PESO_KEC    0.25
#define PESO_A_OR_TC    0.25
#define PESO_L        0.25
#define PESO_C        0.25


using namespace std;

class Similarity {
  public:

    Similarity();

    int index(QPoint *p,int option);

    float similarity_shape(Figure *fig1, Figure *fig2);

    float Levenshtein_distance(Figure *f1, Figure *f2);

    //float dissimilarity_between_points(Figure *f1, int i, Figure *f2, int j);
    float dissimilarity_between_points(QPoint qpt1, QPoint qpt2, float *dist_points, float *dist_angle_curvature, float *dist_length, float *dist_convexity);

    float dissimilarity_between_points_v2(QPoint qpt1, QPoint qpt2, float *dist_points, float *dist_angle_curvature, float *dist_length, float *dist_convexity);


    int minimum_of_3_distances (int value1, int value2, int value3);

    void aligment_matrix(Figure *f1, Figure *f2);


    //Distances between the qualitative concepts representing the kind of relevant
    //points detected in the shape of the objects
    int kind_edges_connected[5][5];

    //Angle
    int angle3[3][3];

    //Curves
    int curvature_angle5[5][5];

    //Length
    int length[7][7];

    //Convexity
    int convexity[2][2];


};
