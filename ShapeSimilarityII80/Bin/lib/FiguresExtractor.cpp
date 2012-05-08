#include "FiguresExtractor.h"
#include "Polyline.cpp"

using namespace std;
using namespace cimg_library;


FiguresExtractor::FiguresExtractor(bool c, int h, int w)
{
  hgt = h;
  wdt = w;
  edgesAlgorithm = 0;
  curDetection = c;
}

/*
FiguresExtractor::~FiguresExtractor(void)
{
  borderPts.clear();
  tempV.clear();
}
*/

FiguresExtractor::FiguresExtractor(Image * img)
{
  image = img;
	hgt = image->hgt;
	wdt = image->wdt;
}

void FiguresExtractor::setSourceImage(Image * img)
{
  image = img;
	hgt = image->hgt;
	wdt = image->wdt;
  if (!borderPts.empty())
  {
    borderPts.clear();
    tempV.clear();
    ed.clear();
  }
}

void FiguresExtractor::clear(void)
{
  image = NULL;
  borderPts.clear();
  tempV.clear();
  ed.clear();
}

void FiguresExtractor::Extract(void)
{
	vector<Figure> figV;
  dbg = false;
  cout<<"Starting figures extraction"<<endl;

	ed.setSrcImg(&(image->img));

	if (edgesAlgorithm == 0)
	{
		ed.Canny(&borderPts); //El resultado de los bordes encontrados por Canny se mete en borders
		if (borderPts.empty())
		{
			throw "No borders found";
		}
	  tempV = borderPts;
	  cout<<tempV.size()<<" "<<borderPts.size()<<endl;

	  cout<<"Edges detected"<<endl;

	  Point2D tempPt;

	  cout<<"Extracting figures..."<<endl;


	  //Con cada iteración se extraen los puntos de una unica figura encontrada en tempV
	  //ademas de eliminarlos del propio vector tempV

	  while (tempV.size()>75)
	  {
	    image->borderPtFgV.push_back(extractPoints());
	  }
	}
	else if (edgesAlgorithm == 1 || edgesAlgorithm == 11)
	{
		float sigma;
  	int k, min;
		if (edgesAlgorithm == 1)
		{
			sigma = 0.45;
			k = 750;
			min = 3500;
		}
		else if (edgesAlgorithm == 11)
		{
			cout<<"- Felzenswalb parameters -"<<endl;

  		cout<<"Sigma: ";
  		cin>>sigma;
  		cout<<"Threshold (k): ";
  		cin>>k;
  		cout<<"Minimum size: ";
  		cin>>min;
  	}

  	vector<vector<Point2D> > tempBorderPtFgV;
  	ed.Felzenswalb(sigma, k, min, &tempBorderPtFgV); //Aplica el algoritmo de Felzenswalb a la imagen
  																									 //y mete el resultado de los bordes separados en figuras dentro de tempBorderPtFgV

  	//for (int i = 0; i<tempBorderPtFgV.size(); i++)
  		//cout<<tempBorderPtFgV[i].size()<<endl;

		arrangeBorders(&tempBorderPtFgV); //Reordenamos los bordes de cada figura y se añaden directamente a image->borderPtFgV

		cout<<"Arrangement with BT completed"<<endl;

		for (int i = 0; i < tempBorderPtFgV.size(); i++)
			tempBorderPtFgV[i].clear();
		tempBorderPtFgV.clear();
	}

  cout<<"Points extracted"<<endl;
  cout<<"Figures' borders found: "<<image->borderPtFgV.size()<<endl;

	if (image->borderPtFgV.size() == 0)
  	throw "No borders found";
  //Se comprueba a continuacion que las figuras sean poligonos cerrados
  //mediante la distancia entre el primer y ultimo punto

	//cout<<ed.felzNeighbours.size()<<" "<<image->borderPtFgV.size()<<endl;

  for(unsigned int a=0;a<image->borderPtFgV.size();a++)
  {
    if(image->borderPtFgV[a].size()<20)
    {
      image->borderPtFgV.erase(image->borderPtFgV.begin()+a);
      if (edgesAlgorithm == 1 || edgesAlgorithm == 2)
      {
      	ed.felzNeighbours.erase(ed.felzNeighbours.begin()+a);
      	for (int i = 0; i< ed.felzNeighbours.size(); i++)
      	{
      		for (int j = 0; j < ed.felzNeighbours[i].size(); j++)
      		{
						if (ed.felzNeighbours[i][j] == a)
						{
      				ed.felzNeighbours[i].erase(ed.felzNeighbours[i].begin()+j);
      				break;
						}
      		}
      		for (int j = 0; j < ed.felzNeighbours[i].size(); j++)
      		{
      			if (ed.felzNeighbours[i][j] > a)
      				ed.felzNeighbours[i][j] = ed.felzNeighbours[i][j] - 1;
      		}
      	}
      }
      a--;
    }
    else
    {
      Point2D pIni = image->borderPtFgV[a].front();
      Point2D pLast = image->borderPtFgV[a].back();

      double dist1 = 0.0;

      Point2D dirV1 = pLast - pIni;
      dist1 = round(dirV1.modulo());

      if(dist1>5)
      {
        image->borderPtFgV.erase(image->borderPtFgV.begin()+a);
        if (edgesAlgorithm == 1 || edgesAlgorithm == 2)
        {
        	ed.felzNeighbours.erase(ed.felzNeighbours.begin()+a);
        	for (int i = 0; i< ed.felzNeighbours.size(); i++)
        	{
        		for (int j = 0; j < ed.felzNeighbours[i].size(); j++)
        		{
							if (ed.felzNeighbours[i][j] == a)
							{
        				ed.felzNeighbours[i].erase(ed.felzNeighbours[i].begin()+j);
        				break;
							}
        		}
        		for (int j = 0; j < ed.felzNeighbours[i].size(); j++)
        		{
        			if (ed.felzNeighbours[i][j] > a)
        				ed.felzNeighbours[i][j] = ed.felzNeighbours[i][j] - 1;
        		}
        	}
        }
        a--;
      }
    }
  }

  vector<vector<Point2D> > tempBrdFg(image->borderPtFgV.size());

  //vpFinal = borderPtFgV;

  /*
  for (unsigned int i=0; i<borderPtFgV.size(); i++)
    for (unsigned int j=0; j<borderPtFgV[i].size(); j++)
      borderFg.push_back(borderPtFgV[i][j]);
  */

  vector<Point2D> vpOrig, vpFig, vpTemp;

  bool sthgToCalculate = false; // Variable chivata que indica si queda algo por calcular

  /*
	float tol; // aprox. tolerance for polyline algorithm
  cout << "Tolerancia: ";
	cin >> tol;
	*/

  //Intento de Gaussiana tras Canny
  for (unsigned int i=0; i<image->borderPtFgV.size(); i++)
  {
    Figure figure;
    vpFig = image->borderPtFgV[i];
    for (int k=0; k<2; k++)
    {
      unsigned int sz = vpFig.size();
      for (unsigned int j=0; j<sz; j++)
      {
        if(j==0||j==1||j==sz-1||j==sz-2)
          vpTemp.push_back(vpFig[j]);
        else
        {
          double desp = (vpFig[j-2].x*3 + vpFig[j-1].x*2 + vpFig[j].x + \
              vpFig[j+1].x*2 + vpFig[j+2].x*3) / 11;
          double base = (vpFig[j-2].y*3 + vpFig[j-1].y*2 + vpFig[j].y + \
              vpFig[j+1].y*2 + vpFig[j+2].y*3) / 11;
          vpTemp.push_back(Point2D (desp,base));
        }
      }
      vpFig.clear();
      vpFig = vpTemp;
      vpTemp.clear();
    }
    vpOrig.clear();
    vpOrig = vpFig;


    float tempCol[] = {140,140,140};
    for(unsigned int j=0; j<vpFig.size(); j++)
      image->imgRes.draw_point(vpFig[j].getX(), vpFig[j].getY(), tempCol);

//     vpTesting = image->borderPtFgV[i];
//    float temp2Col[] = {255,0,0};
//    for(unsigned int j=0; j<vpTesting.size(); j++)
//      image->imgRes.draw_point(vpTesting[j].getX(), vpTesting[j].getY(), temp2Col);


    /*
    for(unsigned int j=0; j<vpFig.size(); j++)
    {
      dd[(int)vpFig[j].x][(int)vpFig[j].y]=0xff000000;
    }
    */

    //Primer filtrado
    unsigned int paso=5;

    unsigned int sz = vpFig.size();
    for(unsigned int j=0;j<sz;j+=paso)
    {
      if (j<sz)
        vpTemp.push_back(vpFig[j]);
    }
    vpFig = vpTemp;
    vpTemp.clear();

    if (dbg)
    {
      cout<<"Primer filtrado evita NaN"<<endl;
      cout<<vpFig.size()<<endl;
    }

    tempCol[0] = 0;
    tempCol[1] = 0;
    tempCol[2] = 0;
    for(unsigned int j=0; j<vpFig.size(); j++)
      image->imgRes.draw_point(vpFig[j].getX(), vpFig[j].getY(), tempCol);


  	/******* PABLO> Polyline added *************/

    /*
		cout << "\nStarting polyline simplification process..." << endl;


		unsigned int infoVerSize = vpFig.size();
		Point2D* vPoly = new Point2D[infoVerSize];
		Point2D* vPolyRes = new Point2D[infoVerSize];
		// Contruccion vector Point2D apartir de vector shapePt
		for (unsigned int j = 0; j < infoVerSize; j++)
		{
			vPoly[j] = vpFig[j];
		}

		int vPolyResSize;

		vPolyResSize = poly_simplify(tol, vPoly, infoVerSize, vPolyRes);
		cout << "Fig " << i << ":\nTalla orig: " << infoVerSize << "\tTalla simp: "
				<< vPolyResSize << endl;

		vpFig.clear();
		for (unsigned int j = 0; j < vPolyResSize; j++)
		{
			vpFig.push_back(vPolyRes[j]);
		}
		delete vPoly;
		//delete vPolyRes;

		cout << "\nEnding polyline simplification..." << endl;
	*/

		/********************************************/


    // Se hace un filtrado para eliminar los vertices que no tienen "informacion interesante":
    // se borra los vertices colineales con los de su alrededor o las curvas sin mucho angulo.
    // Es un filtrado convergente: se pasa varias veces incrementando el valor del angulo
    // para quedarse solo con la informacion realmente relevante
    tempCol[0] = 255;
    tempCol[1] = 0;
    tempCol[2] = 0;

    paso=1;
		int kmax = 1;
    for (int k=0; k<kmax; k++)
    {
      unsigned int szBefore=0;
      unsigned int sz = vpFig.size();
      while (szBefore!=sz)
      {
        unsigned int j=0;
        szBefore = sz;
        while(j<sz)
        {
          unsigned int rear = (j+paso)%sz;
          unsigned int prv = j;
          if (prv<paso)
            prv += sz;
          prv -= paso;

          Point2D A = vpFig[prv];
          Point2D B = vpFig[j];
          Point2D C = vpFig[rear];
          float pxtemp1 = (float)A.x*1000000/(float)wdt;
          float pytemp1 = (float)A.y*1000000/(float)hgt;
          float pxtemp2 = (float)B.x*1000000/(float)wdt;
          float pytemp2 = (float)B.y*1000000/(float)hgt;
          float pxtemp3 = (float)C.x*1000000/(float)wdt;
          float pytemp3 = (float)C.y*1000000/(float)hgt;
          float vector1x = pxtemp2-pxtemp1;
          float vector1y = pytemp2-pytemp1;
          float vector2x = pxtemp3-pxtemp2;
          float vector2y = pytemp3-pytemp2;
          double cosangulo = (vector1x*vector2x+vector1y*vector2y)/(sqrt(vector1x*vector1x+vector1y*vector1y)*sqrt(vector2x*vector2x+vector2y*vector2y));

          //if (k==2 || k==3)
            //printf("%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",pxtemp1,pytemp1,pxtemp2,pytemp2,pxtemp3,pytemp3,vector1x,vector1y,vector2x,vector2y,cosangulo);

          //Si los vertices forman cierto angulo entre ellos, los anyado a la lista final
          float temp = 0.95-k*k*0.015; //0.95-k*k*0.015;
          if(abs(cosangulo)>temp)
          {
            //if (k==3 || k== 2) cout<<"Elimino "<<vpFig[j]<<"; k = "<<k<<"; comp = "<<temp<<endl;
            vpFig.erase(vpFig.begin()+j);
            //image->imgRes.draw_point(vpFig[j].getX(), vpFig[j].getY(), tempCol);
          }
          else
            j+=paso;
          sz=vpFig.size();
        }
      }
    }

    if (dbg)
    {
      cout<<"Filtrado de vertices con informacion interesante (verde)"<<endl;
      cout<<vpFig.size()<<endl;
      cout<<vpFig[0]<<endl;
    }


    tempCol[0] = 10;
    tempCol[1] = 255;
    tempCol[2] = 10;
    for(unsigned int j=0; j<vpFig.size(); j++)
      image->imgRes.draw_point(vpFig[j].getX(), vpFig[j].getY(), tempCol);


    // A continuacion se filtran los vertices cercanos que puedan quedar

    float trshold=0.0;
    float trshold_unstd=0.0;
    //Se calcula un umbral automatico para cada figura, que sea igual a la X-ima parte
    //de su lado mas largo
    //Busqueda de la mayor distancia entre puntos

    for (unsigned int j=0; j<vpFig.size();j++)
    {
      unsigned int sz = vpFig.size();
      unsigned int prv = j;
      if (prv == 0)
        prv += sz;
      prv--;

      Point2D A = vpFig[prv];
      Point2D B = vpFig[j];

      float part = 5; //X-ima parte del lado mas largo
      part /= 100;

      float pxtemp1 = (float)A.x*1000000/(float)wdt;
      float pytemp1 = (float)A.y*1000000/(float)hgt;
      float pxtemp2 = (float)B.x*1000000/(float)wdt;
      float pytemp2 = (float)B.y*1000000/(float)hgt;
      float temp_max= (float) sqrt(pow(pxtemp1-pxtemp2, 2)+pow(pytemp1-pytemp2, 2))*part;//X-ima parte del lado mas largo
      if (temp_max>trshold)
        trshold=temp_max;
      float temp_max2= (float) sqrt(pow(A.x-B.x, 2)+pow(A.y-B.y, 2))*part;//X-ima parte del lado mas largo
      if (temp_max2>trshold_unstd)
        trshold_unstd=temp_max2;
    }

    sz = vpFig.size();
    for (unsigned int j=0; j<sz; j++)
    {

      unsigned int prv = j;

      if (prv == 0)
        prv = sz;
      prv--;

      unsigned int rear = (j+1)%sz;

      Point2D A = vpFig[prv];
      Point2D B = vpFig[j];

      float pxtemp1 = (float)A.x*1000000/(float)wdt;
      float pytemp1 = (float)A.y*1000000/(float)hgt;
      float pxtemp2 = (float)B.x*1000000/(float)wdt;
      float pytemp2 = (float)B.y*1000000/(float)hgt;

      //if ((abs((pytemp1-pytemp2))<trshold) && (abs(pxtemp1-pxtemp2)<trshold))
			if (sqrt(pow(pxtemp1-pxtemp2, 2) + pow(pytemp1-pytemp2, 2)) < trshold)
      {
        //para saber si tengo que borrar el v�rtice actual o el anterior,
        //compruebo si forma parte de la misma "recta" o no, calculando los �ngulos
        //con respecto a los otros v�rtices

        Point2D C = vpFig[rear];

        float pxtemp3 = (float)C.x*1000000/(float)wdt;
        float pytemp3 = (float)C.y*1000000/(float)hgt;
        float vector1x = pxtemp1-pxtemp2;
        float vector1y = pytemp1-pytemp2;
        float vector2x = pxtemp2-pxtemp3;
        float vector2y = pytemp2-pytemp3;

        double cosangulo = (vector1x*vector2x+vector1y*vector2y)/(sqrt(vector1x*vector1x+vector1y*vector1y)*sqrt(vector2x*vector2x+vector2y*vector2y));
        if(cosangulo>0.85) // Son paralelos
          vpFig.erase(vpFig.begin()+j);
        else
          vpFig.erase(vpFig.begin()+prv);
        sz--;
        j--;
      }
    }

    if (dbg)
    {
      cout<<"Filtrado de vertices cercanos (azul)"<<endl;
      cout<<vpFig.size()<<endl;
    }
    //dbg = false;

		/*
    tempCol[0] = 0;
    tempCol[1] = 0;
    tempCol[2] = 255;
    for(unsigned int j=0; j<vpFig.size(); j++)
      image->imgRes.draw_point(vpFig[j].getX(), vpFig[j].getY(), tempCol);
		*/

    // Ahora se intenta extraer las características de los tramos de la siguiente forma:
    // Se calcula la distancia entre el centro de los vertices hallados y el centro real
    // del borde de la figura. Cuanto mayor sea, mas probabilidad de encontrarnos ante una curva
    // Segunda version: ademas calcula lo mismo para la primera y ultima octava parte del tramo
    sz = vpFig.size();
    unsigned int szOrig=vpOrig.size();
    vector<shapePt> vpshapeFig;
    shapePt spt;
    unsigned int first, second;

    if (!curDetection)
    {
    	spt.shape = 0;
    	for (unsigned int j = 0; j < sz; j++)
    	{
    		spt.pt = vpFig[j];
    		vpshapeFig.push_back(spt);
    	}
    }

    else if (curDetection)
    {
    	for (unsigned int j = 0; j < sz; j++)
			{
				unsigned int rear = (j + 1) % sz;
				for (unsigned int k = 0; k < vpOrig.size(); k++)
				{
					if (vpOrig[k] == vpFig[j])
						first = k;
					if (vpOrig[k] == vpFig[rear])
						second = k;
				}
				first = (first + 0) % szOrig;
				if (second < 5)
					second += szOrig;
				second -= 5;

				Point2D A = vpOrig[first];
				Point2D B = vpOrig[second];

				if (first > second)
					second += szOrig;

				int subtraction = second - first;
				unsigned int center = (first + (subtraction) / 2) % szOrig;
				Point2D C = vpOrig[center];

				unsigned int fstQuarter = (first + (subtraction) / 8) % szOrig;
				unsigned int secQuarter = (first + (subtraction) * 7 / 8) % szOrig;

				Point2D D = vpOrig[fstQuarter];
				Point2D E = vpOrig[secQuarter];

				int Cxprima = (int) (B.x + A.x) / 2;
				int Cyprima = (int) (B.y + A.y) / 2;
				int Dxprima = (int) (A.x + (B.x - A.x) / 8);
				int Dyprima = (int) (A.y + (B.y - A.y) / 8);
				int Exprima = (int) (A.x + (B.x - A.x) * 7 / 8);
				int Eyprima = (int) (A.y + (B.y - A.y) * 7 / 8);

				//float pxtemp1=(float)A.x*1000000/(float)wdt;
				//float pytemp1=(float)A.y*1000000/(float)hgt;
				//float pxtemp2=(float)B.x*1000000/(float)wdt;
				//float pytemp2=(float)B.y*1000000/(float)hgt;
				float pxtemp3 = (float) C.x * 1000000 / (float) wdt;
				float pytemp3 = (float) C.y * 1000000 / (float) hgt;
				float pxtemp4 = (float) D.x * 1000000 / (float) wdt;
				float pytemp4 = (float) D.y * 1000000 / (float) hgt;
				float pxtemp5 = (float) E.x * 1000000 / (float) wdt;
				float pytemp5 = (float) E.y * 1000000 / (float) hgt;
				float pxcentr = (float) Cxprima * 1000000 / (float) wdt;
				float pycentr = (float) Cyprima * 1000000 / (float) hgt;
				float pxdprima = (float) Dxprima * 1000000 / (float) wdt;
				float pydprima = (float) Dyprima * 1000000 / (float) hgt;
				float pxeprima = (float) Exprima * 1000000 / (float) wdt;
				float pyeprima = (float) Eyprima * 1000000 / (float) hgt;

				double dist1 = DISTANCE(pxcentr, pycentr, pxtemp3, pytemp3) / MILLION;
				double dist2 = DISTANCE(pxdprima, pydprima, pxtemp4, pytemp4) / MILLION;
				double dist3 = DISTANCE(pxeprima, pyeprima, pxtemp5, pytemp5) / MILLION;
				//      double dist1 = sqrt((pxtemp3-pxcentr)*(pxtemp3-pxcentr)+(pytemp3-pycentr)*(pytemp3-pycentr))/1000000;
				//      double dist2 = sqrt((pxtemp4-pxdprima)*(pxtemp4-pxdprima)+(pytemp4-pydprima)*(pytemp4-pydprima))/1000000;
				//      double dist3 = sqrt((pxtemp5-pxeprima)*(pxtemp5-pxeprima)+(pytemp5-pyeprima)*(pytemp5-pyeprima))/1000000;

				spt.pt = vpFig[j];
				if (((dist1 - dist2) > 0.005) && ((dist1 - dist3) > 0.005))
					spt.shape = 1;
				else
					spt.shape = 0;
				vpshapeFig.push_back(spt);
			}
    }

    if (dbg) cout<<"Primer calculo de shape"<<endl;

    vector<shapePt> vpshapeTemp;

    bool eqVectors = false;
    while (!eqVectors)
    {
      // De nuevo una solucion convergente: se supone que ayudara a la hora de convertir curvas
      // en figuras de "todo circulos" que se podran utilizar despues para recalcularlas
      // mediante pendientes
      vpshapeTemp = vpshapeFig;
      eqVectors = true;

      unsigned int sz = vpshapeFig.size();
      unsigned int szOrig = vpOrig.size();
      unsigned int prv, rear, first, second, center;
      //float pxtemp1, pytemp1, pxtemp2, pytemp2, pxtemp3, pytemp3, vector1x, vector1y, vector2x, vector2y;
      //double cosangulo;

      for(unsigned int j=0;j<sz;j++)
      {
        prv = j;
        if (prv == 0)
          prv = sz;
        prv--;

        int s1 = vpshapeFig[prv].shape;
        int s2 = vpshapeFig[j].shape;

        // filtramos recta-curva

        if ((s1==0) && (s2==1))
        {
        //en vez de usar el vertice real, dejamos un margen de unos 10 pixeles
        //para intentar mejorar problemas de curvas

          for (unsigned int k= 0; k<vpOrig.size(); k++) {
            if (vpOrig[k] == vpshapeFig[prv].pt)
              first = k;
            if (vpOrig[k] == vpshapeFig[j].pt)
              second = k;
          }

          first = (first+10)%szOrig;
          if (second<5)
            second += szOrig;
          second -= 5;

          Point2D A = vpOrig[first];
          Point2D B = vpOrig[second];

          if (first>second)
            second += szOrig;

          center = (first + (second - first) / 2) % szOrig;
          Point2D C = vpOrig[center];

          float pxtemp1=(float)A.x*1000000/(float)wdt;
          float pytemp1=(float)A.y*1000000/(float)hgt;
          float pxtemp2=(float)B.x*1000000/(float)wdt;
          float pytemp2=(float)B.y*1000000/(float)hgt;
          float pxtemp3=(float)C.x*1000000/(float)wdt;
          float pytemp3=(float)C.y*1000000/(float)hgt;

          float vector1x=pxtemp3-pxtemp1;
          float vector1y=pytemp3-pytemp1;
          float vector2x=pxtemp2-pxtemp3;
          float vector2y=pytemp2-pytemp3;

          double cosangulo=(vector1x*vector2x+vector1y*vector2y)/ \
            (sqrt(vector1x*vector1x+vector1y*vector1y)*sqrt(vector2x*vector2x+vector2y*vector2y));

          if (cosangulo<0.991)
          {
            vpshapeFig[prv].shape = 1;
            eqVectors = false;
          }
        }


        // Ahora probaremos el filtrado curva-recta

        rear = (j+1)%sz;

        int s3= vpshapeFig[rear].shape;

        if ((s3==0) && (s2==1))
        {
        //en vez de usar el vertice real, dejamos un margen de unos 10 pixeles
        //para intentar mejorar problemas de curvas

          for (unsigned int k= 0; k<vpOrig.size(); k++)
            if (vpOrig[k] == vpshapeFig[rear].pt)
              first = k;

          first = (first+10)%szOrig;
          second = (first+20)%szOrig;

          Point2D A = vpOrig[first];
          Point2D B = vpOrig[second];

          if (first>second)
            second += szOrig;

          unsigned int center = (first + (second - first) / 2) % szOrig;
          Point2D C = vpOrig[center];

          float pxtemp1=(float)A.x*1000000/(float)wdt;
          float pytemp1=(float)A.y*1000000/(float)hgt;
          float pxtemp2=(float)B.x*1000000/(float)wdt;
          float pytemp2=(float)B.y*1000000/(float)hgt;
          float pxtemp3=(float)C.x*1000000/(float)wdt;
          float pytemp3=(float)C.y*1000000/(float)hgt;

          float vector1x=pxtemp3-pxtemp1;
          float vector1y=pytemp3-pytemp1;
          float vector2x=pxtemp2-pxtemp3;
          float vector2y=pytemp2-pytemp3;

          double cosangulo=(vector1x*vector2x+vector1y*vector2y)/ \
            (sqrt(vector1x*vector1x+vector1y*vector1y)*sqrt(vector2x*vector2x+vector2y*vector2y));

          if (cosangulo<=0.99)
          {
            vpshapeFig[rear].shape = 1;
            eqVectors = false;
          }
        }
      }
    }


    unsigned int m=0;
    int numCurves=0; //numCurves contara cuantas hemos borrado. Si se eliminan mas de dos
                     //seguidas, consideraremos que hay algo para calcular mediante
                     //el metodo normal
    while(m<vpshapeFig.size())
    {
      int prv = m;
      if (prv == 0)
        prv = vpshapeFig.size();
      prv--;

      if (vpshapeFig.size()>1) //Si se pueden eliminar m�s elementos
      {
        int t1 = vpshapeFig[prv].shape;
        int t2 = vpshapeFig[m].shape;
        if ((t1==1) && (t2==1)) //Si hay dos curvas seguidas, se elimina la segunda
        {
          vpshapeFig.erase(vpshapeFig.begin()+m);
          numCurves++;
          if (numCurves>2)
            sthgToCalculate = true; //Avisa al metodo normal que se ocupe de los poligonos que haya
        }
        else
          m++;
      }
      else
        m++; //Si s�lo hay un elemento, incrementa el contador para que pase de la figura
    }// Fin del while

    if (numCurves>2)
    {
      tempBrdFg[i] = vpOrig;//Anyadimos el poligono al vector para que lo procese por el otro modo
      vpshapeFig.clear(); //Y lo quitamos de nuestro vector
    }

    m=0;
    vpshapeTemp.clear();

    sz = vpshapeFig.size();
    szOrig = vpOrig.size();
    while(m<sz)
    {
      int rear = (m+1)%sz;
      int t2 = vpshapeFig[rear].shape;
      int t1 = vpshapeFig[m].shape;
      vpshapeTemp.push_back(vpshapeFig[m]);
      if ((t1==1) && (t2==0))  //Es el tramo que buscamos para recalcular
      {                           //pendientes
        vector<Point2D> vsegment;
        unsigned int first, second;

        if (dbg) cout<<"vpSz: "<<vpOrig.size()<<endl;
        for (unsigned int k = 0; k<vpOrig.size(); k++)
        {
          if (vpOrig[k] == vpshapeFig[m].pt)
          {  first = k;
            if (dbg)
            {
              cout<<"First founded: "<<first<<endl;
              cout<<vpOrig[k]<<" == "<<vpshapeFig[m].pt<<endl;
            }
          }
          if (vpOrig[k] == vpshapeFig[rear].pt)
          {
            second = k;
            if (dbg)
            {
              cout<<"Second founded: "<<second<<endl;
              cout<<vpOrig[k]<<" == "<<vpshapeFig[rear].pt<<endl;
            }
          }
        }
        if (dbg) cout<<second<<endl;

        if (dbg) cout<<"Busqueda de first y second finalizada"<<endl;

        first = (first+10) % szOrig;
        if (second<10)
          second += szOrig;
        second -= 10;
        if (first>second)
          second += szOrig;

        if (dbg) cout<<"First: "<<first<<" ; Second: "<<second<<endl;

        for (unsigned int k=first; k<=second; k++)
          vsegment.push_back(vpOrig[k%szOrig]);

        vector<int> indices;
        //En el siguiente metodo busco los vertices iniciales en funcion de como varia la pte
        indices = findVertices(vsegment);

        if (dbg) cout<<"Finished findVertices"<<endl;

        //buscamos los vertices reales de entre los encontrados en findVertices mirando los ptos
        //alrededor de cada vertice en que direccon van, es decir como van variando la x y la y
        vector<ptInd> vert_final = improveVertices(vsegment, indices);

        if (dbg) cout<<"Finished improveVertices"<<endl;

        if (vert_final.size()>0) //Si hay algo de lo que extraer, lo extraemos
        {
          vector<shapePt> vert_final2 = findSegments(vert_final, vsegment);

          if (dbg) cout<<"Finished findSegments"<<endl;
          //"Implantamos" el tramo a nuestra figura si sus puntos no estan demasiado cerca de los
          //ya existentes
          for (unsigned int j=0; j<vert_final2.size(); j++)
          {
            int pxtemp1,pytemp1,pxtemp2,pytemp2,pxtemp3,pytemp3;
            pxtemp1 = (int) vert_final2[j].pt.x;
            pytemp1 = (int) vert_final2[j].pt.y;
            pxtemp2 = (int) vpOrig[first].x;
            pytemp2 = (int) vpOrig[first].y;
            pxtemp3 = (int) vpOrig[second%szOrig].x;
            pytemp3 = (int) vpOrig[second%szOrig].y;
            if (((abs(pytemp1-pytemp2)<trshold_unstd) && (abs(pxtemp1-pxtemp2)<trshold_unstd)) &&
              ((abs(pytemp1-pytemp3)<trshold_unstd) && (abs(pxtemp1-pxtemp3)<trshold_unstd)))
            {
              //cout<<"Pa dentro: "<<vert_final2[j]<<endl;
              vpshapeTemp.push_back(vert_final2[j]);
            }
          }// fin del for
        }//fin de la extraccion
      } // fin if curva && recta
      m++;
    } // Fin while(m<sz)


    vpshapeFig = vpshapeTemp;

    szOrig = vpOrig.size();
    //Si habia alguna parte de recta-curva-recta, calculamos el punto medio de la curva
    //(suponemos que lo anterior no lo ha hecho bien)
    for(unsigned int j=0; j<vpshapeFig.size(); j++)
    {
      sz = vpshapeFig.size();
      int prv = j;
      if (prv == 0)
        prv = sz;
      prv--;

      int back = (j+1)%sz;

      int t1 = vpshapeFig[prv].shape;
      int t2 = vpshapeFig[j].shape;
      int t3 = vpshapeFig[back].shape;
      if ((t1==0) && (t2==1) && (t3==0)) //Falta un punto de m�xima pendiente
      {
        unsigned int first, second, center;
        for (unsigned int k = 0; k<szOrig; k++)
        {
          if (vpOrig[k] == vpshapeFig[j].pt)
            first = k;
          if (vpOrig[k] == vpshapeFig[back].pt)
            second = k;
        }
        first = (first+10) % szOrig;
        if (second < 10)
          second += szOrig;
        second -= 10;
        if (first > second) second += szOrig;
        center = (first+(second-first)/2)%szOrig;
        shapePt spt;
        spt.pt = vpOrig[center];
        spt.shape = 1;
        vpshapeFig.insert(vpshapeFig.begin()+back, 1, spt);
      }
    }
    // Fin del procesado para UNA figura

    if (dbg) cout<<"Fin del procesado de una figura"<<endl;

    figure.infoVertices.clear();
    for(unsigned int j=0; j<vpshapeFig.size();j++)
      figure.infoVertices.push_back(vpshapeFig[j]);
      //vpFig.push_back(vpshapeFig[j].pt);
    figure.comp = false;
    figure.ncomponents = 0;
    figure.isIntern = false;
    figure.id = i;
    figure.area = 0;

    image->borderPtFgV[i] = vpOrig; // actualizamos la lista del vector original

    if (figure.infoVertices.size()==1)
      figure.infoVertices.clear();
    //vpFinal[i] = vpFig;

    image->figV.push_back(figure); //Si no hay figura, sera una figura sin vertices
    vpOrig.clear();
    vpFig.clear();
    vpTemp.clear();
    vpshapeFig.clear();
    vpshapeTemp.clear();

  }// Fin del procesado por el metodo miliet para TODAS las figuras

  if (dbg) cout<<"Fin del procesado miliet para todas las figuras"<<endl;

  if (sthgToCalculate)//Si habia bastantes curvas en el poligono, recalcula la figura por el metodo normal
  {
    cout<<"Something to calculate"<<endl;
    if (dbg) cout<<"Hay algo que calcular"<<endl;

    Figure figure;
    //VARIABLE UTILIZADA PARA SACAR LOS POSIBLES VERTICES DE LA FIGURA COMPROBANDO LOS PUNTOS CADA 'STEP'
    //int step = 20;
    //FOR utilizado para sacar vertices y tramos de cada polígono
    for(unsigned int i=0; i<tempBrdFg.size();i++)
    {
      if (tempBrdFg[i].size()==0) continue; // si la lista esta vacía lo habíamos calculado ya
                                             // y pasa al siguiente polígono
    //En el siguiente método busco los vértices iniciales en función de como varia la pte
      vector<int> indices = findVertices(tempBrdFg[i]);

    //buscamos los vertices reales de entre los encontrados en buscar_vertices
    //mirando los ptos alrededor de cada vertice en que direcc�n van, es decir como van vaiando la x y la y
      vector<ptInd> vert_final = improveVertices(tempBrdFg[i], indices);

    //Eliminar repetidos de vert_final
      vector<ptInd> vert_final2;
      //Point2D p1, p2, p;
      unsigned int szVF = vert_final.size();
      for(unsigned int m=0; m<szVF; m++)
      {
        int ind1 = vert_final[m].index;
        int ind2 = vert_final[(m+1)%szVF].index;

        if(abs(ind2-ind1)>5)
          vert_final2.push_back(vert_final[m]);
      }


      //�Qu� pasa si el primer elemento encontardo es de los 20 anteriores a ind1(=0)?
      if(vert_final2[0].index > vert_final2[1].index)
      {
        vert_final2.push_back(vert_final[0]);
        vert_final2.erase(vert_final2.begin(), vert_final2.begin()+1);
      }

      vert_final.clear();
      for (unsigned int m=0; m<vert_final2.size(); m++)
        vert_final.push_back(vert_final2[m]);

      vert_final2.clear();
      vector<ptInd> vertices;
      ptInd pi;
      for (unsigned int b=0;b<indices.size()-1;b=b+2)
      {
        pi.index = indices[b];
        pi.pt = tempBrdFg[i][pi.index];
        vertices.push_back(pi);
      }

      //Una vez encontrados los vértices reales de la figura, miro cada tramo qué es, recta o curva.
      vector<shapePt> vertSegm = findSegments(vert_final, tempBrdFg[i]);

      float thold = 0.0;
      float part = 15.0;
      //Calculamos un umbral automático para cada fig, que sea igual a la octava parte de su lado más largo
      //Búsqueda de la mayor distancia entre puntos

      for (unsigned int b=0; b<vertSegm.size(); b++){
        unsigned int prv = b;
        if (prv == 0) prv = vertSegm.size();
        prv--;
        double pxtemp1 = vertSegm[prv].pt.x / (float) wdt;
        double pytemp1 = vertSegm[prv].pt.y / (float) hgt;
        double pxtemp2 = vertSegm[b].pt.x / (float) wdt;
        double pytemp2 = vertSegm[b].pt.y / (float) hgt;
        double temp_max= (sqrt((((pxtemp1-pxtemp2)*(pxtemp1-pxtemp2))+
              ((pytemp1-pytemp2)*(pytemp1-pytemp2)))))/part;//Octava parte del lado mas largo
        if (temp_max>thold) thold=temp_max;
      }

      // Filtro vértices demasiado próximos

      for (unsigned int b=0; b<vertSegm.size(); b++)
      {
        unsigned int prv = b;
        unsigned int back = (b+1)%vertSegm.size();
        if (prv == 0) prv = vertSegm.size();
        prv--;
        double pxtemp1 = vertSegm[prv].pt.x / (float) wdt;
        double pytemp1 = vertSegm[prv].pt.y / (float) hgt;
        double pxtemp2 = vertSegm[b].pt.x / (float) wdt;
        double pytemp2 = vertSegm[b].pt.y / (float) hgt;

        if ((abs((pytemp1-pytemp2))<thold) && (abs(pxtemp1-pxtemp2)<thold))
        {
          //para saber si tengo que borrar el v�rtice actual o el anterior,
          //compruebo si forma parte de la misma "recta" o no, calculando las pendientes
          //con respecto a los otros v�rtices
          double pxtemp3 = vertSegm[back].pt.x / (float) wdt;
          double pytemp3 = vertSegm[back].pt.y / (float) hgt;

          double vector1x=pxtemp1-pxtemp2;
          double vector1y=pytemp1-pytemp2;
          double vector2x=pxtemp2-pxtemp3;
          double vector2y=pytemp2-pytemp3;
          double cosangulo = (vector1x*vector2x+vector1y*vector2y)/(sqrt(vector1x*vector1x+vector1y*vector1y)*sqrt(vector2x*vector2x+vector2y*vector2y));
          if(cosangulo>0.8) // Son paralelos
            vertSegm.erase(vertSegm.begin()+b, vertSegm.begin()+b+1);
          else
            vertSegm.erase(vertSegm.begin()+prv, vertSegm.begin()+prv+1);
        }
      }

      //Filtro tramos con características posiblemente mal calculadas

      for (unsigned int b=0;b<vertSegm.size();b++)
      {
        unsigned int prv = b;
        if (prv == 0) prv = vertSegm.size();
        prv--;
        unsigned int back = (b+1)%vertSegm.size();

        int s1 = vertSegm[prv].shape;
        int s2 = vertSegm[b].shape;
        int s3 = vertSegm[back].shape;

        if ((s1!=s2) && (s2!=s3))
				{
          if(s1==0 && s2==1 && s3==0)
					{
          	vertSegm[b].shape = 0;
					}
        	else if(s1==1 && s2==0 && s3==1) {
          //Comprobamos que no sea una forma redonda con un tramo recto importante
          double pxtemp1 = vertSegm[prv].pt.x;
          double pytemp1 = vertSegm[prv].pt.y;
          double pxtemp2 = vertSegm[b].pt.x;
          double pytemp2 = vertSegm[b].pt.y;
          double pxtemp3 = vertSegm[back].pt.x;
          double pytemp3 = vertSegm[back].pt.y;

          double vector1x = pxtemp1-pxtemp2;
          double vector1y = pytemp1-pytemp2;
          double vector2x = pxtemp2-pxtemp3;
          double vector2y = pytemp2-pytemp3;

          double cosangulo=(vector1x*vector2x+vector1y*vector2y)/(sqrt(vector1x*vector1x+vector1y*vector1y)*sqrt(vector2x*vector2x+vector2y*vector2y));
          if(abs(cosangulo)>0.6)
            vertSegm[b].shape = 1;
        	}
				}
      }

      // Añadimos el resultado en su correspondiente posición del vector final
      image->figV[i].infoVertices.clear();
      //figure.infoVertices.clear();
      for (unsigned int b = 0; b<vertSegm.size(); b++)
        //figure.infoVertices.push_back(vertSegm[b]);
        image->figV[i].infoVertices.push_back(vertSegm[b]);
      image->figV[i].comp = false;
      image->figV[i].id = i;
      //figure.comp = false;
      //figure.id = i;

      //image->figV[i] = figure;
    }
  }


	/******* PABLO> Polyline added *************/

  /*
	cout << "\nStarting polyline simplification process..." << endl;
	float tol; // aprox. tolerance for polyline algorithm

	cout << "Tolerancia: ";
	cin >> tol;
	for (unsigned int i = 0; i < image->figV.size(); i++)
	{
		unsigned int infoVerSize = image->figV[i].infoVertices.size();
		Point2D* vPoly = new Point2D[infoVerSize];
		Point2D* vPolyRes = new Point2D[infoVerSize];
		// Contruccion vector Point2D apartir de vector shapePt
		for (unsigned int j = 0; j < infoVerSize; j++)
		{
			vPoly[j] = image->figV[i].infoVertices[j].pt;
		}

		int vPolyResSize;

		vPolyResSize = poly_simplify(tol, vPoly, infoVerSize, vPolyRes);
		cout << "Fig " << i << ":\nTalla orig: " << infoVerSize << "\tTalla simp: "
				<< vPolyResSize << endl;
		if (vPolyResSize < infoVerSize)
		{ // Se ha simplificado el vector
			bool testigo;
			int dec = 0;
			//Comparamos y los ptos simplificados los eliminamos del vector original
			for (unsigned int j = 0; j < infoVerSize - dec; j++)
			{
				testigo = false;
				for (unsigned int k = 0; k < vPolyResSize; k++)
				{
					if (image->figV[i].infoVertices[j].pt == vPolyRes[k])
					{
						testigo = true;
						break;
					}
				}
				if (!testigo)
				{
					image->figV[i].infoVertices.erase(image->figV[i].infoVertices.begin()
							+ j);
					dec++;
					j--;
				}
			}
		}
		delete vPoly;
		//delete vPolyRes;
	}
	cout << "\nEnding polyline simplification..." << endl;
	*/
	/********************************************/

  //Elimina las objetos que no son figuras
  //NOTA: Si descomento esto, quitar el siguiente
  //if (infoVertices.size() == 0) continue;
  /*
  for (int i=0; i<figV.size(); i++)
  {
    if (figV[i].infoVertices.empty())
    {
      figV.erase(figV.begin()+i);
      borderPtFgV.erase(borderPtFgV.begin()+i);
      i--;
    }
  }
  */


  float colTemp[] = {0,0,0};
  for(unsigned int i=0;i<image->figV.size();i++)
  {
    for(unsigned int j=0;j<image->figV[i].infoVertices.size();j++)
    {
      if (image->figV[i].infoVertices[j].shape == 0)
      {
        colTemp[0] = 0;
        colTemp[2] = 255;
      }
      else
      {
        colTemp[0] = 255;
        colTemp[2] = 0;
      }
      Point2D vert = image->figV[i].infoVertices[j].pt;
      int x = (int) round(vert.x);
      int y = (int) round(vert.y);

      for (int w=-1; w<=1; w++)
        for (int h=-1; h<=1; h++)
          image->imgRes.draw_point(x+w, y+h, colTemp);
		}

  }



  //Bucle donde miro si la figura tiene agujeros o no
  //En figV tengo los vectores finales de los pol�gonos
  for(unsigned int i=0; i<image->figV.size(); i++)
  {
    for (unsigned int j=0; j<image->figV.size(); j++)
    {
      if(i != j)
      {
        if(pointInPolygon(&image->figV[j].infoVertices[0], &(image->figV[i].infoVertices)))
        {//figura con agujero => uno ptos ambas figuras
          image->figV[i].comp = true;
          image->figV[i].ncomponents++;
          image->figV[j].isIntern = true;
          image->figV[i].components.push_back(&image->figV[j]);
          image->figV[j].containers.push_back(&image->figV[i]);
          //for (int k=0; k<borderPtFgV[j].size(); k++)
          //  borderPtFgV[i].push_back(borderPtFg[j][k]);
        }
      }
    }
  }

  //Se calcula el padre de cada figura, si lo tuviera
  for (unsigned int i=0; i<image->figV.size(); i++)
  {
    if (image->figV[i].isIntern)
    {
      image->figV[i].father = image->figV[i].containers[0];
      for (unsigned int j = 1; j<image->figV[i].containers.size(); j++)
        for (unsigned int k = 0; k<(image->figV[i].father)->components.size(); k++)
          if (image->figV[i].father->components[k] == image->figV[i].containers[j])
            image->figV[i].father = image->figV[i].containers[j];
    }
  }

  //Se copia el borde de cada figura desde el vector que los contiene todos
  for (unsigned int j=0; j<image->borderPtFgV.size(); j++)
    image->figV[j].border = image->borderPtFgV[j];

  //Bucle para calcular el color de la figura, y las variables "curves" y "nvertices"
  for(unsigned int i=0; i<image->figV.size(); i++)
  {
    if (image->figV[i].infoVertices.size() == 0) continue;
    //ed_devolver.add(ed.ai2);
    //int col;

    //image->figV[i].setArea();
    image->figV[i].setAreaCentroid();

    Point2D colorPt;
    double centx, centy;

    if (!image->figV[i].comp)
    {//Si la figura no es compuesta tomamos el color del centroide
      colorPt = image->figV[i].centroid;

      //NOTA: Falta mirar que realmente centroide sea un punto de la figura
      //porque podria caer fuera

    }
    else
    {//La figura es compuesta (tiene elementos internos)

      //Miramos si alguno de los elementos coincide con el centroide
      bool elemAtCentroid = false;
      shapePt shCentr(image->figV[i].centroid);
      for (unsigned int j=0; j<image->figV[i].components.size(); j++)
        if (pointInPolygon(&shCentr, &image->figV[i].components[j]->infoVertices))
        {
          elemAtCentroid = true;
          break;
        }

      if (!elemAtCentroid)
        colorPt = image->figV[i].centroid;
      else
      {
        Figure * intFig = image->figV[i].components[0];
        Point2D pi_cont = image->figV[i].infoVertices[0].pt;
        Point2D pi_ag = intFig->infoVertices[0].pt;
        colorPt = pi_ag - pi_cont;
        centx = pi_cont.x + colorPt.x/2;
        centy = pi_cont.y + colorPt.y/2;
        colorPt = Point2D (centx, centy);

        double dist = (pi_ag - pi_cont).modulo();

        //Comprobamos que realmente cogemos los dos puntos m�s cercanos de la figura de entre todos los agujeros
        for(int cont=0; cont<image->figV[i].nvertices; cont++) //para cada punto del contorno
        {
          pi_cont = image->figV[i].infoVertices[cont].pt;
          for(int cont2=0;cont2<intFig->nvertices;cont2++)
          {
            pi_ag = intFig->infoVertices[cont2].pt;
            double newDist = (pi_ag - pi_cont).modulo();
            if (newDist <= dist)
            {
              dist = newDist;
              colorPt = pi_ag - pi_cont;
              centx = pi_cont.x + colorPt.x/2;
              centy = pi_cont.y + colorPt.y/2;
              colorPt = Point2D (centx, centy);
            }
          }
        }
      }
    }

		if (dbg)
		{
    cout<<"Fig "<<i<<" colorPt: "<<colorPt<<endl;
		}

    image->figV[i].RGB[0] = image->img.atXYZV((int)colorPt.getX(), (int)colorPt.getY(), 0, 0); // CImg::at(x,y=0,z=0,v=0)
    image->figV[i].RGB[1] = image->img.atXYZV((int)colorPt.getX(), (int)colorPt.getY(), 0, 1);
    image->figV[i].RGB[2] = image->img.atXYZV((int)colorPt.getX(), (int)colorPt.getY(), 0, 2);

    image->figV[i].RGBf[0] = (float)((int)(((float) image->figV[i].RGB[0]/255.0)*1000))/1000;
    image->figV[i].RGBf[1] = (float)((int)(((float) image->figV[i].RGB[1]/255.0)*1000))/1000;
    image->figV[i].RGBf[2] = (float)((int)(((float) image->figV[i].RGB[2]/255.0)*1000))/1000;

    //Se dibuja el punto donde se ha sacado el color (centroide o intermedio de la recta)
    //int x = (int) round(colorPt.x);
    //int y = (int) round(colorPt.y);
    //for (int w=-5; w<=5; w++)
    //  for (int h=-5; h<=5; h++)
    //    image->imgRes.draw_point(x+w, y+h, image->figV[i].RGB);

    image->figV[i].nvertices = image->figV[i].infoVertices.size();

    //Se calcula el figure.curves = [with,without,only]_curves
    bool someCurve = false;
    bool someStraight = false;
    for (int j=0; j<image->figV[i].nvertices; j++)
    {
      if (image->figV[i].infoVertices[j].shape == 0)
        someStraight = true;
      else
        someCurve = true;
      if (someStraight && someCurve)
      {
        image->figV[i].curves = 1; //With_Curves
        break;
      }
    }
    if (!someStraight)
      image->figV[i].curves = 2; //Only_Curves
    if (!someCurve)
      image->figV[i].curves = 0; //Without_Curves


    //Se calcula los vertices (incluyendo ptos de maxima curvatura)
    //a partir del vector infoVertices
    image->figV[i].info2vertices();

  }


  // Calculo de vecinos a partir de la informacion obtenida en el EdgeDetector (vector felzNeighbours)
  if (image->figV.size() != ed.felzNeighbours.size())
  	cout<<"Error detectado en el calculo de vecinos: no coincide el numero de figuras de figV y felzNeighbours"<<endl;
  else
  {
  	for (int i=0; i < image->figV.size(); i++)
  	{
  		for (int j=0; j<ed.felzNeighbours[i].size(); j++)
  		{
  			int index = ed.felzNeighbours[i][j];
  			image->figV[i].neighbours.push_back(&(image->figV[index]));
  		}
  	}
  }

  cout<<"***** Vecinos *****"<<endl;
  for (int i = 0; i < image->figV.size(); i++)
  {
  	cout<<"Vecinos de "<<image->figV[i].id+1<<": ";
  	for (int j = 0; j < image->figV[i].neighbours.size(); j++)
  	{
  		cout<<image->figV[i].neighbours[j]->id+1<<" ";
  	}
  	cout<<endl;
  }


  cout<<"FiguresExtractor finished"<<endl;

}

