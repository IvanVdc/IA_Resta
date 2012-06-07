#include "Matching.h"

#include <stdio.h>
#include <stdlib.h>

Matching::Matching()
{
  map = NULL;
  fig = NULL;
  nmatched = 0;
  completed = false;
	version = 1;
}

Matching::Matching(Image * im)
{
  map = im;
  matched = vector<bool> (im->nfigures, false);
  fid = vector<int> (im->nfigures, -1);
  nmatched = 0;
  completed = false;
	version = 1;
}

void Matching::clear(void)
{
  nmatched = 0;
  completed = false;
  for (unsigned int i = 0; i < matched.size(); i++)
  {
  	matched[i] = false;
  	fid[i] = -1;
  }
}
 

void Matching::setMap(Image * im)
{
  map = im;
  matched.clear();
  matched = vector<bool> (im->nfigures, false);
  fid = vector<int> (im->nfigures, -1);
  nmatched = 0;
  completed = false;
}

void Matching::setVersion(int v)
{
	version = v;
}

int Matching::qualitativeMatch(Figure * f)
{
  Figure * srcF;
	int result = 0; //Numero de coincidencias encontradas

  for (int i = 0; i < map->nfigures; i++)
  {
    if (!matched[i])
    {
      srcF = &(map->figV[i]);
    
      if (figureComparision(srcF, f))
			{
	      result++;
        matched[i] = true;
	      nmatched++;
				fid[i] = f->id;
			}
    }
  }

  if (nmatched == map->nfigures)
    completed = true;

  return result;
}

bool Matching::figureComparision(Figure * f1, Figure * f2)
{
  bool result = false;
  //Se comprueba primero si coincide la descripcion mas abstracta de cada figura
  if ((f1->nvertices != f2->nvertices) || (f1->curves != f2->curves) || (f1->ncomponents != f2->ncomponents))
    return false;

  //Se comprueba si coincide el color
	if (version == 1)
	{
		if (f1->color != f2->color)
			return false;
	}
	else if (version == 0)
	{	//Distancia euclídea entre los dos puntos RGB
		float r1, g1, b1, r2, g2, b2, dist;
		
		r1 = f1->RGB[0];
		g1 = f1->RGB[1];
		b1 = f1->RGB[2];
		r2 = f2->RGB[0];
		g2 = f2->RGB[1];
		b2 = f2->RGB[2];
		
		dist = sqrt(pow(r1-r2, 2) + pow(g1-g2, 2) + pow(b1-b2, 2)) / 256.0;
		
		if (dist > 0.4)
			if (!(dist > 0.47 && dist < 0.48))
				return false;
	}
		
	/*
  int difH = f1->HSV[0] - f2->HSV[0];
  difH += difH < 0 ? 360 : 0;
  int difS = abs(f1->HSV[1] - f2->HSV[1]);
  int difV = abs(f1->HSV[2] - f2->HSV[2]);

  cout<<"Dif's: "<<difH<<" "<<difS<<" "<<difV<<endl;

  if (f1->color != f2->color)
    if (difH > 40 || difS > 50 || difV > 50)
      return false;
	*/

  //Se pasa a comprobar los puntos cualitativos
  int nvert = f1->nqpts; // = f2->nqpts;
  bool fin = false;
  int j, k = 0;
//	cout<<endl;
//	cout<<f1->description<<endl;
//	cout<<f2->description<<endl;
//	cout<<endl;
  while (!fin && k < nvert)
  {
    result = true;
    for (int i = 0; i < nvert; i++)
    {
      j = (i + k) % nvert;
      if(!QPointComparision(&(f1->qualPtV[i]), &(f2->qualPtV[j])))
      {
        result = false;
        break;
      }
    }

    if (result == true)
      fin = true;
    else
      k++;
  }

  return result;
}

bool Matching::QPointComparision(QPoint * p1, QPoint * p2)
{
  if ((p1->shape == p2->shape) && (p1->angle == p2->angle) && (p1->convexity == p2->convexity))
  {
    if (p1->shape != 2)
    {  
      if (p1->size == p2->size)
        return true;
			else
				return false;
    }
    else
      return true;
  }
  return false;
}

void Matching::drawResult(string fResName)
{
	int x, y;
	char text[3];
	unsigned char color[] = {0, 0, 255};
	CImg<float> im (map->imgRes);
	
	for (unsigned int i = 0; i < map->figV.size(); i++)
	{
		if (fid[i] != -1)
		{
			//color[0] = map->figV[i].RGB[0];
			//color[1] = map->figV[i].RGB[1];
			//color[2] = map->figV[i].RGB[2];
			//color = {map->figV[i].RGB[0], map->figV[i].RGB[1], map->figV[i].RGB[2]};
			//itoa(fid[i], text, 10);
			sprintf(text, "%d", fid[i]+1);
			
			x = (int) round((map->figV[i]).centroid.x);
			y = (int) round((map->figV[i]).centroid.y);
			
			im.draw_text(x, y, text, color, 0, 1, 18);
		}
	}
	im.save(fResName.c_str());
	//map->imgRes.display(map->fResName.c_str());
	
}
