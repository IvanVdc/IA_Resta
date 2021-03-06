#include "CImg.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>



using namespace cimg_library;

using namespace std;

int main(int argc, char *argv[]) {


    vector<string> args;
    vector<float> v_x;
    vector<float> v_y;

    for (int i = 0; i != argc; ++i) {
        args.push_back(string(argv[i]));
    }

    string ruta = args[1];


    char buf[200];

    strcpy(buf, ruta.c_str());

    string fitxer = args[2];


    char buf2[200];

    strcpy(buf2, fitxer.c_str());

    /*
    int n_ver=atoi(args[3].c_str());
    int pos=4;
     for (int aux=0;aux<n_ver;aux++){
    v_x.push_back(atoi(args[pos].c_str()));
    pos++;
    v_y.push_back(atoi(args[pos].c_str()));
    pos++;
    }
     */
	char auxi[128];
    int opcio = atoi(args[3].c_str());
    cout << opcio << endl;
    if (opcio == 1) {
        ofstream fs("vertex1.txt");

        ifstream fe("vertex.txt");
        char cadena[128];
        // Leeremos mediante getline, si lo hiciéramos
        // mediante el operador >> sólo leeríamos
        // parte de la cadena:
        fe.getline(cadena, 128);
        cout << cadena << "LLL";
        fs << cadena << endl;
        int n_ver = atoi(cadena);
        cout << n_ver << "LLL";
        for (int aux = 0; aux < n_ver+1; aux++) { // 
            char aux_x[128], aux_y[128];
            fe.getline(aux_x, 128);
            v_x.push_back(atoi(aux_x));
            fe.getline(aux_y, 128);
            v_y.push_back(atoi(aux_y));
            fs << aux_x << endl;
            fs << aux_y << endl;

        }

	fe.getline(auxi, 128);
         
            fs << auxi << endl;
fe.getline(auxi, 128);

           fs << auxi << endl;
fe.getline(auxi, 128);

          fs << auxi << endl;
        fs.close();
        fe.close();


    } else {

        ofstream fs("vertex2.txt");

        ifstream fe("vertex.txt");
        char cadena[128];
        // Leeremos mediante getline, si lo hiciéramos
        // mediante el operador >> sólo leeríamos
        // parte de la cadena:
        fe.getline(cadena, 128);
        cout << cadena << "LLL";
        fs << cadena << endl;
        int n_ver = atoi(cadena);
        cout << n_ver << "LLL";
        for (int aux = 0; aux < n_ver+1; aux++) {
            char aux_x[128], aux_y[128];
            fe.getline(aux_x, 128);
            v_x.push_back(atoi(aux_x));
            fe.getline(aux_y, 128);
            v_y.push_back(atoi(aux_y));
            fs << aux_x << endl;
            fs << aux_y << endl;

        }

	fe.getline(auxi, 128);
         
            fs << auxi << endl;
fe.getline(auxi, 128);

           fs << auxi << endl;
fe.getline(auxi, 128);

          fs << auxi << endl;


        fs.close();
        fe.close();


    }

    char rcomp[404] = "";
    strcat(rcomp, buf);
    strcat(rcomp, "/");
    strcat(rcomp, buf2);
    CImg<unsigned char> img(rcomp); // Define a 640x400 color image with 8 bits per color component.


    unsigned char rojo[] = {255, 0, 0}; //Define color rojo
    char text[3];

    /*
    for (int aux = 0; aux < (v_x.size()-1); aux++) {


        sprintf(text, "%d", aux + 1);

        img.draw_text(v_x[aux], v_y[aux], text, rojo, 0, 1, 500);

	}*/

    //img.display("Hola...");

    char resul[204] = "fin_";
    char resul2[404] = "";
    strcat(resul2, buf);
    strcat(resul, buf2);
    cout << resul2 << endl;
    strcat(resul2, "/");
    strcat(resul2, resul);
    cout << resul << endl;
    cout << resul2;
    img.save(resul2);

}