vector<Point2D> FiguresExtractor::extractPoints(void)
{
  vector<Point2D>::iterator it;
  vector<ptOr> nghbours;
  vector<ptOr> vecOrd2;
  Point2D pt;
  //int orient;
  ptOr po;
  vector<Point2D> sortedPts;
	sortedPts.clear();

  bool dbg = false;


  //unsigned int k = 0;
  if (!tempV.empty())
		nghbours = getNeighbours(tempV.front());


	unsigned int tVsize = tempV.size();
  while (nghbours.empty() && tVsize>0)
  {
		//it = tempV.begin();
		tempV.erase(tempV.begin());
		tVsize--;
    //pt = tempV.at(k);
    //nghbours = getNeighbours(pt);
		nghbours = getNeighbours(tempV.front());
    //if (dbg) cout<<tempV.at(k)<<" ";
    //k++;
  }
  //k--;

  if (dbg) cout<<endl<<"Nghbours size: "<<nghbours.size()<<endl;
	if (dbg) cout<<"tempV size: "<<tempV.size()<<endl;

  if(!nghbours.empty())
  {
		pt = tempV.front();
    sortedPts.push_back(pt);
		//sortedPts.push_back(tempV.at(k));
    //it = tempV.begin();
    tempV.erase(tempV.begin());
    nghbours = getNeighbours(pt); //Para cuadrar po.index

    po = nghbours.at(0);


  	if (dbg) cout<<"Encontrado punto con vecino"<<endl;

  	bool empty = false;
  	bool foundFig = false;

  	while (!empty || !foundFig)
  	{
    	sortedPts.push_back(po.pt);
			//cout<<"Uno"<<endl;
    	it = tempV.begin()+po.index;
			//cout<<"Dos"<<endl;
    	tempV.erase(it);
			//cout<<"Tres"<<endl;

    	nghbours = getNeighbours(po);
    	int i=0;

    	if (nghbours.size() > 1)
    	{
      	ptOr po1 = nghbours.at(0);
      	ptOr po2 = nghbours.at(1);

      	if (po.orientation == 2)
      	{
        	if (po1.orientation == 5)
          	i = 0;
        	else if (po2.orientation <= 5)
          	i = 1;
      	}
      	else if (po.orientation == 4)
      	{
        	if ((po1.orientation <= 2) || (po1.orientation==4) || (po1.orientation==6) || \
          	(po1.orientation==7))
          	i=0;
        	else if((po2.orientation <= 2) || (po2.orientation==4) || (po2.orientation==6) || \
          	  (po2.orientation==7))
          	i = 1;
      	}
      	else if (po.orientation == 5)
      	{
        	if ((po1.orientation == 2) || (po1.orientation==3) || (po1.orientation==5) || \
          	  (po1.orientation>=7))
          	i=0;
        	else if((po2.orientation == 2) || (po2.orientation==3) || (po2.orientation==5) || \
          	    (po2.orientation>=7))
          	i=1;
      	}
      	else if (po.orientation == 7)
      	{
        	if(po1.orientation >= 4)
          	i=0;
        	else if(po2.orientation >= 4)
          	i=1;
      	}
    	}
    	if (!nghbours.empty())
      	po = nghbours[i];
    	else
    	{
      	empty = true;
      	//no tiene vecinos miramos si hemos encontrado la figura comprobando el tamaño del sortedPts, si es menor q 75 buscamos el siguiente el primer punto que nos ha quedado sin explorar en tempV, para ver si ahí empieza la figura real

      	if((tempV.size()>75) && (sortedPts.size()<75))
      	{
        	pt = tempV.front();
        	sortedPts.clear();
        	sortedPts.push_back(pt);
        	tempV.erase(tempV.begin());
        	nghbours = getNeighbours(pt);
        	if(!nghbours.empty())
        	{
          	empty=false;
          	po = nghbours.at(0);
        	}
      	}
      	else
				{
        	foundFig = true;
				}
    	}
  	}
	}


  if (dbg) cout<<"sortedPts size: "<<sortedPts.size()<<endl;
  if (dbg) cout<<"tempV size: "<<tempV.size()<<endl;

  return sortedPts;
}

