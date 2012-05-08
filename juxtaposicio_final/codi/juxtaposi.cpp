#include "juxtaposi.h"

using namespace std;

string Anterior[3][3] = {
    {"{smaller,equal,bigger}", "{smaller,equal,bigger}", "{smaller,equal,bigger}"},
    {"bigger", "bigger", "bigger"},
    {"bigger", "bigger", "bigger"}
};

string Posterior[3][3] = {
    {"{smaller,equal,bigger}", "{smaller,equal,bigger}", "{smaller,equal,bigger}"},
    {"smaller", "smaller", "smaller"},
    {"smaller", "smaller", "smaller"}
};

string Angle[4][4] = {

    {"{acute-angle,right-angle,obtuse-angle}", "obtuse-angle", "obtuse-angle", "NULL"},
    {"obtuse-angle", "obtuse-angle", "obtuse-angle", "NULL"},
    {"obtuse-angle", "obtuse-angle", "obtuse-angle", "NULL"},
    {"NULL", "NULL", "NULL", "curve"}
};

string Costat[3][3] = {

    {"smaller", "smaller", "{smaller,equal,bigger}"},
    {"smaller", "equal", "bigger"},
    {"{smaller,equal,bigger}", "bigger", "bigger"}
};

string Convc[4][4] = {

    {"NULL", "concave", "concave", "concave"},
    {"concave", "convex", "convex", "{convex,NULL}"},
    {"concave", "convex", "NULL", "concave"},
    {"concave", "{convex,NULL}", "concave", "concave"}
};

int juxtaposi::IdentificaAngle(string angl) {


    int an;

    if (angl == "acute-angle" || angl == "acute") {
        an = 0;
    } else
        if (angl == "right-angle" || angl == "right") {
        an = 1;
    } else
        if (angl == "obtuse-angle" || angl == "obtuse") {
        an = 2;
    } else
        if (angl == "curve") {
        an = 3;
    }

    return an;

}

int juxtaposi::IdentificaConcv(string concv, string angl) {

    int cv = 0;
    int i_ang = IdentificaAngle(angl);
    if (concv == "concave" && i_ang != 3) {
        cv = 0;
    } else
        if (concv == "convex" && i_ang == 0) {
        cv = 1;
    } else
        if (concv == "convex" && i_ang == 1) {
        cv = 2;
    } else
        if (concv == "convex" && i_ang == 2) {
        cv = 3;
    }

    return cv;

}

int juxtaposi::IdentificaCostat(string cost) {

    int cs;

    if (cost == "smaller") {
        cs = 0;
    } else
        if (cost == "equal") {
        cs = 1;
    } else
        if (cost == "bigger") {
        cs = 2;
    }

    return cs;

}

juxtaposi::juxtaposi() {

}

juxtaposi::~juxtaposi() {

}

juxtaposi::juxtaposi(string fig1_, string fig2_) {
    fig1 = fig1_;
    fig2 = fig2_;

}

