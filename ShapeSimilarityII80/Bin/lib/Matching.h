#pragma once

#include <vector>
#include <string>
#include <iostream>


#include "Image.h"
#include "Figure.h"
#include "Point2D.h"
#include "QPoint.h"
#include "shapePt.h"


using namespace std;

class Matching {
  public:
    Image * map;
    Figure * fig;
    vector<bool> matched; //El indice corresponde con el orden de las figuras en map
		vector<int> fid; //El indice corresponde con el orden de las figuras en map
    int nmatched; //Numero de encontradas en map
		int version;
    bool completed;
    
    Matching();
    Matching(Image * im);
    void clear(void);
    void setMap(Image * im);
		void setVersion(int v);
    int qualitativeMatch(Figure * f);
    bool figureComparision(Figure * f1, Figure * f2);
    bool QPointComparision(QPoint * p1, QPoint * p2);
		void drawResult(string fResName);
};