vector<ptOr> FiguresExtractor::getNeighbours(Point2D pt)
{
  vector<ptOr> nghb;
  vector<ptInd> temp;
  //vector<Point2D>::iterator it;
  //ptOr po;
  ptInd pi;
  Point2D tempPt1, tempPt2, tempPt3, tempPt4, tempPt5, tempPt6, tempPt7, tempPt8;
  unsigned int i;

	tempPt1 = Point2D(pt.x-1, pt.y-1);
	tempPt2 = Point2D(pt.x, pt.y-1);
	tempPt3 = Point2D(pt.x+1, pt.y-1);
	tempPt4 = Point2D(pt.x-1, pt.y);
	tempPt5 = Point2D(pt.x+1, pt.y);
	tempPt6 = Point2D(pt.x-1, pt.y+1);
	tempPt7 = Point2D(pt.x, pt.y+1);
	tempPt8 = Point2D(pt.x+1, pt.y+1);

  for (i = 0; i < tempV.size(); i++)
  {
  	if (tempV[i] == tempPt1 || tempV[i] == tempPt2 || tempV[i] == tempPt3 || tempV[i] == tempPt4 || tempV[i] == tempPt5 || tempV[i] == tempPt6 || tempV[i] == tempPt7 || tempV[i] == tempPt8)
  	{
  		pi.pt = tempV[i];
  		pi.index = i;
  		temp.push_back(pi);
  	}
  }

  for (i=0; i<temp.size(); i++)
  {
    if(temp[i] == tempPt1) {
      ptOr po = {tempPt1, 1, temp[i].index};
      nghb.push_back(po);
      break;
    }
  }

  for (i=0; i<temp.size(); i++)
  {
    if(temp[i] == tempPt2) {
      ptOr po = {tempPt2, 2, temp[i].index};
      nghb.push_back(po);
      break;
    }
  }

  for (i=0; i<temp.size(); i++)
  {
    if(temp[i] == tempPt3) {
      ptOr po = {tempPt3, 3, temp[i].index};
      nghb.push_back(po);
      break;
    }
  }

  for (i=0; i<temp.size(); i++)
  {
    if(temp[i] == tempPt4) {
      ptOr po = {tempPt4, 4, temp[i].index};
      nghb.push_back(po);
      break;
    }
  }

  for (i=0; i<temp.size(); i++)
  {
    if(temp[i] == tempPt5) {
      ptOr po = {tempPt5, 5, temp[i].index};
      nghb.push_back(po);
      break;
    }
  }

  for (i=0; i<temp.size(); i++)
  {
    if(temp[i] == tempPt6) {
      ptOr po = {tempPt6, 6, temp[i].index};
      nghb.push_back(po);
      break;
    }
  }

  for (i=0; i<temp.size(); i++)
  {
    if(temp[i] == tempPt7) {
      ptOr po = {tempPt7, 7, temp[i].index};
      nghb.push_back(po);
      break;
    }
  }

  for (i=0; i<temp.size(); i++)
  {
    if(temp[i] == tempPt8) {
      ptOr po = {tempPt8, 8, temp[i].index};
      nghb.push_back(po);
      break;
    }
  }

  return nghb;
} // getNeighbours()