vector <string> direccio_desplasament(int un1, int un2, vector<string> pos_forat, int num_fig) {


    int matdespx[4][5] = {
        {2, 6, 0, 4},
        {0, 6, 0, 6},
        {3, 5, 2, 3},
        {4, 4, 2, 2}
    };
    int matdespy[4][5] = {
        {2, 6, 0, 4},
        {0, 6, 0, 6},
        {3, 5, 1, 3},
        {4, 4, 2, 2}
    };
    int matforatsx[3][7][3] = {
        {
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 1, 0},
            {1, 0, 0},
            {0, 1, 1}
        },
        {
            {1, 0, 0},
            {1, 0, 0},
            {1, 1, 0},
            {0, 1, 0},
            {0, 1, 1},
            {0, 0, 1},
            {0, 0, 1}
        },
        {
            {1, 1, 0},
            {0, 1, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1}
        }
    };
    int matforatsy[3][7][3] = {
        {
            {0, 1, 1},
            {1, 1, 0},
            {1, 1, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0}
        },
        {
            {0, 0, 1},
            {0, 0, 1},
            {0, 1, 1},
            {0, 1, 0},
            {1, 1, 0},
            {1, 0, 0},
            {1, 0, 0}
        },
        {
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 1, 1},
            {0, 1, 1},
            {1, 1, 0}
        }
    };
    string matorientacions[3][3] = {
        {"NW", "N", "NE"},
        {"W", "C", "E"},
        {"SW", "S", "SE"}
    };
    vector<float> v1_x;
    vector<float> v1_y;
    vector<float> v2_x;
    vector<float> v2_y;
    int resultat[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int despx, despy;

    int absXa, absXb, absYa, absYb, posx, posy;

    int Xa;
    int Ya;

    int Xb;
    int Yb;
    int m;
    char cadena[128];


    ifstream fe("../vertex1.txt");

    // Leeremos mediante getline, si lo hiciÃ©ramos
    // mediante el operador >> sÃ³lo leerÃ­amos
    // parte de la cadena:
    fe.getline(cadena, 128);


    int n_ver = atoi(cadena);

    for (int aux = 0; aux < n_ver + 1; aux++) {
        char aux_x[128], aux_y[128];
        fe.getline(aux_x, 128);
        v1_x.push_back(atoi(aux_x));
        fe.getline(aux_y, 128);
        v1_y.push_back(atoi(aux_y));


    }

    fe.close();
    ifstream fe2("../vertex2.txt");

    // Leeremos mediante getline, si lo hiciÃ©ramos
    // mediante el operador >> sÃ³lo leerÃ­amos
    // parte de la cadena:
    fe2.getline(cadena, 128);

    n_ver = atoi(cadena);

    for (int aux = 0; aux < n_ver + 1; aux++) {
        char aux_x[128], aux_y[128];
        fe2.getline(aux_x, 128);
        v2_x.push_back(atoi(aux_x));
        fe2.getline(aux_y, 128);
        v2_y.push_back(atoi(aux_y));


    }

    fe2.close();

    int cx1 = 0;
    int cx2 = 0;
    int cy1 = 0;
    int cy2 = 0;

    if (num_fig == 1) {

        cx1 = v1_x.back();
        cx2 = v2_x.back();
        cy1 = v1_y.back();
        cy2 = v2_y.back();
    } else if (num_fig == 2) {
        cx2 = v1_x.back();
        cx1 = v2_x.back();
        cy2 = v1_y.back();
        cy1 = v2_y.back();



    }

    Xa = cx1 - v1_x[un1 - 1];
    Ya = cy1 - v1_y[un1 - 1];

    Xb = cx2 - v2_x[un2 - 1];
    Yb = cy2 - v2_y[un2 - 1];

    //  m = min(abs(v1_x[un1 - 1] - v1_x[un1]), abs(v1_y[un1 - 1] - v1_y[un1])) / 6;
    m = 20;

    absXa = abs(Xa);
    absXb = abs(Xb);
    absYa = abs(Ya);
    absYb = abs(Yb);

    posx = 0;
    posy = 0;


    if (absXa < absXb) {
        if (2 * absXa < absXb)
            posx = 1;
        else if (absXa + m < absXb)
            posx = 0;
        else
            posx = 2;
    } else {
        if (absXa < absXb + m)
            posx = 2;
        else
            posx = 3;

    }
    if (Xa > 0) {
        if (Xb > 0)
            posy = 0;
        else
            posy = 1;
    } else {
        if (Xb > 0)
            posy = 2;
        else
            posy = 3;
    }
    despx = matdespx[posx][posy];


    if (absYa < absYb) {
        if (2 * absYa < Yb)
            posx = 1;
        else if (absYa < absYb - m)
            posx = 2;
        else
            posx = 0;
    } else {
        if (absYa + m < absYb)
            posx = 3;
        else
            posx = 2;
    }
    if (Ya > 0) {
        if (Yb > 0)
            posy = 3;
        else
            posy = 2;
    } else {
        if (Yb > 0)
            posy = 1;
        else
            posy = 0;
    }

    despy = matdespy[posx][posy];



    for (int i = 0; i < pos_forat.size(); i++) {
        if ((pos_forat[i] == "NW") | (pos_forat[i] == "W") | (pos_forat[i] == "SW")) {
            posx = 0;
        } else {
            if (("N" == pos_forat[i]) | ("C" == pos_forat[i]) | ("S" == pos_forat[i])) {

                posx = 1;
            } else
                posx = 2;
        }

        if (("NW" == pos_forat[i]) | ("N" == pos_forat[i]) | ("NE" == pos_forat[i])) {
            posy = 0;
        } else {
            if (("W" == pos_forat[i]) | ("C" == pos_forat[i]) | ("E" == pos_forat[i])) {
                posy = 1;

            } else
                posy = 2;
        }
    }



    for (int j = 0; j < 3; j++)
        if (matforatsx[posx][despx][j] == 1)
            for (int k = 0; k < 3; k++)
                if (matforatsy[posy][despy][k] == 1) {

                    resultat[k][j] = 1;
                }
    vector <string> resul;
    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++) {

            if (resultat[j][k] == 1) {
                resul.push_back(matorientacions[j][k]);

            }

        }




    return resul;
}

