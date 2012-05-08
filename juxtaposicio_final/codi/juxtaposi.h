#ifndef juxtaposi_H
#define juxtaposi_H



#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>


using namespace std;

class juxtaposi {
public:
    juxtaposi();
    juxtaposi(string fig1_, string fig2_);
    ~juxtaposi();
    void operacio(int r1v1_, int r1v2_, int r2v1_, int r2v2_);
    friend ostream & operator<<(ostream& os, juxtaposi &s);
    int IdentificaCostat(string cost);
    int IdentificaConcv(string concv, string angl);
    int IdentificaAngle(string angl);

    string posicion_final(string desp_horit,string desp_vert, string pos_forats[], int num_fig);


    string fig1;
    string fig2;
    string result;

};

#endif