vector<ptOr> FiguresExtractor::getNeighbours(ptOr p)
{
//EStablezco prioridades entre los vecinos de modo que si tengo varios elijo en función de la dirección en
//la que he venido
//
  vector<ptOr> nghb;

  ptOr po;
  Point2D tempPt, pt;
  unsigned int i;

  bool found = false;

  pt = p.pt;
  switch(p.orientation)
  {
    case 1:
      //Se elige en primer lugar el vecino 2 porque comparten la coordenada x
      //En su defecto el 4, o el 1, y finalmente cualquiera, siendo el caso normalmente de un
      //vertice
      tempPt = Point2D(pt.x, pt.y-1);
      for (i=0; i<tempV.size(); i++)
      {
        if(tempV[i] == tempPt) {
          ptOr po = {tempPt, 2, i};
          nghb.push_back(po);
          found = true;
          break;
        }
      }
      if(!found)
      {
        tempPt = Point2D(pt.x-1, pt.y);
        for (i=0; i<tempV.size(); i++)
        {
          if(tempV[i] == tempPt) {
          ptOr po = {tempPt, 4, i};
          nghb.push_back(po);
          found = true;
          break;
          }
        }
      }
      if(!found)
      {
        tempPt = Point2D(pt.x-1, pt.y-1);
        for (i=0; i<tempV.size(); i++)
          {
          if(tempV[i] == tempPt) {
            ptOr po = {tempPt, 1, i};
            nghb.push_back(po);
            found = true;
            break;
          }
        }
      }
      if(!found)
      {
        nghb = getNeighbours(pt);
      }
      break;

    case 2:
      nghb = getNeighbours(pt);
      break;

    case 3:
      tempPt = Point2D(pt.x, pt.y-1);
      for (i=0; i<tempV.size(); i++)
      {
        if(tempV[i] == tempPt) {
          ptOr po = {tempPt, 2, i};
          nghb.push_back(po);
          found = true;
          break;
        }
      }
      if(!found)
      {
        tempPt = Point2D(pt.x+1, pt.y);
        for (i=0; i<tempV.size(); i++)
        {
          if(tempV[i] == tempPt) {
            ptOr po = {tempPt, 5, i};
            nghb.push_back(po);
            found = true;
            break;
          }
        }
      }
      if (!found)
      {
        tempPt = Point2D(pt.x+1, pt.y-1);
        for (i=0; i<tempV.size(); i++)
        {
          if(tempV[i] == tempPt) {
          ptOr po = {tempPt, 3, i};
          nghb.push_back(po);
          found = true;
          break;
          }
        }
      }
      if(!found)
      {
        nghb = getNeighbours(pt);
      }
      break;

    case 4:
      nghb = getNeighbours(pt);
      break;

    case 5:
      nghb = getNeighbours(pt);
      break;

    case 6:
      tempPt = Point2D(pt.x, pt.y+1);
      for (i=0; i<tempV.size(); i++)
      {
        if(tempV[i] == tempPt) {
          ptOr po = {tempPt, 7, i};
          nghb.push_back(po);
          found = true;
          break;
        }
      }
      if(!found)
      {
        tempPt = Point2D(pt.x-1, pt.y);
        for (i=0; i<tempV.size(); i++)
        {
          if(tempV[i] == tempPt) {
            ptOr po = {tempPt, 4, i};
            nghb.push_back(po);
            found = true;
            break;
          }
        }
      }
      if (!found)
      {
        tempPt = Point2D(pt.x-1, pt.y+1);
        for (i=0; i<tempV.size(); i++)
        {
          if(tempV[i] == tempPt) {
          ptOr po = {tempPt, 6, i};
          nghb.push_back(po);
          found = true;
          break;
          }
        }
      }
      if(!found)
      {
        nghb = getNeighbours(pt);
      }
      break;

    case 7:
      nghb = getNeighbours(pt);
      break;

    case 8:
      tempPt = Point2D(pt.x, pt.y+1);
      for (i=0; i<tempV.size(); i++)
      {
        if(tempV[i] == tempPt) {
          ptOr po = {tempPt, 7, i};
          nghb.push_back(po);
          found = true;
          break;
        }
      }
      if(!found)
      {
        tempPt = Point2D(pt.x+1, pt.y);
        for (i=0; i<tempV.size(); i++)
        {
          if(tempV[i] == tempPt) {
            ptOr po = {tempPt, 5, i};
            nghb.push_back(po);
            found = true;
            break;
          }
        }
      }
      if (!found)
      {
        tempPt = Point2D(pt.x+1, pt.y+1);
        for (i=0; i<tempV.size(); i++)
        {
          if(tempV[i] == tempPt) {
          ptOr po = {tempPt, 8, i};
          nghb.push_back(po);
          found = true;
          break;
          }
        }
      }
      if(!found)
      {
        nghb = getNeighbours(pt);
      }
      break;
  };

  return nghb;
}//getNeighbours()

