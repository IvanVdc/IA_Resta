#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#define UMBRAL 3

using namespace std;

int mat_curbatura [5][5] = {{-1, 0, 1, 6, 7},
			    {0, -1, 0, 1, 6},
			    {1, 0, -1, 1, 1},
			    {6, 1, 1, -1, 8},
			    {7, 6, 1, 8, -1}};

void StringExplode(string str, string separator, vector<string>* results){
   int found;
   found = str.find_first_of(separator);
   while(found != string::npos){
       if(found > 0){
           results->push_back(str.substr(0,found));
       }
       str = str.substr(found+1);
       found = str.find_first_of(separator);
   }
   if(str.length() > 0){
       results->push_back(str);
   }
}


struct Posicion{
  int x;
  int y;
  Posicion(int a, int b){x=a; y=b;}

  bool EsIgual(Posicion p){
    return (abs(p.x - x)<=5 && abs(p.y - y)<=5);
  }
  bool EstaIzq(Posicion p){
    return ((p.x < x) && (abs(p.y - y)<=5));
  }
};

struct Vertice{
  Posicion * pos;
  int conexion;
  int curvatura;
  int longitud;
  int convexidad;
  bool visitado;
  Vertice(int x, int y, int con, int cur, int lon, int conv){
    pos= new Posicion(x,y);
    conexion=con;
    curvatura=cur;
    longitud=lon;
    convexidad=conv;
    visitado=false;
  }
  void mostrar(){
    cout<<"Coordenadas: " << pos->x <<", "<<pos->y<<endl;
    cout<<"Conexion: "<<conexion<<endl;
    cout<<"Curvatura: "<<curvatura<<endl;
    cout<<"Longitud: "<<longitud<<endl;
    cout<<"Convexidad: "<<convexidad<<endl; 
  }
};

struct Figura{
  vector <Vertice> vertices; 
  int tam;

  Figura(vector <Vertice> vecs){
    vertices=vecs;
    tam=vecs.size();
  };

  Figura(string descrip,string descrip2){
    vector <string> result;
    vector <string> result2;
    int x,y;

    descrip=descrip.substr(0,descrip.size()-1);
    descrip2=descrip2.substr(0,descrip2.size()-5);

    StringExplode(descrip, "{", &result);
    StringExplode(descrip2, "]", &result2);
     
    tam=0;
    for (int i = 0; i<result.size(); i++){
      tam++;
      result2[i]=result2[i].substr(2,result2[i].size());

      vector <string> datos;
      result[i]=result[i].substr(0,result[i].size()-2);
      StringExplode(result[i], " ", &datos);
      
      vector <string> puntos;
      datos[0]=datos[0].substr(1,datos[0].size()-1);
      StringExplode(datos[0], ",", &puntos);
      x = atoi(puntos[0].c_str() );
      y = atoi(puntos[1].c_str() );
            
      vector <string> caract;
      StringExplode(result2[i], ",", &caract);

      string conexion;
      string curvatura;
      string longitud;
      string convexidad;
      int con, cu, lo, co;

      conexion=caract[0];
      curvatura = caract[1];
      convexidad  = caract[3];
      longitud = caract[2];

      if (convexidad.compare("convex")==0){
	co=1;
      }
      else{
	co=0;
      }

      if (curvatura.compare("very_acute")==0){
	cu=0;
      }
      else if (curvatura.compare("acute")==0){
	cu=1;
      }
      else if (curvatura.compare("right")==0){
	cu=2;
      }
      else if (curvatura.compare("obtuse")==0){
	cu=3;
      }
      else if (curvatura.compare("very_obtuse")==0){
	cu=4;
      }
      else{
	cerr<<"Error curvatura desconocida"<<curvatura<<endl;
      }


      if (conexion.compare("line-line")==0){
	con=1;
      }
      else{
	con=0;
      }


      if (longitud.compare("msh")==0){
	lo=0;
      }
      else if (longitud.compare("hl")==0){
	lo=1;
      }
      else if (longitud.compare("qsh")==0){
	lo=2;
      }
      else if (longitud.compare("sl")==0){
	lo=3;
      }
      else if (longitud.compare("ql")==0){
	lo=4;
      }
      else if (longitud.compare("dl")==0){
	lo=5;
      }
      else if (longitud.compare("ml")==0){
	lo=6;
      }
      else{
	cerr<<"Error longitud desconocida:"<<longitud<<endl;
      }



      Vertice ver(x, y, con, cu, lo, co);
      vertices.push_back(ver);
    }

    if (abs(vertices[0].pos->y - vertices[tam-1].pos->y) <= UMBRAL){
      vertices[0].pos->y=vertices[tam-1].pos->y;
      Vertice aux (vertices[tam-1].pos->x, vertices[tam-1].pos->y, vertices[tam-1].conexion, vertices[tam-1].curvatura, vertices[tam-1].longitud, vertices[tam-1].convexidad);
      vertices.pop_back();
      vector<Vertice>::iterator it;
      it=vertices.begin();
      vertices.insert(it, aux);
    }
  }

