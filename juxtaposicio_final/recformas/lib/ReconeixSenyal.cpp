#include "ReconeixSenyal.h"

using namespace std;

struct sim_seny{
    string nom;
    string imatge;
    float simil;
    };


 //  |red   |reddish-orange |orange |yellow |yel..-green    |green  |vivid-green    |emerald-green  |turquoise-blue |cyan   |blue   |violet |lilac  |pink   |fuchsia|
float Colors[NSymbol1][NSymbol1] = {
//              r       ro      o       y       yg      vg      eg      tb      c       b       v       l       p       f   	b       dg      g     lg      w      NONE
/* r    */      {1.00,  0.95,   0.90,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* ro   */      {0.95,  1.00,   0.95,   0.90,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* o    */      {0.90,  0.95,   1.00,   0.95,   0.90,   0.00,   1.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* y    */      {0.00,  0.90,   0.95,   1.00,   0.95,   0.90,   1.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* yg   */      {0.00,  0.00,   0.90,   0.95,   1.00,   0.95,   0.90,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* vg   */      {0.00,  0.00,   0.00,   0.90,   0.95,   1.00,   0.95,   0.90,   0.10,   0.00,   0.00,   0.00,   0.00,   0.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* eg   */      {0.00,  0.00,   0.00,   0.00,   0.90,   0.95,   1.00,   0.95,   0.90,   0.00,   0.00,   0.00,   0.00,   0.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* tb   */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,   0.95,   0.90,   0.00,   0.00,   0.00,   0.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* c    */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,   0.95,   0.90,   0.00,   0.00,   0.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* b    */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,   0.95,   0.90,   0.00,   0.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* v    */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,   0.95,   0.90,   0.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* l    */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,   0.95,   0.90,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* p    */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,   0.95,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* f    */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,  	0.00,   0.00,   0.00,   0.00,   0.00,   0.00},
/* bl   */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,  	1.00,   0.95,   0.90,   0.00,   0.00,   0.00},
/* dg   */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,  	0.95,   1.00,   0.95,   0.90,   0.00,   0.00},
/* gre  */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,  	0.90,   0.95,   1.00,   0.95,   0.90,   0.00},
/* lg   */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,  	0.00,   0.90,   0.95,   1.00,   0.95,   0.00},
/* w    */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.90,   0.95,   1.00,  	0.00,   0.00,   0.90,   0.95,   1.00,   0.00},
/* NONE */      {0.00,  0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00,   0.00},


};

float BandW[NSymbol1][NSymbol1] = {
//              b       dg      g       lg      w
/* b    */    	{1.00,  0.95,   0.90,   0.00,   0.00},
/* dg    */     {0.95,  1.00,   0.95,   0.90,   0.00},
/* g    */      {0.90,  0.95,   1.00,   0.95,   0.90},
/* lg    */     {0.00,  0.90,   0.95,   1.00,   0.95},
/* w    */      {0.00,  0.00,   0.90,   0.95,   1.00},



    };

float Orientacio[5][5]= {
//               e       dr      da       b      i
/* e    */    	{1.00,  0.00,   0.00,   0.00,   0.95},
/* dr   */     {0.00,  1.00,   0.00,   0.00,   0.95},
/* da   */      {0.00,  0.00,   1.00,   0.00,   0.95},
/* b    */     {0.00,  0.00,   0.00,   1.00,   0.95},
/* i    */      {0.95,  0.95,   0.95,   0.95,   0.95},



    };

int ReconeixSenyal::IdentificaOrien(string ori){

			int c=0;
			if (ori=="esquerra"){
				c=0;
			}
			else
			   if (ori=="dreta"){
				c=1;
			}
			else
			   if (ori=="dalt"){
				c=2;
			}
			else
			   if (ori=="baix"){
				c=3;
			}
			else
			   if (ori=="igual"){
				c=4;
			}
return c;
}
int ReconeixSenyal::IdentificaColor(string color){

			int c=0;
			if (color=="red"){
				c=0;
			}
			else
			   if (color=="reddish-orange"){
				c=1;
			}
			else
			   if (color=="orange"){
				c=2;
			}
			else
			   if (color=="yellow"){
				c=3;
			}
			else
			   if (color=="yellow-green"){
				c=4;
			}
			else
			   if (color=="green"){
				c=5;
			}
			else
			   if (color=="vivid-green"){
				c=6;
			}
			else
			   if (color=="emerald-green"){
				c=7;
			}
			else
			   if (color=="turquoise-blue"){
				c=8;
			}
			else
			   if (color=="cyan"){
				c=9;
			}
			else
			   if (color=="blue"){
				c=10;
			}
			else
			   if (color=="violet"){
				c=11;
			}
			else
			   if (color=="pink"){
				c=12;
			}
			else
			   if (color=="fuchsia"){
				c=13;
			}
			else
			   if (color=="black"){
				c=14;
			}
			else
			   if (color=="dark-grey"){
				c=15;
			}
			else
			   if (color=="grey"){
				c=16;
			}
			else
			   if (color=="light-grey"){
				c=17;
			}
			else
			   if (color=="white"){
				c=18;
			}
			else{
				c=19;
				}



    return c;

    }



int ReconeixSenyal::IdentificaBandW(string bandw){
	int bw;

			if (bandw=="black"){
				bw=0;
			}
			else
			   if (bandw=="dark-grey"){
				bw=1;
			}
			else
			   if (bandw=="grey"){
				bw=2;
			}
			else
			   if (bandw=="light-grey"){
				bw=3;
			}
			else
			   if (bandw=="white"){
				bw=4;
			}
			else{
				bw=-1;
				}

return bw;

}





ReconeixSenyal::ReconeixSenyal(Senyal &s){

    Perill per=Perill();
    Obligacio obl=Obligacio();
    Indicacio ind=Indicacio();
    Prioritat pri=Prioritat();
    float max=0;
    vector<int> maxims;

    vector <float> similitut;

    //similitut amb senyals de perill

    float total=0;



    total+= (100*Colors[IdentificaColor(s.c_borde)][IdentificaColor(per.c_borde)])*0.3;
    cout <<total;
    total+= (100*Colors[IdentificaColor(s.c_fondo)][IdentificaColor(per.c_fondo)])*0.2;
        cout <<total;

    total+= (100-Similitut(per.n_ver,per.f_ext,s.n_ver,s.d_quali))*0.5;
    cout <<total;

    similitut.push_back(total);

    if (total > max){
	max=total;
	}

    cout << "SIMILITUT DE SENYAL DE PERILL: "<< total<<endl;

    total=0;
    float max2=0.0, aux2=0.0;
    int posi2=0;

    while(posi2<pri.c_borde.size()){
    aux2=0;
    aux2+= (100*Colors[IdentificaColor(s.c_borde)][IdentificaColor(pri.c_borde[posi2])])*0.3;
    aux2+= (100*Colors[IdentificaColor(s.c_fondo)][IdentificaColor(pri.c_fondo[posi2])])*0.2;
    aux2+= (100-Similitut(pri.n_ver[0],pri.f_ext[0],s.n_ver,s.d_quali))*0.5;

    posi2++;
    if (max2<aux2){
        max2=aux2;
        }

    if (max2 > max){
	max=max2;
	}
    }
     similitut.push_back(max2);






    cout << "SIMILITUT DE SENYAL DE PRIORITAT: "<< max2<<endl;

/*    float total=0;


    total+= (100*Colors[IdentificaColor(s.c_borde)][IdentificaColor(pri.c_borde)])*0.3;
    total+= (100*Colors[IdentificaColor(s.c_fondo)][IdentificaColor(pri.c_fondo)])*0.2;
    cout << total;
    total+= (100-Similitut(pri.n_ver,pri.f_ext,s.n_ver,s.d_quali))*0.5;

    similitut.push_back(total);

    cout << "SIMILITUT DE SENYAL DE PRIORITAT: "<< total<<endl;
*/

    total=0;

    total+= (100*Colors[IdentificaColor(s.c_borde)][IdentificaColor(obl.c_borde)])*0.3;
    total+= (100*Colors[IdentificaColor(s.c_fondo)][IdentificaColor(obl.c_fondo)])*0.2;
    total+= (100-Similitut(obl.n_ver,obl.f_ext,s.n_ver,s.d_quali))*0.5;

     similitut.push_back(total);

    if (total > max){
	max=total;
	}
    cout << "SIMILITUT DE SENYAL DE OBLIGACIO: "<< total<<endl;

    total=0;

    total+= (100*Colors[IdentificaColor(s.c_borde)][IdentificaColor(ind.c_borde)])*0.3;

    total+= (100*Colors[IdentificaColor(s.c_fondo)][IdentificaColor(ind.c_fondo)])*0.2;

    total+= (100-Similitut(ind.n_ver,ind.f_ext,s.n_ver,s.d_quali))*0.5;

     similitut.push_back(total);

    if (total > max){
	max=total;

	}

	cout << "SIMILITUT DE SENYAL DE INDICACIO: "<< total<<endl;


    int i=0;
	while (similitut.size()!=0){
	    float aux3=similitut.back();

	    if (aux3==max){
            maxims.push_back(i);
           }

	    similitut.pop_back();
	    i++;

	    }

   int tipus=0;
   float major;
    int tvec=maxims.size()-1;
    int cont=0;
    vector<sim_seny> sim_max;
    while ( cont<=tvec){

        tipus=maxims[cont];

    if (tipus==3){

	cout << "LA SENYAL ES DE TIPUS PERILL"<< endl;
    major=-1.0;
    sim_seny aux;


    Perill1 peri1;
    float kk=ElegeixSenyalPerill(s,peri1);
    if (kk > major){ major=kk;aux.nom=peri1.nom; aux.imatge=peri1.imatge; aux.simil=kk;}
    Perill2 peri2;
    kk=ElegeixSenyalPerill(s,peri2);
    if (kk > major){ major=kk;aux.nom=peri2.nom; aux.imatge=peri2.imatge; aux.simil=kk;}
    Perill3 peri3;
     kk=ElegeixSenyalPerill(s,peri3);
    if (kk > major){ major=kk;aux.nom=peri3.nom; aux.imatge=peri3.imatge; aux.simil=kk;}
    Perill4 peri4;
     kk=ElegeixSenyalPerill(s,peri4);
    if (kk > major){ major=kk;aux.nom=peri4.nom; aux.imatge=peri4.imatge; aux.simil=kk;}
    Perill5 peri5;
     kk=ElegeixSenyalPerill(s,peri5);
    if (kk > major){ major=kk;aux.nom=peri5.nom; aux.imatge=peri5.imatge; aux.simil=kk;}
    Perill6 peri6;
     kk=ElegeixSenyalPerill(s,peri6);
    if (kk > major){ major=kk;aux.nom=peri6.nom; aux.imatge=peri6.imatge; aux.simil=kk;}
    Perill7 peri7;
     kk=ElegeixSenyalPerill(s,peri7);
    if (kk > major){ major=kk;aux.nom=peri7.nom; aux.imatge=peri7.imatge; aux.simil=kk;}
    Perill8 peri8;
     kk=ElegeixSenyalPerill(s,peri8);
    if (kk > major){ major=kk;aux.nom=peri8.nom; aux.imatge=peri8.imatge; aux.simil=kk;}

    sim_max.push_back(aux);


	}


	if (tipus == 2){
    Prioritat maxpri;
	cout << "LA SENYAL ES DE TIPUS PRIORITAT"<< endl;
    major=-1.0;
    sim_seny aux;
	Prioritat1 pri1;
    float kk=ElegeixSenyalPrioritat(s,pri1);
    if (kk > major){ major=kk;aux.nom=pri1.nom; aux.imatge=pri1.imatge; aux.simil=kk;}
    Prioritat2 pri2;
    kk=ElegeixSenyalPrioritat(s,pri2);
    if (kk > major){ major=kk;aux.nom=pri2.nom; aux.imatge=pri2.imatge; aux.simil=kk;}
    Prioritat3 pri3;
     kk=ElegeixSenyalPrioritat(s,pri3);
    if (kk > major){ major=kk;aux.nom=pri3.nom; aux.imatge=pri3.imatge; aux.simil=kk;}
    Prioritat4 pri4;
     kk=ElegeixSenyalPrioritat(s,pri4);
    if (kk > major){ major=kk;aux.nom=pri4.nom; aux.imatge=pri4.imatge; aux.simil=kk;}
    Prioritat5 pri5;
     kk=ElegeixSenyalPrioritat(s,pri5);
    if (kk > major){ major=kk;aux.nom=pri5.nom; aux.imatge=pri5.imatge; aux.simil=kk;}
    sim_max.push_back(aux);

	}

	if (tipus == 1){

	cout << "LA SENYAL ES DE TIPUS OBLIGACIO"<< endl;
    major=-1.0;
    sim_seny aux;
    Obligacio1 obl1;
    float kk=ElegeixSenyalObligacio(s,obl1);
    if (kk > major){ major=kk;aux.nom=obl1.nom; aux.imatge=obl1.imatge; aux.simil=kk;}
    Obligacio2 obl2;
    kk=ElegeixSenyalObligacio(s,obl2);
    if (kk > major){ major=kk;aux.nom=obl2.nom; aux.imatge=obl2.imatge; aux.simil=kk;}
    Obligacio3 obl3;
     kk=ElegeixSenyalObligacio(s,obl3);
    if (kk > major){ major=kk;aux.nom=obl3.nom; aux.imatge=obl3.imatge; aux.simil=kk;}
    sim_max.push_back(aux);



	}

	if (tipus == 0){

	cout << "LA SENYAL ES DE TIPUS INDICACIO"<< endl;
	major=0.0;
	sim_seny aux;
    Indicacio1 ind1;
    float kk=ElegeixSenyalIndicacio(s,ind1);
    if (kk > major){ major=kk;aux.nom=ind1.nom; aux.imatge=ind1.imatge; aux.simil=kk;}
    Indicacio2 ind2;
    kk=ElegeixSenyalIndicacio(s,ind2);
    if (kk > major){ major=kk;aux.nom=ind2.nom; aux.imatge=ind2.imatge; aux.simil=kk;}
    Indicacio3 ind3;
     kk=ElegeixSenyalIndicacio(s,ind3);
    if (kk > major){ major=kk;aux.nom=ind3.nom; aux.imatge=ind3.imatge; aux.simil=kk;}
    Indicacio4 ind4;
     kk=ElegeixSenyalIndicacio(s,ind4);
    if (kk > major){ major=kk;aux.nom=ind4.nom; aux.imatge=ind4.imatge; aux.simil=kk;}
    Indicacio5 ind5;
     kk=ElegeixSenyalIndicacio(s,ind5);
    if (kk > major){ major=kk;aux.nom=ind5.nom; aux.imatge=ind5.imatge; aux.simil=kk;}
    Indicacio6 ind6;
     kk=ElegeixSenyalIndicacio(s,ind6);
    if (kk > major){ major=kk;aux.nom=ind6.nom; aux.imatge=ind6.imatge; aux.simil=kk;}
    Indicacio7 ind7;
     kk=ElegeixSenyalIndicacio(s,ind7);
    if (kk > major){ major=kk;aux.nom=ind7.nom; aux.imatge=ind7.imatge; aux.simil=kk;}


    sim_max.push_back(aux);


	}

cont++;
}
int cont2=0;
major=0.0;
sim_seny maxi;
while(cont2<sim_max.size()){
    sim_seny aux=sim_max[cont2];
    if (major<aux.simil){
        major=aux.simil;
        maxi=aux;}
    cont2++;}

cout<<maxi.nom<<endl;
cout<<maxi.simil<<endl;
cout<<maxi.imatge;


}

float ReconeixSenyal::ElegeixSenyalPerill(Senyal &s,   Perill &per){


    //Perill* per = pe.clonar( );
    float total =0.0;

	if (per.num_figures == s.figures.size()){
	bool orien=false;
	Forma fig1, fig2;
    int posi=0;
    if (per.num_figures==0){
        if (s.figures.size()==0){
            total=100;}
        else{
            total=0;
            cout << "Total 0"<<endl;
            }
    }
    else{
	while ((posi) < (s.figures.size())){
		fig1=per.figures[posi];
		fig2=s.figures[posi];
		if(!orien){

			total+= (100*Colors[IdentificaColor(fig1.color)][IdentificaColor(fig2.color)])*0.5;
            total+= (100-SimilitutNoCiclica(fig1.n_ver,fig1.d_quali,fig2.n_ver,fig2.d_quali))*0.5;
			orien=true;


			}
		else{


                const string delimiters = ",";
        		vector<string> tokens;

	    		string o1;
                o1= per.orientacio[posi-1];


			    string::size_type lastPos = o1.find_first_not_of(delimiters, 0);
			    // Find first "non-delimiter".
			    string::size_type pos     = o1.find_first_of(delimiters, lastPos);

			    while (string::npos != pos || string::npos != lastPos)
			    {
				// Found a token, add it to the vector.
				tokens.push_back(o1.substr(lastPos, pos - lastPos));
				// Skip delimiters.  Note the "not_of"
				lastPos = o1.find_first_not_of(delimiters, pos);
                //cout<<tokens.back()<<endl;
				// Find next "non-delimiter"
				pos = o1.find_first_of(delimiters, lastPos);
			    }


        		vector<string> tokens2;

	    		string o2;
                o2= s.orientacio[posi-1];


			    lastPos = o2.find_first_not_of(delimiters, 0);
			    // Find first "non-delimiter".
                pos     = o2.find_first_of(delimiters, lastPos);

			    while (string::npos != pos || string::npos != lastPos)
			    {
				// Found a token, add it to the vector.
				tokens2.push_back(o2.substr(lastPos, pos - lastPos));

				// Skip delimiters.  Note the "not_of"
				lastPos = o2.find_first_not_of(delimiters, pos);
				// Find next "non-delimiter"
				pos = o2.find_first_of(delimiters, lastPos);
			    }



			total+= (100*Orientacio[IdentificaOrien(tokens[0])][IdentificaOrien(tokens2[0])])*0.15;
			total+= (100*Orientacio[IdentificaOrien(tokens[1])][IdentificaOrien(tokens2[1])])*0.15;
			total+= (100*Colors[IdentificaColor(fig1.color)][IdentificaColor(fig2.color)])*0.4;
            total+= (100-SimilitutNoCiclica(fig1.n_ver,fig1.d_quali,fig2.n_ver,fig2.d_quali))*0.3;

		}

    posi++;

	}
    }
	}

    if (per.num_figures!=0){

  total=total/per.num_figures;
  }
	cout <<" Similitut en "<< per.nom <<" "<<total <<endl;




return total;




    }


float ReconeixSenyal::ElegeixSenyalObligacio(Senyal &s,   Obligacio &obl){

 float total =0.0;


	if (obl.num_figures == s.figures.size()){

	bool orien=false;
	Forma fig1, fig2;
    int posi=0;
    if (obl.num_figures==0){
        if (s.figures.size()==0)
            total=100;
        else
            total=0;


    }
    else{
	while ((posi) < (s.figures.size())){
		fig1=obl.figures[posi];
		fig2=s.figures[posi];
		if(!orien){

			total+= (100*Colors[IdentificaColor(fig1.color)][IdentificaColor(fig2.color)])*0.5;
            total+= (100-SimilitutNoCiclica(fig1.n_ver,fig1.d_quali,fig2.n_ver,fig2.d_quali))*0.5;
			orien=true;


			}
		else{

                const string delimiters = ",";
        		vector<string> tokens;

	    		string o1;
                o1= obl.orientacio[posi-1];


			    string::size_type lastPos = o1.find_first_not_of(delimiters, 0);
			    // Find first "non-delimiter".
			    string::size_type pos     = o1.find_first_of(delimiters, lastPos);

			    while (string::npos != pos || string::npos != lastPos)
			    {
				// Found a token, add it to the vector.
				tokens.push_back(o1.substr(lastPos, pos - lastPos));
				// Skip delimiters.  Note the "not_of"
				lastPos = o1.find_first_not_of(delimiters, pos);
                //cout<<tokens.back()<<endl;
				// Find next "non-delimiter"
				pos = o1.find_first_of(delimiters, lastPos);
			    }


        		vector<string> tokens2;

	    		string o2;
                o2= s.orientacio[posi-1];


			    lastPos = o2.find_first_not_of(delimiters, 0);
			    // Find first "non-delimiter".
                pos     = o2.find_first_of(delimiters, lastPos);

			    while (string::npos != pos || string::npos != lastPos)
			    {
				// Found a token, add it to the vector.
				tokens2.push_back(o2.substr(lastPos, pos - lastPos));

				// Skip delimiters.  Note the "not_of"
				lastPos = o2.find_first_not_of(delimiters, pos);
				// Find next "non-delimiter"
				pos = o2.find_first_of(delimiters, lastPos);
			    }



			total+= (100*Orientacio[IdentificaOrien(tokens[0])][IdentificaOrien(tokens2[0])])*0.15;
			total+= (100*Orientacio[IdentificaOrien(tokens[1])][IdentificaOrien(tokens2[1])])*0.15;
			total+= (100*Colors[IdentificaColor(fig1.color)][IdentificaColor(fig2.color)])*0.4;
            total+= (100-SimilitutNoCiclica(fig1.n_ver,fig1.d_quali,fig2.n_ver,fig2.d_quali))*0.3;

		}

    posi++;

	}
    }
	}

    if (obl.num_figures!=0){

   total=total/obl.num_figures;}
	cout <<" Similitut en "<< obl.nom <<" "<<total <<endl;


return total;


    }



float ReconeixSenyal::ElegeixSenyalIndicacio(Senyal &s,   Indicacio &ind){

 float total =0.0;


	if (ind.num_figures == s.figures.size()){

	bool orien=false;
	Forma fig1, fig2;
    int posi=0;
    if (ind.num_figures==0){
        if (s.figures.size()==0)
            total=100;
        else
            total=0;


    }
    else{
	while ((posi) < (s.figures.size())){
		fig1=ind.figures[posi];
		fig2=s.figures[posi];
		if(!orien){

			total+= (100*Colors[IdentificaColor(fig1.color)][IdentificaColor(fig2.color)])*0.5;
            total+= (100-SimilitutNoCiclica(fig1.n_ver,fig1.d_quali,fig2.n_ver,fig2.d_quali))*0.5;
			orien=true;


			}
		else{

                const string delimiters = ",";
        		vector<string> tokens;

	    		string o1;
                o1= ind.orientacio[posi-1];


			    string::size_type lastPos = o1.find_first_not_of(delimiters, 0);
			    // Find first "non-delimiter".
			    string::size_type pos     = o1.find_first_of(delimiters, lastPos);

			    while (string::npos != pos || string::npos != lastPos)
			    {
				// Found a token, add it to the vector.
				tokens.push_back(o1.substr(lastPos, pos - lastPos));
				// Skip delimiters.  Note the "not_of"
				lastPos = o1.find_first_not_of(delimiters, pos);
                //cout<<tokens.back()<<endl;
				// Find next "non-delimiter"
				pos = o1.find_first_of(delimiters, lastPos);
			    }


        		vector<string> tokens2;

	    		string o2;
                o2= s.orientacio[posi-1];


			    lastPos = o2.find_first_not_of(delimiters, 0);
			    // Find first "non-delimiter".
                pos     = o2.find_first_of(delimiters, lastPos);

			    while (string::npos != pos || string::npos != lastPos)
			    {
				// Found a token, add it to the vector.
				tokens2.push_back(o2.substr(lastPos, pos - lastPos));

				// Skip delimiters.  Note the "not_of"
				lastPos = o2.find_first_not_of(delimiters, pos);
				// Find next "non-delimiter"
				pos = o2.find_first_of(delimiters, lastPos);
			    }



			total+= (100*Orientacio[IdentificaOrien(tokens[0])][IdentificaOrien(tokens2[0])])*0.15;
			total+= (100*Orientacio[IdentificaOrien(tokens[1])][IdentificaOrien(tokens2[1])])*0.15;
			total+= (100*Colors[IdentificaColor(fig1.color)][IdentificaColor(fig2.color)])*0.4;
            total+= (100-SimilitutNoCiclica(fig1.n_ver,fig1.d_quali,fig2.n_ver,fig2.d_quali))*0.3;

		}

    posi++;

	}
    }
	}

    if (ind.num_figures!=0){

   total=total/ind.num_figures;}
	cout <<" Similitut en "<< ind.nom <<" "<<total <<endl;


return total;


    }



float ReconeixSenyal::ElegeixSenyalPrioritat(Senyal &s,   Prioritat &pri){

    //Perill* per = pe.clonar( );
    float total =0.0;


	if (pri.num_figures == s.figures.size()){

	bool orien=false;
	Forma fig1, fig2;
    int posi=0;
    if (pri.num_figures==0){
        if (s.figures.size()==0)
            total=100;
        else
            total=0;


    }
    else{
	while ((posi) < (s.figures.size())){
		fig1=pri.figures[posi];
		fig2=s.figures[posi];
		if(!orien){

			total+= (100*Colors[IdentificaColor(fig1.color)][IdentificaColor(fig2.color)])*0.5;
            total+= (100-SimilitutNoCiclica(fig1.n_ver,fig1.d_quali,fig2.n_ver,fig2.d_quali))*0.5;
			orien=true;


			}
		else{

                const string delimiters = ",";
        		vector<string> tokens;

	    		string o1;
                o1= pri.orientacio[posi-1];


			    string::size_type lastPos = o1.find_first_not_of(delimiters, 0);
			    // Find first "non-delimiter".
			    string::size_type pos     = o1.find_first_of(delimiters, lastPos);

			    while (string::npos != pos || string::npos != lastPos)
			    {
				// Found a token, add it to the vector.
				tokens.push_back(o1.substr(lastPos, pos - lastPos));
				// Skip delimiters.  Note the "not_of"
				lastPos = o1.find_first_not_of(delimiters, pos);
                //cout<<tokens.back()<<endl;
				// Find next "non-delimiter"
				pos = o1.find_first_of(delimiters, lastPos);
			    }


        		vector<string> tokens2;

	    		string o2;
                o2= s.orientacio[posi-1];


			    lastPos = o2.find_first_not_of(delimiters, 0);
			    // Find first "non-delimiter".
                pos     = o2.find_first_of(delimiters, lastPos);

			    while (string::npos != pos || string::npos != lastPos)
			    {
				// Found a token, add it to the vector.
				tokens2.push_back(o2.substr(lastPos, pos - lastPos));

				// Skip delimiters.  Note the "not_of"
				lastPos = o2.find_first_not_of(delimiters, pos);
				// Find next "non-delimiter"
				pos = o2.find_first_of(delimiters, lastPos);
			    }



			total+= (100*Orientacio[IdentificaOrien(tokens[0])][IdentificaOrien(tokens2[0])])*0.15;
			total+= (100*Orientacio[IdentificaOrien(tokens[1])][IdentificaOrien(tokens2[1])])*0.15;
			total+= (100*Colors[IdentificaColor(fig1.color)][IdentificaColor(fig2.color)])*0.4;
            total+= (100-SimilitutNoCiclica(fig1.n_ver,fig1.d_quali,fig2.n_ver,fig2.d_quali))*0.3;

		}

    posi++;

	}
    }
	}

    if (pri.num_figures!=0){

   total=total/pri.num_figures;}
	cout <<" Similitut en "<< pri.nom <<" "<<total <<endl;


return total;






    }




float ReconeixSenyal::Similitut(int ver1,  string des1, int ver2, string des2) {
	Similarity sim;
	int vertice_fig2, figTemp2;
	float dist_points, dist_angle_curvature, dist_length, dist_convexity,
			disimilarity, disimilarity_vertex;
	int Qsimilar_vert;
	int nvert1, nvert2;
	float finalDisimilarity = 101.0;
	vector<int> vTemp;
	string  s1;
	string  s2;
        int v1;
        int v2;
	int dif;

	if (v1 >= v2)
	{
		s1 = des1;
		s2 = des2;
                v1=ver1;
                v2=ver2;
	}
	else
	{
		s1 = des2;
		s2 = des1;
                v1 = ver2;
                v2 = ver1;

	}

	nvert1 = v1;
	nvert2 = v2;
	dif = nvert1 - nvert2;

	//cout << dif <<" "<<nvert1 <<" "<<nvert2;

	/*
	 * Caso en que las figuras no tienen el mismo numero de vertices
	 * Se utiliza un vector v donde se encuentran los indices de la figura
	 * con mayor numero de vertices que se van a comparar con el punto vacio.
	 * Estos indices se actualizan hasta contemplar todas las combinaciones.
	 */
         int encontrado=0;  int i;

	//string s1(s1);
	//string s2(s2);


         for(i=0;i<s1.length();i++) {

            if(s1[i]=='[') {
            encontrado=1;



            }
            if(encontrado==1) {
            s1.erase(i,1);
	    i--;
            encontrado=0;
            }
            }





        encontrado=0;
         for(i=0;i<s2.length();i++) {
            if(s2[i]=='[') {
            encontrado=1;
            }
            if(encontrado==1) {
            s2.erase(i,1);
	    i--;
            encontrado=0;
            }
            }


          const string delimiters = "]";
            vector<string> tokens;


            string::size_type lastPos = s1.find_first_not_of(delimiters, 0);
            // Find first "non-delimiter".
            string::size_type pos     = s1.find_first_of(delimiters, lastPos);

            while (string::npos != pos || string::npos != lastPos)
            {
                // Found a token, add it to the vector.
                tokens.push_back(s1.substr(lastPos+1, pos - lastPos-1));
                // Skip delimiters.  Note the "not_of"
                lastPos = s1.find_first_not_of(delimiters, pos);
                // Find next "non-delimiter"
                pos = s1.find_first_of(delimiters, lastPos);
            }

            tokens.erase(tokens.begin());


            vector<string> tokens2;


             lastPos = s2.find_first_not_of(delimiters, 0);
            // Find first "non-delimiter".
             pos     = s2.find_first_of(delimiters, lastPos);

            while (string::npos != pos || string::npos != lastPos)
            {
                // Found a token, add it to the vector.
                tokens2.push_back(s2.substr(lastPos+1, pos - lastPos-1));//per a llevar també les comes
                // Skip delimiters.  Note the "not_of"
                lastPos = s2.find_first_not_of(delimiters, pos);
                // Find next "non-delimiter"
                pos = s2.find_first_of(delimiters, lastPos);
            }
            tokens2.erase(tokens2.begin());
  			//cout <<"|"<<tokens2[0]<<"|"<<tokens2[1]<<"|"<<tokens2[2]<<"|"<<tokens2[3]<<"|"<<tokens2[4]<<"|";




	if (dif > 0)
	{
		QPoint emptyQpt; //Representa el punto vacio
		int x, actualizable, size = dif, inipos;
		bool seguir, fin, found;

		vector<int> v(size, 0);
		for (int i = 0; i < v.size(); i++)
			v[i] = i;

		fin = false;
		while (!fin)
		{


			int k;
			for (int j = 0; j < nvert2; j++)
			{
				//Inicializamos las variables
				dist_points = 0.0;
				dist_angle_curvature = 0.0;
				dist_length = 0.0;
				dist_convexity = 0.0;
				disimilarity = 0.0;
				disimilarity_vertex = 0.0;
				Qsimilar_vert = 0;

				k = j;
                                QPoint qp1(tokens2[k]);

				for (int i = 0; i < nvert1; i++)
				{
					//cout<<i<<" "<<k<<endl;
					//Nos guardamos los indices por donde empezamos a mirar la figura
					//if (i == 0)
					//	vertice_fig2 = j;
                                        QPoint qp2(tokens[i]);

					found = false;
					for (int n = 0; n < v.size(); n++)
					{

						if (v[n] == i)
						{
							found = true; //Es uno de los indices a comparar con EMPTY
							//cout<<"ENCONTRADO "<<v[n]<<endl;
						}
					}

					if (!found)
					{
						disimilarity_vertex = sim.dissimilarity_between_points(qp2,
								qp1, &dist_points, &dist_angle_curvature,
								&dist_length, &dist_convexity);
						k = (k + 1) % nvert2;
						//cout<<"No Empty: "<<disimilarity_vertex<<endl;

					}
					else // Vertice a comparar con nada, indicado en v
					{
						//disimilarity_vertex = dissimilarity_between_points_v2(f1->qualPtV[i],
						//		emptyQpt, &dist_points, &dist_angle_curvature, &dist_length,
						//		&dist_convexity);
						disimilarity_vertex = 100.0;
						//cout<<"Empty: "<<disimilarity_vertex<<endl;
					}

					//if (disimilarity_vertex == 0.0)
					//{
					//	Qsimilar_vert = Qsimilar_vert + 1;
					//}

					disimilarity += disimilarity_vertex;

					//printf("%d - %d: ", i, j);
					//printf(
					//		"p:%.2f\t a_c:%.2f\t l:%.2f\t c: %.2f\t dis_point: %.2f\t dis_total: %.2f\n",
					//		dist_points, dist_angle_curvature, dist_length, dist_convexity,
					//		disimilarity_vertex, disimilarity);

				}


				//Nos vamos quedando con la distancia menor
				disimilarity = disimilarity / nvert1;

				//cout<<disimilarity<<endl;
				if (disimilarity < finalDisimilarity)
				{
					finalDisimilarity = disimilarity;
					vTemp = v;
					figTemp2 = j;
				}

			}
			//printf("Minimum disimilarity starting (fig1: %d, fig2: %d)\n", 0, fig2);
			//finalDisimilarity=(finalDisimilarity/nvert1);




			v[size - 1] = v[size - 1] + 1;

			seguir = true;
			x = 1;
			actualizable = -1;
			while (seguir)
			{ // Movimiento de los indices en v
				if ((size - x) < 0)
					break;

				//cout<<size-x<<" "<<nvert1<<" "<<size<<endl;
				//cout << "Ey: "<<v[size-x]<<" "<<LIMIT(size-x, nvert1, size)<<endl;
				if (v[size - x] == (nvert1 - (size - (size - x)) + 1))
				{
					if ((size - x) == 0) //El 0 ha llegado al limite, por lo que hemos acabado
					{
						fin = true;
						break;
					}
					actualizable = size - x;
					v[size - x - 1] = v[size - x - 1] + 1;
					x++;
				}
				else
				{
					seguir = false;
					if (actualizable != -1)
					{
						inipos = v[actualizable - 1];
						for (int i = actualizable; i < size; i++)
						{
							inipos++;
							v[i] = inipos;
						}
					}
				}
			}
		}
	}

	else
	{
		QPoint qp1(tokens2[1]);
		//Recorremos las dos imagenes calculando las distancias.
		//La imagen 2 la vamos rotando, y nos quedamos con la distancia menor calculada,
		//de este modo si las imagenes son iguales pero estan en otra posicion
		//no afecta a la comparacion de la forma.
		int k = 0, j;
		while (k < nvert1)
		{
			//Inicializamos las variables
			dist_points = 0.0;
			dist_angle_curvature = 0.0;
			dist_length = 0.0;
			dist_convexity = 0.0;
			disimilarity = 0.0, disimilarity_vertex = 0.0;
			Qsimilar_vert = 0;

			//Recorremos todos los vertices de las dos imagenes
			for (int i = 0; i < nvert1; i++)
			{
				j = (i + k) % nvert1;
				//cout << tokens[j]<<endl;
                                QPoint qp1(tokens2[j]);
                                QPoint qp2(tokens[i]);
				//cout << qp1 <<" "<<qp2 << endl;
				//Nos guardamos los indices por donde empezamos a mirar la figura
				if (i == 0)
					vertice_fig2 = j;

				disimilarity_vertex = sim.dissimilarity_between_points(qp2,
						qp1, &dist_points, &dist_angle_curvature, &dist_length,
						&dist_convexity);

				if (disimilarity_vertex == 0.0)
				{
					Qsimilar_vert = Qsimilar_vert + 1;
				}

				disimilarity = disimilarity + disimilarity_vertex;

			}



			//Nos vamos quedando con la distancia menor
			disimilarity = disimilarity / nvert1;

			if (disimilarity < finalDisimilarity)
			{
				finalDisimilarity = disimilarity;
				figTemp2 = vertice_fig2;
			}

			k++;

		}
		//printf("Minimum disimilarity starting (fig1: %d, fig2: %d)\n", 0, fig2);
		//finalDisimilarity=(finalDisimilarity/nvert1);
	}

	/*cout << "Diferencia de vertices: " << dif << endl;
	if (dif > 0)
	{
		cout << "EMPTYs: {";
		int sz = vTemp.size();
		for (int i = 0; i < sz - 1; i++)
			cout << vTemp[i] << ", ";
		cout << vTemp[sz - 1] << "}" << endl;
	}
	cout << "Vertice de inicio de la f2: " << figTemp2 << endl;
	cout << "Similitud: " << 100.0 - finalDisimilarity << endl;
*/
	return finalDisimilarity;
}

float ReconeixSenyal::SimilitutNoCiclica(int ver1, string des1, int ver2, string des2) {
	Similarity sim;
	int vertice_fig2, figTemp2;
	float dist_points, dist_angle_curvature, dist_length, dist_convexity,
			disimilarity, disimilarity_vertex;
	int Qsimilar_vert;
	int nvert1, nvert2;
	float finalDisimilarity = 101.0;
	vector<int> vTemp;
	string  s1;
	string  s2;
        int v1;
        int v2;
	int dif;

	if (v1 >= v2)
	{
		s1 = des1;
		s2 = des2;
                v1=ver1;
                v2=ver2;
	}
	else
	{
		s1 = des2;
		s2 = des1;
                v1 = ver2;
                v2 = ver1;

	}

	nvert1 = v1;
	nvert2 = v2;
	dif = nvert1 - nvert2;

	//cout << dif <<" "<<nvert1 <<" "<<nvert2;

	/*
	 * Caso en que las figuras no tienen el mismo numero de vertices
	 * Se utiliza un vector v donde se encuentran los indices de la figura
	 * con mayor numero de vertices que se van a comparar con el punto vacio.
	 * Estos indices se actualizan hasta contemplar todas las combinaciones.
	 */
         int encontrado=0;  int i2;

	//string s1(s1);
	//string s2(s2);


         for(i2=0;i2<s1.length();i2++) {

            if(s1[i2]=='[') {
            encontrado=1;



            }
            if(encontrado==1) {
            s1.erase(i2,1);
	    i2--;
            encontrado=0;
            }
            }





        encontrado=0;
         for(i2=0;i2<s2.length();i2++) {
            if(s2[i2]=='[') {
            encontrado=1;
            }
            if(encontrado==1) {
            s2.erase(i2,1);
	    i2--;
            encontrado=0;
            }
            }


          const string delimiters = "]";
            vector<string> tokens;


            string::size_type lastPos = s1.find_first_not_of(delimiters, 0);
            // Find first "non-delimiter".
            string::size_type pos     = s1.find_first_of(delimiters, lastPos);

            while (string::npos != pos || string::npos != lastPos)
            {
                // Found a token, add it to the vector.
                tokens.push_back(s1.substr(lastPos+1, pos - lastPos-1));
                // Skip delimiters.  Note the "not_of"
                lastPos = s1.find_first_not_of(delimiters, pos);
                // Find next "non-delimiter"
                pos = s1.find_first_of(delimiters, lastPos);
            }

            tokens.erase(tokens.begin());


            vector<string> tokens2;


             lastPos = s2.find_first_not_of(delimiters, 0);
            // Find first "non-delimiter".
             pos     = s2.find_first_of(delimiters, lastPos);

            while (string::npos != pos || string::npos != lastPos)
            {
                // Found a token, add it to the vector.
                tokens2.push_back(s2.substr(lastPos+1, pos - lastPos-1));//per a llevar també les comes
                // Skip delimiters.  Note the "not_of"
                lastPos = s2.find_first_not_of(delimiters, pos);
                // Find next "non-delimiter"
                pos = s2.find_first_of(delimiters, lastPos);
            }
            tokens2.erase(tokens2.begin());
  			//cout <<"|"<<tokens2[0]<<"|"<<tokens2[1]<<"|"<<tokens2[2]<<"|"<<tokens2[3]<<"|"<<tokens2[4]<<"|";




	if (dif > 0)
	{
		QPoint emptyQpt; //Representa el punto vacio
		int x, actualizable, size = dif, inipos;
		bool seguir, fin, found;

		vector<int> v(size, 0);
		for (int i = 0; i < v.size(); i++)
			v[i] = i;

		fin = false;
		while (!fin)
		{


			int k;
			for (int j = 0; j < nvert2; j++)
			{
				//Inicializamos las variables
				dist_points = 0.0;
				dist_angle_curvature = 0.0;
				dist_length = 0.0;
				dist_convexity = 0.0;
				disimilarity = 0.0;
				disimilarity_vertex = 0.0;
				Qsimilar_vert = 0;

				k = j;
                                QPoint qp1(tokens2[k]);
				QPoint qp2(tokens[k]);




						disimilarity_vertex = sim.dissimilarity_between_points(qp2,
								qp1, &dist_points, &dist_angle_curvature,
								&dist_length, &dist_convexity);
						k = (k + 1) % nvert2;
						//cout<<"No Empty: "<<disimilarity_vertex<<endl;



					//if (disimilarity_vertex == 0.0)
					//{
					//	Qsimilar_vert = Qsimilar_vert + 1;
					//}

					disimilarity += disimilarity_vertex;

					//printf("%d - %d: ", i, j);
					//printf(
					//		"p:%.2f\t a_c:%.2f\t l:%.2f\t c: %.2f\t dis_point: %.2f\t dis_total: %.2f\n",
					//		dist_points, dist_angle_curvature, dist_length, dist_convexity,
					//		disimilarity_vertex, disimilarity);




				//Nos vamos quedando con la distancia menor
				disimilarity = disimilarity / nvert1;

				//cout<<disimilarity<<endl;
				if (disimilarity < finalDisimilarity)
				{
					finalDisimilarity = disimilarity;
					vTemp = v;
					figTemp2 = j;
				}

			}
			//printf("Minimum disimilarity starting (fig1: %d, fig2: %d)\n", 0, fig2);
			//finalDisimilarity=(finalDisimilarity/nvert1);




			v[size - 1] = v[size - 1] + 1;

			seguir = true;
			x = 1;
			actualizable = -1;
			while (seguir)
			{ // Movimiento de los indices en v
				if ((size - x) < 0)
					break;

				//cout<<size-x<<" "<<nvert1<<" "<<size<<endl;
				//cout << "Ey: "<<v[size-x]<<" "<<LIMIT(size-x, nvert1, size)<<endl;
				if (v[size - x] == (nvert1 - (size - (size - x)) + 1))
				{
					if ((size - x) == 0) //El 0 ha llegado al limite, por lo que hemos acabado
					{
						fin = true;
						break;
					}
					actualizable = size - x;
					v[size - x - 1] = v[size - x - 1] + 1;
					x++;
				}
				else
				{
					seguir = false;
					if (actualizable != -1)
					{
						inipos = v[actualizable - 1];
						for (int i = actualizable; i < size; i++)
						{
							inipos++;
							v[i] = inipos;
						}
					}
				}
			}
		}
	}

	else
	{

		//Recorremos las dos imagenes calculando las distancias.
		//La imagen 2 la vamos rotando, y nos quedamos con la distancia menor calculada,
		//de este modo si las imagenes son iguales pero estan en otra posicion
		//no afecta a la comparacion de la forma.
		int k = 0, j;
		while (k < nvert1)
		{
			//Inicializamos las variables
			dist_points = 0.0;
			dist_angle_curvature = 0.0;
			dist_length = 0.0;
			dist_convexity = 0.0;
			disimilarity = 0.0, disimilarity_vertex = 0.0;
			Qsimilar_vert = 0;

			//cout << tokens[k]<<""<<tokens.size()<<" "<<k<<endl;
                        QPoint qp1(tokens2[k]);
                        QPoint qp2(tokens[k]);
			//Recorremos todos los vertices de las dos imagenes


				disimilarity_vertex = sim.dissimilarity_between_points(qp2,
						qp1, &dist_points, &dist_angle_curvature, &dist_length,
						&dist_convexity);

				if (disimilarity_vertex == 0.0)
				{
					Qsimilar_vert = Qsimilar_vert + 1;
				}

				disimilarity = disimilarity + disimilarity_vertex;





			//Nos vamos quedando con la distancia menor
			disimilarity = disimilarity / nvert1;

			if (disimilarity < finalDisimilarity)
			{
				finalDisimilarity = disimilarity;
				figTemp2 = vertice_fig2;
			}

			k++;

		}
		//printf("Minimum disimilarity starting (fig1: %d, fig2: %d)\n", 0, fig2);
		//finalDisimilarity=(finalDisimilarity/nvert1);
	}

	/*cout << "Diferencia de vertices: " << dif << endl;
	if (dif > 0)
	{
		cout << "EMPTYs: {";
		int sz = vTemp.size();
		for (int i = 0; i < sz - 1; i++)
			cout << vTemp[i] << ", ";
		cout << vTemp[sz - 1] << "}" << endl;
	}
	cout << "Vertice de inicio de la f2: " << figTemp2 << endl;
	cout << "Similitud: " << 100.0 - finalDisimilarity << endl;
*/
	return finalDisimilarity;
}