int FiguresExtractor::findClosedBorder(vector<vector<Point2D> > * completed, int prvInd, ptInd pi, vector<Point2D> rest, Point2D initialPt)
{
	//vector<Point2D> completed;
	int myInd;
	Point2D tempPt, tempPt1, tempPt2, tempPt3, tempPt4, tempPt5, tempPt6, tempPt7, tempPt8;
	vector<ptInd> nghb;

	tempPt = pi.pt;
	completed->push_back(vector<Point2D> (1, tempPt));
	if (prvInd == 0) //Primera ejecución
		rest.erase(rest.begin() + pi.index);
	myInd = completed->size() - 1;

	while(true)
	{
		// Buscamos vecinos
		tempPt1 = Point2D(tempPt.x+1, tempPt.y);
		tempPt2 = Point2D(tempPt.x+1, tempPt.y+1);
		tempPt3 = Point2D(tempPt.x+1, tempPt.y-1);
		tempPt4 = Point2D(tempPt.x, tempPt.y+1);
		tempPt5 = Point2D(tempPt.x, tempPt.y-1);
		tempPt6 = Point2D(tempPt.x-1, tempPt.y+1);
		tempPt7 = Point2D(tempPt.x-1, tempPt.y);
		tempPt8 = Point2D(tempPt.x-1, tempPt.y-1);
		nghb.clear();
		int sz = rest.size();
		for (int j = 0; j < sz; j++)
		{
			if (rest[j] == tempPt1 || rest[j] == tempPt2 || rest[j] == tempPt3 || rest[j] == tempPt4 || rest[j] == tempPt5 || rest[j] == tempPt6 || rest[j] == tempPt7 || rest[j] == tempPt8)
			{
				pi.pt = rest[j];
				pi.index = j;
				nghb.push_back(pi);
				rest.erase(rest.begin() + j);
				sz--;
				j--;
			}
		}
		if (nghb.size() == 0)
		{
			//cout<<"Fin del camino: "<<DISTANCE(tempPt.x, tempPt.y, initialPt.x, initialPt.y)<<endl;

			if (DISTANCE(tempPt.x, tempPt.y, initialPt.x, initialPt.y) < 5)
			{
				//cout<<"Camino encontrado: "<<myInd<<endl;
				return myInd;
			}
			else
			{
				(*completed)[myInd].clear();
				return -1;
			}
		}
		else if (nghb.size() == 1)
		{
			//cout<<"Un vecino encontrado"<<endl;
			tempPt = nghb[0].pt;
			(*completed)[myInd].push_back(tempPt);
			//rest.erase(rest.begin() + nghb[0].index);
		}
		else if (nghb.size() > 1)
		{
			int index = -1, tempSize = 0, indexResult = -1;
			//for (int k = 0; k < nghb.size(); k++)
				//rest.erase(rest.begin() + nghb[k].index);
			for (int k = 0; k < nghb.size(); k++)
			{
				index = findClosedBorder(completed, myInd, nghb[k], rest, initialPt); //Deulve el indice de "results" donde se encuentra el borde más largo
				if (index != -1)
				{ // Se busca el maximo de los valores devueltos
					//cout<<"Me han devuelto un camino encontrado "<<index<<" "<<(*completed)[index].size()<<" "<<tempSize<<endl;
					if ((*completed)[index].size() > tempSize)
					{
						//cout<<"mayor tempsize"<<endl;
						tempSize = (*completed)[index].size();
						indexResult = index;
					}
				}
			}
			if (indexResult == -1)
			{
				//(*completed)[myInd].push_back(tempPt);
				(*completed)[myInd].clear();
				return -1;
			}
			else
			{
				for (int i = 0; i < tempSize; i++)
					(*completed)[myInd].push_back((*completed)[indexResult][i]);

				(*completed)[indexResult].clear();
				return myInd;
			}
		}
	}
}