  void mostrar(){
    cout<<"Numero de vertices "<<tam<<endl;
    for (int i=0;i<tam;i++){
      cout<<"Vertice num "<<i<<endl;
      vertices[i].mostrar();
      cout<<endl;
    }
  }

  void PonerEnElEje (){
    int x=vertices[0].pos->x, y=vertices[0].pos->y;
    for (int i = 1; i<tam; i++){
      if (vertices[i].pos->x < x) x = vertices[i].pos->x;
      if (vertices[i].pos->y < y) y = vertices[i].pos->y;
    }

    for (int j = 0; j<tam; j++){
      vertices[j].pos->x-=x;
      vertices[j].pos->y-=y;
    }
    vertices[0].pos->x=0;
    vertices[0].pos->y=0; 

    for (int i = 1; i<tam; i++){
      if (abs(vertices[i].pos->x - vertices[i-1].pos->x)<5)
	vertices[i].pos->x = vertices[i-1].pos->x;
      if (abs(vertices[i].pos->y - vertices[i-1].pos->y)<5)
	vertices[i].pos->y = vertices[i-1].pos->y;
    }

    if (abs(vertices[tam-1].pos->x - vertices[0].pos->x)<5)
      vertices[tam-1].pos->x = vertices[0].pos->x;
    if (abs(vertices[tam-1].pos->y - vertices[0].pos->y)<5)
      vertices[tam-1].pos->y = vertices[0].pos->y;
  }

  void NadaVisitado (){
    for (int i = 0; i<tam; i++)
      vertices[i].visitado=false;
  }

  bool EsFrontera ( Posicion p){
    Posicion *n,*m;
    int i, j;
    int difx, dify, maxim, frontx, fronty, minx, miny;
    for (i=0;i<tam;i++){
      n=vertices[i].pos;
      m=vertices[(i+1)%tam].pos;
      minx = (n->x < m->x)? 1 : -1;
      miny = (n->y < m->y)? 1 : -1;
      difx=abs(n->x - m->x);
      dify=abs(n->y - m->y);
      maxim=max(difx,dify);
      for (j=0; j<maxim; j++){
	frontx = n->x + int((float(difx)/float(maxim))*j*minx);
	fronty = n->y + int((float(dify)/float(maxim))*j*miny); 
	//cout << "punto x " << frontx << " y " << fronty << endl;
	if (p.x == frontx && p.y == fronty)
	  return true;
      }
    }
    return false;
  }

};


Figura* LeerFigura (char * figura){
  int tub[2];
  pipe(tub);

  if(fork()==0){
    if (fork()!=0){
      close(1);
      close(tub[0]);
      dup(tub[1]);
  
      int ret;
      char *cmd[] = { "./RecFormas", "-C", figura, (char *)0 };
      ret = execv ("./RecFormas", cmd);
  
      close(tub[1]);
    }

    else{
      sleep(1);
      system("killall -9 RecFormas");
    }
    exit(0);
  }
  
  else{
    string descrip="";
    string descrip2="";
    close(tub[1]);

    FILE *stream;
    int c;
    bool ant = false, encontrado = false, final = false;
    stream = fdopen (tub[0], "r");
    while (((c = fgetc (stream)) != EOF) and !final){
      if (encontrado){
	descrip+=c;
	if ((char)c=='\n')
	  final=true;
      }
      else{
	if (c==81)
	  ant=true;
	else if (ant and c==68){
	  encontrado=true;
	  for (int i=0; i<12; i++){
	    fgetc (stream);
	  }
	}
      }
    }

    stream = fdopen (tub[0], "r");
    ant = false, encontrado = false, final = false;
    while (((c = fgetc (stream)) != EOF) and !final){
      if ((char)c=='N'){
	ant=true;
      }else if (ant and (char)c=='O'){
	encontrado=true;
	for (int i=0; i<26; i++){
	  fgetc (stream);
	}
      }
      else if(encontrado==true){
	descrip2+=c;
	if ((char)c=='\n')
	  final=true;
      } 
    }
    
    fclose (stream);
    close(tub[0]);

    Figura *fig;
    fig = new Figura(descrip,descrip2);
    return fig;

  }
}