void juxtaposi::operacio(int r1v1, int r1v2, int r2v1, int r2v2) {
	
    //primera figura

    int encontrado = 0;
    int i;
    encontrado = 0;
    for (i = 0; i < fig1.length(); i++) {
        if (fig1[i] == '[') {
            encontrado = 1;
        }
        if (encontrado == 1) {
            fig1.erase(i, 1);
            i--;
            encontrado = 0;
        }
    }


    const string deli = "CIi";
    vector<string> tokens;
    int ult_pos = 0;

    for (int i = 0; i < fig1.size(); i++) {
        //cout <<deli[0]<<" "<<fig1[i]<<" "<<deli[1]<<" "<<fig1[i+1]<<" "<<deli[2]<<" "<<fig1[i+2]<<endl;
        if (deli[0] == fig1[i] && deli[1] == fig1[i + 1] && deli[2] == fig1[i + 2]) {

            tokens.push_back(fig1.substr(ult_pos, i));
            i += 4;
            ult_pos = i;
        }
    }
    tokens.push_back(fig1.substr(ult_pos, -1));


    const string delimiters2 = "]";
    vector<vector<string> > tokens2;

    for (int i = 0; i < tokens.size(); i++) {

        string::size_type lastPos = tokens[i].find_first_not_of(delimiters2, 0);
        // Find first "non-delimiter".
        string::size_type pos = tokens[i].find_first_of(delimiters2, lastPos);
        vector<string> aux;
        while (string::npos != pos || string::npos != lastPos) {
            // Found a token, add it to the vector.
            if (i == 0) {
                if (lastPos != tokens[i].find_first_not_of(delimiters2, 0))
                    aux.push_back(tokens[i].substr(lastPos, pos - lastPos));
            } else {

                aux.push_back(tokens[i].substr(lastPos, pos - lastPos));
            }

            // Skip delimiters.  Note the "not_of"
            lastPos = tokens[i].find_first_not_of(delimiters2, pos);
            // Find next "non-delimiter"
            pos = tokens[i].find_first_of(delimiters2, lastPos);
        }
        tokens2.push_back(aux);
        //tokens.erase(tokens.begin());

    }


    vector<vector<string> > trosos;
    for (int i = 0; i < tokens2.size(); i++) {
        trosos.resize(2);
        for (int j = 0; j < tokens2[i].size(); j++) {

            const string delimiters = ",";

            string::size_type lastPos = tokens2[i][j].find_first_not_of(delimiters, 0);
            // Find first "non-delimiter".
            string::size_type pos = tokens2[i][j].find_first_of(delimiters, lastPos);

            while (string::npos != pos || string::npos != lastPos) {

                // Found a token, add it to the vector.
                trosos[i].push_back(tokens2[i][j].substr(lastPos, pos - lastPos));


                // Skip delimiters.  Note the "not_of"
                lastPos = tokens2[i][j].find_first_not_of(delimiters, pos);
                //cout<<tokens.back()<<endl;
                // Find next "non-delimiter"
                pos = tokens2[i][j].find_first_of(delimiters, lastPos);
            }
        }
    }


    //segona  figura
    encontrado = 0;
    encontrado = 0;
    for (i = 0; i < fig2.length(); i++) {
        if (fig2[i] == '[') {
            encontrado = 1;
        }
        if (encontrado == 1) {
            fig2.erase(i, 1);
            i--;
            encontrado = 0;
        }
    }


    tokens.clear();
    ult_pos = 0;

    for (int i = 0; i < fig2.size(); i++) {
        //cout <<deli[0]<<" "<<fig1[i]<<" "<<deli[1]<<" "<<fig1[i+1]<<" "<<deli[2]<<" "<<fig1[i+2]<<endl;

        if (deli[0] == fig2[i] && deli[1] == fig2[i + 1] && deli[2] == fig2[i + 2]) {
            // cout<<"HOL"<<endl;
            tokens.push_back(fig2.substr(ult_pos, i));
            i += 4;
            ult_pos = i;
        }

    }


    tokens.push_back(fig2.substr(ult_pos, -1));

    for (int i = 0; i < tokens2.size(); i++) {

        tokens2[i].clear();


    }

    vector<vector<string> > tokens3;
    // cout<<"LLLLLLL"<<tokens.size()<<endl;
    for (int i = 0; i < tokens.size(); i++) {

        string::size_type lastPos = tokens[i].find_first_not_of(delimiters2, 0);
        // Find first "non-delimiter".
        string::size_type pos = tokens[i].find_first_of(delimiters2, lastPos);
        vector<string> aux;
        while (string::npos != pos || string::npos != lastPos) {
            // Found a token, add it to the vector.
            if (i == 0) {
                if (lastPos != tokens[i].find_first_not_of(delimiters2, 0))
                    aux.push_back(tokens[i].substr(lastPos, pos - lastPos));
            } else {

                aux.push_back(tokens[i].substr(lastPos, pos - lastPos));
            }

            // Skip delimiters.  Note the "not_of"
            lastPos = tokens[i].find_first_not_of(delimiters2, pos);
            // Find next "non-delimiter"
            pos = tokens[i].find_first_of(delimiters2, lastPos);
        }
        tokens3.push_back(aux);

        //tokens.erase(tokens.begin());

    }

    /*  for (int i=0; i< 1;i++)
          for(int j=0; j<trosos[i].size();j++){

              cout<<trosos[i][j]<<endl;




              }
      cout <<endl;


     */ string::size_type lastPos2;
    string::size_type pos2;
    vector<vector<string> > trosos2;


    for (int i = 0; i < tokens3.size(); i++) {
        trosos2.resize(2);
        for (int j = 0; j < tokens3[i].size(); j++) {

            const string delimiters = ",";


            lastPos2 = tokens3[i][j].find_first_not_of(delimiters, 0);

            // Find first "non-delimiter".
            pos2 = tokens3[i][j].find_first_of(delimiters, lastPos2);


            while (string::npos != pos2 || string::npos != lastPos2) {



                // Found a token, add it to the vector.
                trosos2[i].push_back(tokens3[i][j].substr(lastPos2, pos2 - lastPos2));


                // Skip delimiters.  Note the "not_of"
                lastPos2 = tokens3[i][j].find_first_not_of(delimiters, pos2);

                //cout<<tokens.back()<<endl;
                // Find next "non-delimiter"
                pos2 = tokens3[i][j].find_first_of(delimiters, lastPos2);
            }

        }

    }


    //    cout<<"Trozos"<<endl;
    //     for (int i = 0; i < trosos2[0].size(); i++) {
    //         cout<< trosos2[0][i]<<endl;
    //
    //         }

    int t1 = trosos[0].size() - 1;
    int t2 = trosos2[0].size() - 1;

    int tam1 = trosos[0].size() / 3;
    int tam2 = trosos2[0].size() / 3;
    int tame = trosos[0].size() / 3 + trosos2[0].size() / 3 - 2;


    vector <vector<string> > matriu1(tam1, vector<string > (3));
    vector <vector<string> > matriu2(tam2, vector<string > (3));

    int auxii = 0, auxij = 0;
    for (int i = 0; i < trosos[0].size(); i++) {
        matriu1[auxii][auxij] = trosos[0][i];
        if ((auxij + 1) % 3 == 0 and auxij != 0) {

            auxij = 0;
            auxii++;

        } else {
            auxij++;
        }




    }

    auxii = 0, auxij = 0;
    for (int i = 0; i < trosos2[0].size(); i++) {
        matriu2[auxii][auxij] = trosos2[0][i];
        if ((auxij + 1) % 3 == 0 and auxij != 0) {
            auxij = 0;
            auxii++;

        } else {
            auxij++;

        }


    }


	
    vector<vector<string> > resultatf(tame, vector<string > (3));
	
    int cont = 0;
    int cont2 = 0;
    int ant_nul = 0;
    int cont_nul = 0;
    string nulo;
    i = 0;
    int j = 0;
    cont2 = (r2v2 - 1)*3;
    vector <string> costat_ant;
    vector <string> costat_sig;
    vector <int> comp_i;
    // cont2 = cont2 % t2;

    int c_ver1 = 0;
    int c_ver2 = r2v2 - 1;


    //nulo = Convc[IdentificaConcv(matriu1[r1v1-1][2], matriu1[r1v1-1][0])][IdentificaConcv(matriu2[r2v2-1][2], matriu2[r2v2-1][0])];


    // nulo = Convc[IdentificaConcv(matriu1[r1v2-1][2], matriu1[r1v2-1][0])][IdentificaConcv(matriu2[r2v1-1][2], matriu2[r2v1-1][0])];



    //nulo = Convc[Iden/tificaConcv(matriu1[c_ver][2], matriu1[c_ver][0])][IdentificaConcv(matriu2[r2v2-1][2], matriu2[r2v2-1][0])];
    //nulo = Convc[IdentificaConcv(trosos[0][cont + 2], trosos[0][cont])][IdentificaConcv(trosos2[0][cont2 + 2], trosos2[0][cont2])];

    while (c_ver1 < (r1v1 - 1)) {

        resultatf[i][0] = matriu1[c_ver1][0];
        j++;
        resultatf[i][1] = matriu1[c_ver1][1];
        j++;
        resultatf[i][2] = matriu1[c_ver1][2];
        c_ver1++;
        i++;
        j = 0;

    }



    nulo = Convc[IdentificaConcv(matriu1[c_ver1][2], matriu1[c_ver1][0])][IdentificaConcv(matriu2[c_ver2][2], matriu2[c_ver2][0])];
    if (nulo == "NULL") {



        comp_i.push_back(i);
        costat_ant.push_back(matriu1[c_ver1][1]);
        costat_sig.push_back(matriu2[c_ver2][1]);

        c_ver2++;





    } else {
        //res += "[";


        resultatf[i][0] = Angle[IdentificaAngle(matriu1[0][cont])][IdentificaAngle(matriu2[c_ver2][0])];
        j++;
        resultatf[i][1] = Costat[IdentificaCostat(matriu1[0][cont])][IdentificaCostat(matriu2[c_ver2][1])];
        j++;
        resultatf[i][2] = Convc[IdentificaConcv(matriu1[r1v1 - 1][2], matriu1[r1v1 - 1][0])][IdentificaConcv(matriu2[r2v2 - 1][2], matriu2[r2v2 - 1][0])];
        c_ver2++;
        i++;
        j = 0;
        c_ver1 = r1v2 - 1;

    }


    while (c_ver2 > ((r2v1 - 1))) {

        if (c_ver2 >= tam2) {
            c_ver2 = 0;


        }


        resultatf[i][0] = matriu2[c_ver2][0];
      
        j++;
        resultatf[i][1] = matriu2[c_ver2][1];
        j++;
        resultatf[i][2] = matriu2[c_ver2][2];

        c_ver2++;
        if (c_ver2 >= tam2) {
            c_ver2 = 0;

        }
        i++;
        j = 0;


    }



    // nulo = Convc[IdentificaConcv(trosos[0][cont + 2], trosos[0][cont])][IdentificaConcv(trosos2[0][cont2 + 2], trosos2[0][cont2])];
    nulo = Convc[IdentificaConcv(matriu1[r1v2 - 1][2], matriu1[r1v1 - 1][0])][IdentificaConcv(matriu2[r2v1 - 1][2], matriu2[r2v2 - 1][0])];

    if (nulo == "NULL") {




        comp_i.push_back(i);
        costat_ant.push_back(matriu1[c_ver1][1]);

        costat_sig.push_back(matriu2[c_ver2][1]);



        c_ver1++;




    } else {
        //res += "[";

        resultatf[i][0] = Angle[IdentificaAngle(matriu1[c_ver1][0])][IdentificaAngle(matriu2[c_ver2][0])];
        j++;
        resultatf[i][1] = Costat[IdentificaCostat(matriu1[c_ver1][1])][IdentificaCostat(matriu2[c_ver2][1])];
        j++;
        resultatf[i][2] = Convc[IdentificaConcv(matriu1[c_ver1][2], matriu1[c_ver1][0])][IdentificaConcv(matriu2[c_ver2][2], matriu2[c_ver2][0])];
        c_ver2++;
        i++;
        j = 0;
        c_ver1++;



    }



    while (c_ver1 < tam1 - 1) {


        resultatf[i][0] = matriu1[c_ver1][0];
        j++;
        resultatf[i][1] = matriu1[c_ver1][1];
        j++;
        resultatf[i][2] = matriu1[c_ver1][2];
        c_ver1++;
        i++;
        j = 0;


    }

    for (int auxil = 0; auxil < comp_i.size(); auxil++) {
        int nou = comp_i[auxil];

        if (nou > (tame - comp_i.size() - 1))
            resultatf[0][1] = Anterior[IdentificaCostat(costat_ant[auxil])][IdentificaCostat(costat_sig[auxil])];
        else
            resultatf[nou][1] = Anterior[IdentificaCostat(costat_ant[auxil])][IdentificaCostat(costat_sig[auxil])];
        if (nou != 0)
            resultatf[nou - 1][1] = Posterior[IdentificaCostat(costat_ant[auxil])][IdentificaCostat(costat_sig[auxil])];
        else
            resultatf[tame - comp_i.size() - 1][1] = Posterior[IdentificaCostat(costat_ant[auxil])][IdentificaCostat(costat_sig[auxil])];
    }



    string mostra = "";
    mostra += "[";

    for (int i = 0; i < (resultatf.size() - comp_i.size()); i++) {
        mostra += "[";
        for (int j = 0; j < 3; j++) {
            mostra += resultatf[i][j];
            if (j != 2)
                mostra += ",";
        }
        mostra += "]";
    }




    vector <string> coord;
    vector <string> coord2;
    vector <string> de_for1;
    vector <string> de_for2;
    vector <string> resul;
    vector <string> resul2;

    // if (trosos[1].size() > 0 or trosos2[1].size() > 0){
    //   mostra+=",CIi";mostra+=",[";

    if (trosos[1].size() > 0) {
        mostra += ",CIi";
        mostra += ",[";

        for (int i = 0; i < trosos[1].size(); i++) {
            if (trosos[1][i].size() <= 2)
                coord.push_back(trosos[1][i]);

        }
        for (int i = 0; i < trosos[1].size(); i++) {
            if (trosos[1][i].size() > 2)
                de_for1.push_back(trosos[1][i]);

        }



        resul = direccio_desplasament(r1v1, r2v2, coord, 1);

        for (int i = 0; i < resul.size(); i++) {
            for (int j = 0; j < resul[i].size(); j++) {

                mostra += resul[i][j];

                if (i != (resul.size() - 1))
                    mostra += ",";

            }
        }
        mostra += "],[";
        for (int i = 0; i < de_for1.size(); i += 3) {

            mostra += "[";
            mostra += de_for1[i];
            mostra += ",";
            mostra += de_for1[i + 1];
            mostra += ",";
            mostra += de_for1[i + 2];
            mostra += "]";

        }


    }


    if (trosos2[1].size() > 0) {


        for (int i = 0; i < trosos2[1].size(); i++) {
            if (trosos2[1][i].size() <= 2)
                coord2.push_back(trosos2[1][i]);

        }


        for (int i = 0; i < trosos2[1].size(); i++) {
            if (trosos2[1][i].size() > 2)
                de_for2.push_back(trosos2[1][i]);

        }

        resul2 = direccio_desplasament(r1v2, r2v1, coord2, 2);

        mostra += ",CIi";
        if (resul2.size() > 1)
            mostra += ",[";
        else
            mostra +=",";


        for (int i = 0; i < resul2.size(); i++) {
            //for (int j = 0; j < resul2[i].size(); j++) {
            mostra += resul2[i];

            if (i != (resul2.size() - 1))
                mostra += ",";

        }

        if (resul2.size() > 1)
            mostra += "],[";
        else
            mostra += ",[";

        for (int i = 0; i < de_for2.size(); i += 3) {
            mostra += "[";
            mostra += de_for2[i];
            mostra += ",";
            mostra += de_for2[i + 1];
            mostra += ",";
            mostra += de_for2[i + 2];
            mostra += "]";

        }
        mostra += "]";
    }



    mostra += "]";
    
    cout << mostra << endl;
    


}