void FiguresExtractor::arrangeBordersBT(vector<vector<Point2D> > *v)
{
	vector<vector<Point2D> > results;
	vector<Point2D> tV;
	vector<ptInd> nghb;
	ptInd pi;
	int maxIni;
  Point2D tempPt, tempPt1, tempPt2, tempPt3, tempPt4, tempPt5, tempPt6, tempPt7, tempPt8;
  bool found;


	for (int i = 0; i < v->size(); i++)
	{
		cout<<"Figura "<<i<<endl;
		tV = (*v)[i];
		tempPt = tV[0];
		tV.erase(tV.begin());
		//image->borderPtFgV.push_back(vector<Point2D> (1, tempPt));

		results.push_back(vector<Point2D> (1, tempPt));
		maxIni = 2;
		// Buscamos vecinos
		for (int iter = 0; iter < maxIni; iter++)
		{
			tempPt1 = Point2D(tempPt.x + 1, tempPt.y);
			tempPt2 = Point2D(tempPt.x + 1, tempPt.y + 1);
			tempPt3 = Point2D(tempPt.x + 1, tempPt.y - 1);
			tempPt4 = Point2D(tempPt.x, tempPt.y + 1);
			tempPt5 = Point2D(tempPt.x, tempPt.y - 1);
			tempPt6 = Point2D(tempPt.x - 1, tempPt.y + 1);
			tempPt7 = Point2D(tempPt.x - 1, tempPt.y);
			tempPt8 = Point2D(tempPt.x - 1, tempPt.y - 1);
			nghb.clear();
			for (int j = 0; j < tV.size(); j++)
			{
				if (tV[j] == tempPt1 || tV[j] == tempPt2 || tV[j] == tempPt3 || tV[j]
						== tempPt4 || tV[j] == tempPt5 || tV[j] == tempPt6 || tV[j]
						== tempPt7 || tV[j] == tempPt8)
				{
					pi.pt = tV[j];
					pi.index = j;
					nghb.push_back(pi);
				}
			}
			if (!nghb.empty())
			{
				found = false;
				for (int j = 0; j < nghb.size(); j++)
				{
					if (nghb[j] == tempPt1)
					{
						tempPt = nghb[j].pt;
						tV.erase(tV.begin() + nghb[j].index);
						results[0].push_back(tempPt);
						found = true;
						break;
					}
				}
				if (!found)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt2)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin() + nghb[j].index);
							results[0].push_back(tempPt);
							found = true;
							break;
						}
					}
				}
				if (!found)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt3)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin() + nghb[j].index);
							results[0].push_back(tempPt);
							found = true;
							break;
						}
					}
				}
				if (!found)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt4)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin() + nghb[j].index);
							results[0].push_back(tempPt);
							found = true;
							break;
						}
					}
				}
				if (!found)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt5)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin() + nghb[j].index);
							results[0].push_back(tempPt);
							found = true;
							break;
						}
					}
				}
				if (!found)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt6)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin() + nghb[j].index);
							results[0].push_back(tempPt);
							found = true;
							break;
						}
					}
				}
				if (!found)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt7)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin() + nghb[j].index);
							results[0].push_back(tempPt);
							found = true;
							break;
						}
					}
				}
				if (!found)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt8)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin() + nghb[j].index);
							results[0].push_back(tempPt);
							found = true;
							break;
						}
					}
				}
			}
		}

		tempPt1 = Point2D(tempPt.x + 1, tempPt.y);
		tempPt2 = Point2D(tempPt.x + 1, tempPt.y + 1);
		tempPt3 = Point2D(tempPt.x + 1, tempPt.y - 1);
		tempPt4 = Point2D(tempPt.x, tempPt.y + 1);
		tempPt5 = Point2D(tempPt.x, tempPt.y - 1);
		tempPt6 = Point2D(tempPt.x - 1, tempPt.y + 1);
		tempPt7 = Point2D(tempPt.x - 1, tempPt.y);
		tempPt8 = Point2D(tempPt.x - 1, tempPt.y - 1);
		nghb.clear();
		for (int j = 0; j < tV.size(); j++)
		{
			if (tV[j] == tempPt1 || tV[j] == tempPt2 || tV[j] == tempPt3 || tV[j]
					== tempPt4 || tV[j] == tempPt5 || tV[j] == tempPt6 || tV[j]
					== tempPt7 || tV[j] == tempPt8)
			{
				pi.pt = tV[j];
				pi.index = j;
				nghb.push_back(pi);
			}
		}

		int index = -1, tempSize = 0, indexResult = -1;
		//for (int k = 0; k < nghb.size(); k++)
			//rest.erase(rest.begin() + nghb[k].index);
		for (int k = 0; k < nghb.size(); k++)
		{
			index = findClosedBorder(&results, 0, nghb[k], tV, results[0][0]); //Deulve el indice de "results" donde se encuentra el borde más largo
			if (index != -1)
			{ // Se busca el maximo de los valores devueltos
				//cout<<"Me han devuelto un camino encontrado "<<index<<" "<<(*completed)[index].size()<<" "<<tempSize<<endl;
				if (results[index].size() > tempSize)
				{
					//cout<<"mayor tempsize"<<endl;
					tempSize = results[index].size();
					indexResult = index;
				}
			}
		}


		cout<<"************************************************"<<endl;
		cout<<"findClosedBorder terminado con ind: "<<indexResult<<endl;
		cout<<"************************************************"<<endl<<endl;

		if (indexResult != -1 && tempSize > 0)
		{
			image->borderPtFgV.push_back(vector<Point2D> (1, results[indexResult][0]));
			int indFig = image->borderPtFgV.size() - 1;
			for (int j = 1; j < results[indexResult].size(); j++)
				image->borderPtFgV[indFig].push_back(results[indexResult][j]);
		} // else: No se añade nada al vector de borde

		for (int j = 0; j < results.size(); j++)
			results[j].clear();
		results.clear();
	}
}

void FiguresExtractor::arrangeBorders(vector<vector<Point2D> > *v)
{
	vector<Point2D> tV, temp;
	vector<ptInd> nghb;
	ptInd pi;
  Point2D tempPt, tempPt1, tempPt2, tempPt3, tempPt4, tempPt5, tempPt6, tempPt7, tempPt8;
  bool finish, found1, found2, backup;


	for (int i = 0; i < v->size(); i++)
	{
		tV = (*v)[i];
		tempPt = tV[0];
		tV.erase(tV.begin());
		image->borderPtFgV.push_back(vector<Point2D> (1, tempPt));
		finish = false;
		backup = false;

		while (!finish)
		{
			tempPt1 = Point2D(tempPt.x+1, tempPt.y);
			tempPt2 = Point2D(tempPt.x+1, tempPt.y+1);
			tempPt3 = Point2D(tempPt.x+1, tempPt.y-1);
			tempPt4 = Point2D(tempPt.x, tempPt.y+1);
			tempPt5 = Point2D(tempPt.x, tempPt.y-1);
			tempPt6 = Point2D(tempPt.x-1, tempPt.y+1);
			tempPt7 = Point2D(tempPt.x-1, tempPt.y);
			tempPt8 = Point2D(tempPt.x-1, tempPt.y-1);
			nghb.clear();
			found1 = false;

			for (int j = 0; j < tV.size(); j++)
			{
				if (tV[j] == tempPt1 || tV[j] == tempPt2 || tV[j] == tempPt3 || tV[j] == tempPt4 || tV[j] == tempPt5 || tV[j] == tempPt6 || tV[j] == tempPt7 || tV[j] == tempPt8)
				{
					pi.pt = tV[j];
					pi.index = j;
					nghb.push_back(pi);
					found1 = true;
				}
			}

			if (found1)
			{
				found2 = false;
				for (int j = 0; j < nghb.size(); j++)
				{
					if (nghb[j] == tempPt1)
					{
						tempPt = nghb[j].pt;
						tV.erase(tV.begin()+nghb[j].index);
						image->borderPtFgV[i].push_back(tempPt);
						found2 = true;
						break;
					}
				}
				if (!found2)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt2)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin()+nghb[j].index);
							image->borderPtFgV[i].push_back(tempPt);
							found2 = true;
							break;
						}
					}
				}
				if (!found2)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt3)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin()+nghb[j].index);
							image->borderPtFgV[i].push_back(tempPt);
							found2 = true;
							break;
						}
					}
				}
				if (!found2)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt4)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin()+nghb[j].index);
							image->borderPtFgV[i].push_back(tempPt);
							found2 = true;
							break;
						}
					}
				}
				if (!found2)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt5)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin()+nghb[j].index);
							image->borderPtFgV[i].push_back(tempPt);
							found2 = true;
							break;
						}
					}
				}
				if (!found2)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt6)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin()+nghb[j].index);
							image->borderPtFgV[i].push_back(tempPt);
							found2 = true;
							break;
						}
					}
				}
				if (!found2)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt7)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin()+nghb[j].index);
							image->borderPtFgV[i].push_back(tempPt);
							found2 = true;
							break;
						}
					}
				}
				if (!found2)
				{
					for (int j = 0; j < nghb.size(); j++)
					{
						if (nghb[j] == tempPt8)
						{
							tempPt = nghb[j].pt;
							tV.erase(tV.begin()+nghb[j].index);
							image->borderPtFgV[i].push_back(tempPt);
							found2 = true;
							break;
						}
					}
				}
			}
			else if (!found1 || tV.empty())
			{
				if (tV.size() > image->borderPtFgV[i].size() && tV.size() > temp.size()) //Nos quedamos con el borde conectado más grande
				{
					if (image->borderPtFgV[i].size() > temp.size())
						temp = image->borderPtFgV[i]; //Almacenamos a modo de backup el borde más grance encontrado hasta el momento
					image->borderPtFgV[i].clear();
					image->borderPtFgV[i].push_back(tV[0]);
					tempPt = tV[0];
					tV.erase(tV.begin());
				}
				else
				{
					if (temp.size() > image->borderPtFgV[i].size())
						image->borderPtFgV[i] = temp;
					finish = true;
					temp.clear();
					cout<<"Tamaño del tV restante: "<<tV.size()<<endl;
				}
			}
		}
	}
}