Figura* Restar (Figura *fig1, Figura *fig2){
  vector <Vertice> vertices;
  int x1,y1,x2,y2;
  int i1, i2;
  int i1n, i2n;
  int iguales = 1;

  fig1->NadaVisitado();
  fig2->NadaVisitado();

  fig1->vertices[0].visitado=true;
  fig2->vertices[0].visitado=true;  

  iguales = 1;
  i1n=fig1->tam-1;
  i2n=fig2->tam-1;
  while (iguales) {
    if (fig1->vertices[i1n].pos->EsIgual(*fig2->vertices[i2n].pos)){
      fig1->vertices[i1n].visitado=true;
      fig2->vertices[i2n].visitado=true;
      i1n--;
      i2n--;
      if (i1n == -1){
	Figura *fig_res;
	fig_res = new Figura(vertices);
	return fig_res;
      }
    }
    else iguales = 0;
  }

  iguales = 1;
  i1=1;
  i2=1;
  while (iguales) {
    if (fig1->vertices[i1].pos->EsIgual(*fig2->vertices[i2].pos)){
      fig1->vertices[i1].visitado=true;
      fig2->vertices[i2].visitado=true;
      i1++;
      i2++;
    }
    else iguales = 0;
  }


  //Primera linea de la figura2 hasta llegar al primer vertice no visitado
  for (int j=1; j<fig2->tam; j++){
    if (!fig2->vertices[j].visitado)
      if(fig2->vertices[i2].pos->EstaIzq(*fig2->vertices[j].pos)){
	i2=j;
      }
  }
  
  //  for(desde i2 hasta 0 o hasta encontrar el primer visitado)
  while(i2>0 && fig2->vertices[i2].visitado==false){
    x2=fig2->vertices[i2].pos->x;
    y2=fig2->vertices[i2].pos->y;
    fig2->vertices[i2].visitado=true;
    Vertice ver(x2, y2, 1, -1, -1, -1);
    vertices.push_back(ver);
    i2--;
  }
 
  //Todos los de la figura1 en orden horario
  while(i1<fig1->tam && fig1->vertices[i1].visitado==false){
    x1=fig1->vertices[i1].pos->x;
    y1=fig1->vertices[i1].pos->y;
    fig1->vertices[i1].visitado=true;
    Vertice ver(x1, y1, 1, -1, -1, -1);
    vertices.push_back(ver);
    i1++;
  }

  //Todos los de la figura2 en orden antihorario
  while(i2n>0 && fig2->vertices[i2n].visitado==false){
    x2=fig2->vertices[i2n].pos->x;
    y2=fig2->vertices[i2n].pos->y;
    fig2->vertices[i2n].visitado=true;
    Vertice ver(x2, y2, 1, -1, -1, -1);
    vertices.push_back(ver);
    i2n--;
  }

  Figura *fig_res;
  fig_res = new Figura(vertices);
  return fig_res;

}



int main(){
  //  char *Nombre_figura1 = "gran.jpg";
  char *Nombre_figura1 = "quad2.jpg";
  Figura *fig1;
  fig1=LeerFigura(Nombre_figura1);
  //fig1->mostrar();
  fig1->PonerEnElEje();
  cout<<"------------------------------------------------------------"<<endl;
  cout<<"Figura 1"<<endl;
  fig1->mostrar();

  Figura *fig2;
  //  char *Nombre_figura2 = "mitad1.jpg";
  char *Nombre_figura2 = "quad.jpg";
  fig2=LeerFigura(Nombre_figura2);
  //fig2->mostrar();
  fig2->PonerEnElEje();
  cout<<"------------------------------------------------------------"<<endl;
  cout<<"Figura 2"<<endl;
  fig2->mostrar();

  Figura *fig3;
  fig3 = Restar(fig1,fig2);
  cout<<"------------------------------------------------------------"<<endl;
  cout<<"Figura 3 = Figura 1 - Figura 2"<<endl;
  fig3->mostrar();

  

  cout<<endl<<"jijaju"<<endl;
  return 0;
}