vector<int> FiguresExtractor::findVertices(vector<Point2D> iv)
{
  int longi = iv.size();
  vector<Point2D> vertices;
  vector<int> indices;

  double pte1, pte2, pte_ini=0;
  Point2D p1, p2, p3;
  int i = 10;
  bool cte = true;
  int cc = 4;

  //Se comprueba en 30 ptos si su pte se mantiene cte respecto al primer pto escogido:
  //cte -> recta
  //NO cte (crece o decrece) -> curva

  //Se comprueba si el pto 0 es realmente un vértice o no
  int i2=0;
  pte1=0;
  bool eq=false;
  bool pte_cte=true;
  bool inc=false;
  int ll = (int) longi/5;
  ll *= 5;
  int a = 10;
  p1 = iv[ll-20];
  p2 = iv[ll-15];
  if(p2.x - p1.x == 0)
    eq=true;
  else
    pte1=(p2.y-p1.y)/(p2.x-p1.x);
  while(a>=0 && pte_cte)
  {
    p1 = p2;
    p2= iv[ll-a-1];
    if((p2.x - p1.y)!=0)
    {
      pte2=(p2.y-p1.y)/(p2.x-p1.x);
      if(fabs(pte1-pte2)>0.24)
      {
        pte_cte=false;
        if(pte2>=pte1)
          inc=true;
      }
    }
    a-=5;
  }
  a=5;
  while(a<=20 && pte_cte)
  {
    p1=p2;
    p2= iv[a];
    if(p2.x-p1.x!=0)
    {
      pte2=(p2.y-p1.y)/(p2.x-p1.x);
      if(fabs(pte1-pte2)>0.24)
      {
        pte_cte=false;
        if(pte2>=pte1)
          inc=true;
      }
    }
    a=(a+5)%iv.size();
  }
  if(!pte_cte)
  {
    p1 = iv[0];
    vertices.push_back(p1);
    indices.push_back(0);
    i = 10;
  }
  else
  {
    a=25;
    cout<<vertices.size()<<endl;
    while(pte_cte)
    {
      //cout<<a<<endl;
      p1 = p2;
      p2 = iv[a];
      if(p2.x - p1.x != 0)
      {
        pte2=(p2.y-p1.y)/(p2.x-p1.x);
        if(fabs(pte1-pte2)>0.3)
        {
          pte_cte = false;
          if(pte2>=pte1)
            inc = true;
        }
        pte1 = pte2;
      }
      a = (a+5) % iv.size();
    }
    vertices.push_back(p1);
    indices.push_back(a-5);
    if((a%10) == 0)
      i=a;
    else
      i=a+5;
  }

  while(i<longi-10)
  {
    p1= iv[i-10];
    p2= iv[i-5];
    if(p2.x-p1.x==0)
      eq = true;
    else
    {
      pte1 = (p2.y-p1.y)/(p2.x-p1.x);
      eq=false;
    }
    cc=i;
    if(i+15>longi-10)
      i2 = i + 10;
    else
      i2 = i + 15;
    cte = true;
    inc = false;
    while((cc<=i2) && cte)
    {
      p1 = p2;
      p2 = iv[cc];
      if(!eq)
      {
        if(p2.x-p1.x!=0)
        {
          pte2 = (p2.y-p1.y)/(p2.x-p1.x);
          if(fabs(pte1-pte2)>0.4)
            cte=false;
        }
        else
          eq=true;
      }
      else
        if(p2.x-p1.x!=0)
          eq = false;
      cc = cc + 5;
    }//fin while 30 ptos ss

    if(eq || cte)
    {
      if(eq)
      {
        bool is_vert = false;
        double difX, difX2=0;
        p1 = iv[i];
        p2 = iv[i+10];
        difX = fabs(p2.x-p1.x);
        i=i+20;
        while((i<longi-10) && !is_vert)
        {
          p1 = p2;
          p2 = iv[i];
          difX2 = p2.x - p1.x;
          if(fabs(difX-difX2)>1)
          {
            is_vert = true;
            vertices.push_back(p1);
            indices.push_back(0);
            indices.push_back(i-10);
          }
          i=i+10;
        }
      }
      else{
        p1 = iv[i];
        bool is_vert = false;
        pte_ini = pte1;
        bool x_ig = false;
        int w_xig = 0;
        while((i<longi-10) && !is_vert)
        {
          p2 = iv[i+10];
          if(p2.x-p1.x==0)
          {
            x_ig=true;
            w_xig++;
            p1=p2;
          }
          else
          {
            x_ig=false;
            pte2=(p2.y-p1.y)/(p2.x-p1.x);
            if(fabs(pte1-pte2)>0.5)
            {
              vertices.push_back(p1);
              indices.push_back(0);
              indices.push_back(i);
              is_vert = true;
            }
            p1 = p2;
            pte1 = pte2;
          }
          if(x_ig && (w_xig >= 2))
          {
            vertices.push_back(p1);
            indices.push_back(0);
            indices.push_back(i);
            is_vert = true;
          }
          i=i+10;
        }
      }
    }
    else
    {
      p1 = iv[i];
      bool is_vert = false;
      Point2D p_temp;
      while((i<longi-10) && !is_vert)
      {
        p2 = iv[i+10];
        if(p2.x-p1.x==0)
        {
          pte2 = pte1;
        }
        else
          pte2 = (p2.y-p1.y)/(p2.x-p1.x);
        if((pte1>=0 && pte2<0) || (pte1<0 && pte2>=0))
        {
            vertices.push_back(p1);
            indices.push_back(1); //Shape: curve
            indices.push_back(i);
            is_vert=true;
        }
        i=i+10;
        p1=p2;
        pte1=pte2;
      }
    }
  }
  if(cte)
    indices.push_back(0); //Shape: straight
  else
    indices.push_back(1); //Shape: curve

  return indices;
}

vector<int> FiguresExtractor::findVerticesAlt(vector<Point2D> iv)
{
  vector<int> indices;



  return indices;
}

vector<ptInd> FiguresExtractor::improveVertices(vector<Point2D> vec_ordXY, vector<int> indices)
{
  int ind1 = 0;
  int long_vo = vec_ordXY.size();
  Point2D pto1, pto2;
  double difX, difY = 0;
  double difX2, difY2 = 0;
  vector<Point2D> vec_pos;
  vector<ptInd> vert_final;

  for (unsigned int k=0; k<indices.size(); k+=2)
  {
    ind1 = indices[k];
    bool is_vert = false;
    bool incX = false;
    bool incY = false;
    bool eqX = false;
    bool eqY = false;
    int con = 0;
    int con2 = 0;
    int con3 = 0;
    int con4 = 0;
    int con_enterX = 0;
    int con_enterY = 0;
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int ptos_max = 0;
    int l;
    double Y = 0;
    double X = 0;
    double dif;
    int pos = 0;
    int con_incX = 0;
    int con_decreX = 0;
    Point2D pv, p_temp, p_temp2, pto1, pto2;
    ptInd pti;
    int con_incY = 0;
    int con_decreY = 0;

    if(indices[k+1] == 0) //Si == curva
      ptos_max = 10;
    else
      ptos_max = 6;

    if(ind1<20)
    {
      pto1 =  vec_ordXY[long_vo-20-ind1];
      pto2 =  vec_ordXY[long_vo-19-ind1];
      difX = pto2.x-pto1.x;
      difY = pto2.y-pto1.y;

      if(difX>0)
        incX=true;
      else
        if(difX==0)
          eqX=true;
      if(difY>0)
        incY=true;
      else
        if(difY==0)
          eqY=true;
      l = long_vo-18-ind1;

      while((l<long_vo) && !is_vert)
      {
        pto1=pto2;
        pto2 = vec_ordXY[l];
        difX2 = pto2.x-pto1.x;
        difY2 = pto2.y-pto1.y;
        if(eqX)
        {
          if((difX2>0)&& con<8)
          {
            incX=true;
            eqX=false;
          }
          else if((difX2<0) && con<8)
            eqX=false;
          else if(con>=8 && difX2!=0)//!(difX2<=1 && difX2>=-1))
          {
            if(con_enterX==0)
              X=pto1.y;
            con_enterX++;
            dif=fabs(X-pto2.x);
            if(dif>1)
            {
              is_vert=true;
              pv=pto2;
              pos=l;
            }
          }
          if (difX2==0)//(difX2<=1 && difX2>=-1)
            con++;
        }
        else
        {
          if (difX2==0 && (con_incX<6 || con_decreX<6) && con3>10)
          {
            eqX=true;
          }
          if(difX2==0)//(difX2<=1 && difX2>=-1)
          {
            con3++;
            if(con3==1)
            {
              p_temp=pto1;
              pos=l-1;
            }
          }
          else
          {
            con3=0;
            if (difX2>0 && incX)
              con_incX++;
            else if (difX2<0 && !incX)
              con_decreX++;
          }
          if (con3>=ptos_max)
          {
            is_vert=true;
            pv=p_temp;
          }
          if((difX2>0) && !incX)
          {
            if(counter==0)
            {
              p_temp2=pto1;
              pos=l-1;
            }
            counter++;
          }
          if((difX2>0) && !incX && counter>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difX2<0) && !incX)
            counter=0;
          if((difX2<0) && incX)
          {
            if(counter2==0)
            {
              p_temp2=pto1;
              pos=l-1;
            }
            counter2++;
          }
          if(difX2<0 && incX && counter2>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difX2>0) && incX)
            counter2=0;
        }
        if(eqY)
        {
          if((difY2>0)&& con2<8)
          {
            incY=true;
            eqY=false;
          }
          else if((difY2<0) && con2<8)
            eqY=false;
          else if(con2>=8 && difY2!=0)//!((difY2>=-1) && (difY2<=1)))
          {
            if(con_enterY==0)
              Y=pto1.y;
            con_enterY++;
            dif=fabs(Y-pto2.y);
            if(dif>1)
            {
              is_vert=true;
              pv=pto2;
              pos=l;
            }
          }
          if(difY2!=0)//(difY2>=-1) && (difY2<=1))
            con2++;
        }
        else
        {
          if((difY2==0) && (con_incY<6 || con_decreY<6) && con4>10)
          {
            eqY=true;
          }
          if(difY2==0)
          {
            con4++;
            if(con4==1)
            {
              p_temp=pto1;
              pos=l;
            }
          }
          else
          {
            con4=0;
            if (difY2>0 && incY)
              con_incY++;
            else if (difY2<0 && !incY)
              con_decreY++;
          }
          if (con4>=8)
          {
            is_vert=true;
            pv=p_temp;
          }
          if((difY2>0) && !incY)
          {
            if(counter3==0)
            {
              p_temp2=pto1;
              pos=l-1;
            }
            counter3++;
          }
          if((difY2>0) && !incY && counter3>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difY2<0) && !incY)
            counter3=0;
          if((difY2<0) && incY)
          {
            if(counter4==0)
            {
              p_temp2=pto1;
              pos=l-1;
            }
            counter4++;
          }
          if(difY2<0 && incY && counter4>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difY2>0) && incY)
            counter4=0;
        }
        difX=difX2;
        difY=difY2;
        l++;
      }
      l=0;
      while((l<20-ind1) && !is_vert)
      {
        pto1=pto2;
        pto2 =  vec_ordXY[l];
        difX2 = pto2.x-pto1.x;
        difY2 = pto2.y-pto1.y;
        if(eqX)
        {
          if((difX2>0)&& con<8)
          {
            incX=true;
            eqX=false;
          }
          else if((difX2<0) && con<8)
              eqX=false;
          else if(con>=8 && difX2==0)//!(difX2<=1 && difX2>=-1))
          {
            if(con_enterX==0)
              X=pto1.x;
            con_enterX++;
            dif=fabs(X-pto2.x);
            if(dif>1)
            {
              is_vert=true;
              pv=pto2;
              pos=l;
            }
          }
          if(difX2==0)//(difX2<=1 && difX2>=-1)
            con++;
        }
        else
        {
          if (difX2==0 && (con_incX<6 || con_decreX<6) && con3>10)
          {
            eqX=true;
          }
          if(difX2==0)//(difX2<=1 && difX2>=-1)
          {
            con3++;
            if(con3==1)
            {
              p_temp= pto1;
              pos=l;
            }
          }
          else
          {
            con3=0;
            if (difX2>0 && incX)
              con_incX++;
            else if (difX2<0 && !incX)
              con_decreX++;
          }
          if (con3>=ptos_max)
          {
            is_vert=true;
            pv=p_temp;
          }
          if((difX2>0) && !incX)
          {
            if(counter==0)
            {
              p_temp2=pto1;
              pos=l;
            }
            counter++;
          }
          if((difX2>0) && !incX && counter>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difX2<0) && !incX)
            counter=0;
          if((difX2<0) && incX)
          {
            if(counter2==0)
            {
              p_temp2=pto1;
              pos=l;
            }
            counter2++;
          }
          if(difX2<0 && incX && counter2>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difX2>0) && incX)
            counter2=0;
        }
        if(eqY)
        {
          if((difY2>0)&& con2<8)
          {
            incY=true;
            eqY=false;
          }
          else if((difY2<0) && con2<8)
            eqY=false;
          else if(con2>=8 && (difY2!=0))
          {
            if(con_enterY==0)
              Y=pto1.y;
            con_enterY++;
            dif=fabs(Y-pto2.y);
            if(dif>1)
            {
              is_vert=true;
              pv=pto2;
              pos=l;
            }
          }
          if(difY2==0)//((difY2>=-1) && (difY2<=1))
            con2++;
        }
        else
        {
          if((difY2==0) && (con_incY<6 || con_decreY<6) && con4>10)
          {
            eqY=true;
          }
          if(difY2==0)
          {
            con4++;
            if(con4==1)
            {
              p_temp= pto1;
              pos=l;
            }
          }
          else
          {
            con4=0;
            if (difY2>0 && incY)
              con_incY++;
            else if (difY2<0 && !incY)
              con_decreY++;
          }
          if (con4>=8)
          {
            is_vert=true;
            pv=p_temp;
          }
          if((difY2>0) && !incY)
          {
            if(counter3==0)
            {
              p_temp2=pto1;
              pos=l;
            }
            counter3++;
          }
          if((difY2>0) && !incY && counter3>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difY2<0) && !incY)
            counter3=0;
          if((difY2<0) && incY)
          {
            if(counter4==0)
            {
              p_temp2=pto1;
              pos=l;
            }
            counter4++;
          }
          if(difY2<0 && incY && counter4>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difY2>0) && incY)
            counter4=0;
        }
        difX=difX2;
        difY=difY2;
        l++;
      }
      if(is_vert)
      {
        pti.pt = pv;
        pos = -1;
        for (unsigned int k = long_vo-20-ind1; k< vec_ordXY.size(); k++)
        {
          if (vec_ordXY[k] == pv)
          {
            pos = k;
            break;
          }
        }
        if(pos==-1)
        {
          for (unsigned int k = 0; k< vec_ordXY.size(); k++)
          {
            if (vec_ordXY[k] == pv)
            {
              pos = k;
              break;
            }
          }
        }
        pti.index = pos;
        vert_final.push_back(pti);
      }
    }
    else
    {//ind1>0
      pto1 =  vec_ordXY[ind1-19];
      pto2 =  vec_ordXY[ind1-18];
      difX = pto2.x-pto1.x;
      difY = pto2.y-pto1.y;
      if(difX>0)
        incX=true;
      else if(difX==0)
        eqX=true;
      if(difY>0)
        incY=true;
      else if(difY==0)
        eqY=true;
      l=ind1-17;
      while(l<long_vo && (l<ind1+20) && !is_vert)
      {
        pto1=pto2;
        pto2 = vec_ordXY[l];
        difX2 = pto2.x-pto1.x;
        difY2 = pto2.y-pto1.y;
        if(eqX)
        {
          if((difX2>0)&& con<8)
          {
            incX=true;
            eqX=false;
          }
          else if((difX2<0) && con<8)
            eqX=false;
          else if(con>=8 && difX2!=0)
          {
            if(con_enterX==0)
            {
              X=pto1.x;
            }
            con_enterX++;
            dif=fabs(X-pto2.x);
            if(dif>1)
            {
              is_vert=true;
              pv=pto2;
              pos=l;
            }
          }
          if(difX2==0)
            con++;
        }
        else
        {
          if (difX2==0 && (con_incX<6 || con_decreX<6) && con3>10)
          {
            eqX=true;
          }
          if(difX2==0)
          {
            con3++;
            if(con3==1)
            {
              p_temp=pto1;
              pos=l-1;
            }
          }
          else
          {
            con3=0;
            if (difX2>0 && incX)
              con_incX++;
            else if (difX2<0 && !incX)
              con_decreX++;
          }
          if (con3>=ptos_max)
          {
            is_vert=true;
            pv=p_temp;
          }
          if((difX2>0) && !incX)
          {
            if(counter==0)
            {
              p_temp2=pto1;
              pos=l-1;
            }
            counter++;
          }
          if((difX2>0) && !incX && counter>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difX2<0) && !incX)
            counter=0;
          if((difX2<0) && incX)
          {
            if(counter2==0)
            {
              p_temp2=pto1;
              pos=l-1;
            }
            counter2++;
          }
          if(difX2<0 && incX && counter2>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difX2>0) && incX)
            counter2=0;
        }
        if(eqY)
        {
          if((difY2>0)&& con2<8)
          {
            incY=true;
            eqY=false;
          }
          else if((difY2<0) && con2<8)
            eqY=false;
          else if(con2>=8 && (difY2!=0))
          {
            if (con_enterY==0)
            {
              Y=pto1.y;
            }
            con_enterY++;
            dif=fabs(Y-pto2.y);
            if (dif>1)
            {
              pos=l;
              is_vert=true;
              pv=pto2;
            }
          }
          if(difY2==0)
          {
            con2++;
          }
        }
        else
        {
          if((difY2==0) && (con_incY<6 || con_decreY<6) && con4>10)
          {
            eqY=true;
          }
          if (difY2==0)
          {
            con4++;
            if(con4==1)
            {
              p_temp= pto1;
              pos=l-1;
            }
          }
          else
          {
            con4=0;
            if (difY2>0 && incY)
              con_incY++;
            else if (difY2<0 && !incY)
              con_decreY++;
          }
          if (con4>=8)
          {
            is_vert=true;
            pv=p_temp;
          }
          if((difY2>0) && !incY)
          {
            if(counter3==0)
            {
              p_temp2=pto1;
              pos=l-1;
            }
            counter3++;
          }
          if((difY2>0) && !incY && counter3>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difY2<0) && !incY)
            counter3=0;
          if((difY2<0) && incY)
          {
            if(counter4==0)
            {
              p_temp2=pto1;
              pos=l-1;
            }
            counter4++;
          }
          if(difY2<0 && incY && counter4>1)
          {
            is_vert=true;
            pv=p_temp2;
          }
          if((difY2>0) && incY)
            counter4=0;
        }
        difX=difX2;
        difY=difY2;
        l++;
      }
      if(is_vert)
      {
        pti.pt = pv;
        pos = -1;
        for (unsigned int k = ind1-20; k< vec_ordXY.size(); k++)
        {
          if (vec_ordXY[k] == pv)
          {
            pos = k;
            break;
          }
        }
        if(pos==-1)
        {
          for (unsigned int k = 0; k< vec_ordXY.size(); k++)
          {
            if (vec_ordXY[k] == pv)
            {
              pos = k;
              break;
            }
          }
        }
        pti.index = pos;
        vert_final.push_back(pti);
      }
    }
  }

  return vert_final;
}//fin improveVertices

vector<shapePt> FiguresExtractor::findSegments(vector<ptInd> vert_final, vector<Point2D> vec_ordXY)
{
  vector<shapePt> vert_final2;
  shapePt sptTemp;
  Point2D p1, p2, middleP, p2p1, pcp1, pCen, pBfCen, pAfCen, pacp1, pdcp1;
  double dist, dist2, dist3;
  int pos1, pos2, posCen, posAfCen, posBfCen;

  for(unsigned int a=0; a<vert_final.size()-1;a++)
  {
    p1 = vert_final[a].pt;
    p2 = vert_final[a+1].pt;
    middleP.x = (p1.x+p2.x)/2;
    middleP.y = (p1.y+p2.y)/2;

    pos1 = vert_final[a].index;
    pos2 = vert_final[a+1].index;
    posCen = (int) round((pos2-pos1)/2)+pos1;

    pCen =  vec_ordXY[posCen];
    posAfCen=0;
    posBfCen =0;
    posAfCen= (int) round((posCen-pos1)/4) + pos1;
    posBfCen = pos2 - (int) round((pos2-posCen)/4);
    pAfCen =  vec_ordXY[posAfCen];
    pBfCen = vec_ordXY[posBfCen];
    p2p1 = p2 - p1;
    pcp1 = pCen - p1;
    dist = (p2p1.moduloProductoVectorial(pcp1))/p2p1.modulo();

    pacp1= pAfCen - p1;
    dist2 = (p2p1.moduloProductoVectorial(pacp1))/p2p1.modulo();

    pdcp1= pBfCen - p1;
    dist3 = (p2p1.moduloProductoVectorial(pdcp1))/p2p1.modulo();

    if (dist2>=dist || dist3>=dist)
    {
      sptTemp.pt = p1;
      sptTemp.shape = 0; //Straight
      vert_final2.push_back(sptTemp);
    }
    else
    {
      if (fabs(dist2-dist)<0.5 || fabs(dist3-dist)<0.5)
      {
	      sptTemp.pt = p1;
      	sptTemp.shape = 0; //Straight
        vert_final2.push_back(sptTemp);
      }
      else
      {
      	sptTemp.pt = p1;
      	sptTemp.shape = 1; //Curve
      	vert_final2.push_back(sptTemp);
      }
    }
  }//fin for

  p1 = vert_final[vert_final.size()-1].pt;
  p2 = vert_final[0].pt;
  middleP = Point2D((p1.x+p2.x)/2, (p1.y+p2.y)/2);
  pos1 = vert_final[vert_final.size()-1].index;
  pos2 = vert_final[0].index;
  unsigned int dd1 = (int) round((vec_ordXY.size()-pos1+pos2)/2);
  unsigned int dd2 = (int) round(dd1/4);
  posAfCen = 0;
  posBfCen = 0;
  posCen = 0;
  if(pos2-dd2<0)
    posBfCen = vec_ordXY.size()-(dd2-pos2);
  else
    posBfCen = pos2-dd2;
  if((pos1+dd2)<vec_ordXY.size())
    posAfCen = pos1+dd2;
  else
    posAfCen = dd2-(vec_ordXY.size()-pos1);

  if(pos1+dd1<vec_ordXY.size())
    posCen = pos1+dd1;
  else
    posCen = (dd1-(vec_ordXY.size()-pos1));

  pCen = vec_ordXY[posCen];
  pAfCen = vec_ordXY[posAfCen];
  pBfCen = vec_ordXY[posBfCen];

  p2p1 = p2 - p1;
  pcp1 = pCen - p1;
  dist = (p2p1.moduloProductoVectorial(pcp1))/p2p1.modulo();

  pacp1= pAfCen - p1;
  dist2 = (p2p1.moduloProductoVectorial(pacp1))/p2p1.modulo();

  pdcp1= pBfCen - p1;
  dist3 = (p2p1.moduloProductoVectorial(pdcp1))/p2p1.modulo();

  if (dist2>=dist || dist3>=dist)
  {
	  sptTemp.pt = p1;
    sptTemp.shape = 0; //Straight
    vert_final2.push_back(sptTemp);

  }
  else
  {
    if (abs(dist2-dist)<0.5 || abs(dist3-dist)<0.5)
    {
     sptTemp.pt = p1;
    	sptTemp.shape = 0; //Straight
      vert_final2.push_back(sptTemp);
    }
    else
    {
   	  sptTemp.pt = p1;
      sptTemp.shape = 1; //Curve
      vert_final2.push_back(sptTemp);
   }
  }
  return vert_final2;
}//Fin de findSegments


bool FiguresExtractor::pointInPolygon(Point2D * p, vector<Point2D> * pol)
{
  //Algorithm based on Jordan Curve Theorem

  /* The points creating the polygon. */
  double x1,x2;

  /* The coordinates of the point */
  double px = p->x;
  double py = p->y;

  /* How many times the ray crosses a line-segment */
  int crossings = 0;

  int sz = pol->size();
  /* Iterate through each line */
  for ( int i = 0; i < sz; i++ ){

	/* This is done to ensure that we get the same result when
	   the line goes from left to right and right to left */
	  if ( (*pol)[i].x < (*pol)[(i+1)%sz].x )
    {
		  x1 = (*pol)[i].x;
		  x2 = (*pol)[(i+1)%sz].x;
  	}
    else {
		  x1 = (*pol)[(i+1)%sz].x;
  		x2 = (*pol)[i].x;
	  }

  	/* First check if the ray is possible to cross the line */
  	if ( px > x1 && px <= x2 && ( py < (*pol)[i].x || py <= (*pol)[(i+1)%sz].y)) {
	  	static const double eps = 0.000001;

  		/* Calculate the equation of the line */
  		double dx = (*pol)[(i+1)%sz].x - (*pol)[i].x;
  		double dy = (*pol)[(i+1)%sz].y - (*pol)[i].y;
  		double k;

		  if ( fabs(dx) < eps )
			  k = INFINITY;	// math.h
      else
			  k = dy/dx;

		  double m = (*pol)[i].y - k * (*pol)[i].x;

		  /* Find if the ray crosses the line */
		  double y2 = k * px + m;
		  if ( py <= y2 ){
			  crossings++;
		  }
	  }
  }

  if (crossings % 2 == 1)
    return true;
  else
    return false;
}

bool FiguresExtractor::pointInPolygon(shapePt * p, vector<shapePt> * pol)
{
  //Algorithm based on Jordan Curve Theorem

  /* The points creating the polygon. */
  double x1, x2;

  /* The coordinates of the point */
  double px = p->pt.x;
  double py = p->pt.y;

  /* How many times the ray crosses a line-segment */
  int crossings = 0;

  int sz = pol->size();
  /* Iterate through each line */
  for ( int i = 0; i < sz; i++ ){

	/* This is done to ensure that we get the same result when
	   the line goes from left to right and right to left */
	  if ( (*pol)[i].pt.x < (*pol)[(i+1)%sz].pt.x )
    {
		  x1 = (*pol)[i].pt.x;
		  x2 = (*pol)[(i+1)%sz].pt.x;
  	}
    else {
		  x1 = (*pol)[(i+1)%sz].pt.x;
  		x2 = (*pol)[i].pt.x;
	  }

  	/* First check if the ray is possible to cross the line */
  	if ( px > x1 && px <= x2 && ( py < (*pol)[i].pt.x || py <= (*pol)[(i+1)%sz].pt.y)) {
	  	static const double eps = 0.000001;

  		/* Calculate the equation of the line */
  		double dx = (*pol)[(i+1)%sz].pt.x - (*pol)[i].pt.x;
  		double dy = (*pol)[(i+1)%sz].pt.y - (*pol)[i].pt.y;
  		double k;

		  if ( fabs(dx) < eps )
			  k = INFINITY;	// math.h
      else
			  k = dy/dx;

		  double m = (*pol)[i].pt.y - k * (*pol)[i].pt.x;

		  /* Find if the ray crosses the line */
		  double y2 = k * px + m;
		  if ( py <= y2 ){
			  crossings++;
		  }
	  }
  }

  if (crossings % 2 == 1)
    return true;
  else
    return false;
}

float FiguresExtractor::pixelLightness(float *crgb)
{
  float max=0, min=1;

  for (int i=0; i<3; i++)
  {
    if (crgb[i] > max)
      max = crgb[i];
    if (crgb[i] < min)
      min = crgb[i];
  }

  return (max+min)/2;
}

void FiguresExtractor::setEdgeAlgorithm(int ea)
{
	edgesAlgorithm = ea;
}
