#include "QualitativeDescriptor.h"

#define BTW(n, inf, sup) (n > inf && n <= sup) ? true : false

using namespace std;


QualitativeDescriptor::QualitativeDescriptor(void)
{
  dbg = false;
	version = 1;
}

/*
QualitativeDescriptor::~QualitativeDescriptor(void)
{
}
*/

QualitativeDescriptor::QualitativeDescriptor(Image * image)
{
  img = image;
  dbg = false;
	version = 1;
}

QualitativeDescriptor::QualitativeDescriptor(Image * image, int vers)
{
  img = image;
  dbg = false;
	version = vers;
}

void QualitativeDescriptor::clear(void)
{
  img = NULL;
}

void QualitativeDescriptor::setSourceImage(Image * image)
{
  img = image;
}

void QualitativeDescriptor::setVersion(int vers)
{
	version = vers;
}

void QualitativeDescriptor::generateDescription(bool orientation, Image * im)
{
  if (im != NULL)
    img = im;

  Figure * fig;

  cout<<"Generating Description..."<<endl;

  img->nfigures = img->figV.size();

  for (int i = 0; i<img->nfigures; i++)
  {
    fig = &(img->figV[i]);
    unsigned int prv, rear, sz;

    //Se actualiza el valor del numero de vertices, siendo ahora el real
    fig->nvertices = fig->infoVertices.size();

    /**** Calcular el punto con maxima Y para reordenar ****/

    // De momento no se hace. Si hiciera falta se implementa.

    /*******************************************************/

    sz = fig->nvertices;
    for (unsigned int j = 0; j<sz; j++)
    {
      prv = j;
      if (prv == 0)
        prv = sz;
      prv--;
      rear = (j + 1) % sz;

			if (version == 1) //Version extendida
			{
				if (fig->infoVertices[j].shape == 1) //curve
				{
					if (fig->infoVertices[prv].shape == 1) //curve
					{
						if (j != 0 && fig->qualPtV[prv].shape == 2)
						{
							fig->qualPtV.push_back(describeStraight(fig->infoVertices[prv], fig->infoVertices[j], fig->infoVertices[rear]));
							fig->qualPtV[j].shape = 22; //curve-curve
						}
						else
						{
							fig->qualPtV.push_back(describeCurve(fig->infoVertices[prv], fig->infoVertices[j], fig->infoVertices[rear]));
							fig->qualPtV[j].shape = 2; //curve (max curvature)
						}
					}
					else //line
					{
						fig->qualPtV.push_back(describeStraight(fig->infoVertices[prv], fig->infoVertices[j], fig->infoVertices[rear]));
						fig->qualPtV[j].shape = 12; //line-curve
					}
				}
				else //line
				{
					fig->qualPtV.push_back(describeStraight(fig->infoVertices[prv], fig->infoVertices[j], fig->infoVertices[rear]));
					if (fig->infoVertices[prv].shape == 0) //line
						fig->qualPtV[j].shape = 11; //line-line
					else //curve
						fig->qualPtV[j].shape = 21; //curve-line
				}
			}

			else if (version == 0) //Version original
			{
				if (fig->infoVertices[j].shape == 1) //curve
				{
					if (fig->infoVertices[prv].shape == 1) //curve
					{
						if (j == 0)
						{
							fig->qualPtV.push_back(describeCurve(fig->infoVertices[prv], fig->infoVertices[j], fig->infoVertices[rear]));
							//fig->qualPtV[j].shape = 2; //curve (max curvature)
							//Par la version original, la funcion describeCurve añade la "shape"
						}
					}
				}
				else //line
				{
					if (fig->infoVertices[prv].shape == 0) //line
					{

						fig->qualPtV.push_back(describeStraight(fig->infoVertices[prv], fig->infoVertices[j], fig->infoVertices[rear]));
						//fig->qualPtV[j].shape = 11; //line-line
						//Para la version original, la funcion describeStraight añade la "shape"
					}
				}
			}
    }

		fig->nqpts = fig->qualPtV.size();

    if (sz > 0)
    {
			fig->RGBtoHSV();
    	fig->RGBtoHSL();
			if (version == 1)
			{
      	//Se calcula la caracteristica cualitativa -color-
      	fig->color = HSV2qColor(fig->HSV);
			}
			else
			{
				fig->color = "None";
			}

      //Se calcula la convexidad de la figura
      fig->convexity = 1;
      for (unsigned int j = 0; j < fig->qualPtV.size(); j++)
      {
        if (fig->qualPtV[j].convexity == 0)
        {
          fig->convexity = 0;
          break;
        }
      }
    }


    //Zfalomir
    //---------
    //Generamos el nombre de la figura
    fig->set_regularity();
    fig->set_name();

    //Generamos el string de descripcion final
		if (version == 1)
    	fig->description = fig->shapeStringDescription();
		else if (version == 0)
			fig->description = fig->shapeStringDescriptionOriginal();

		if (orientation)
		{
	    fig->description = fig->stringDescription_all();
	    fig->VisualDescription = fig->stringVisualDescription();
	    //fig->SpatialDescription = fig->stringSpatialDescription();
	    fig->SpatialDescription = fig->stringSpatialDescription_object_centred();
		}

  }
}


QPoint QualitativeDescriptor::describeStraight(shapePt prvPt, shapePt actPt, shapePt rearPt)
{
	//cout<<prvPt<<" "<<actPt<<" "<<rearPt<<endl;

  QPoint qpt;
  double vector1x, vector1y, vector2x, vector2y, cosine, arcos;

  qpt.pt = actPt.pt;

  /* Se calcula el angulo */
  vector1x = prvPt.pt.x - actPt.pt.x;
  vector1y = prvPt.pt.y - actPt.pt.y;
  vector2x = rearPt.pt.x - actPt.pt.x;
  vector2y = rearPt.pt.y - actPt.pt.y;

  cosine = (vector1x * vector2x + vector1y * vector2y) / (sqrt(vector1x * vector1x + \
        vector1y * vector1y) * sqrt(vector2x * vector2x + vector2y * vector2y));

  if (cosine > 1) cosine = 1.0;
  else if (cosine < -1) cosine = -1.0;

  arcos = acos(cosine) * 180.0 / M_PI;


	if (version == 0)
	{
  	if(arcos < 85.0) //Originalmente 85
    	qpt.angle = -1; //acute
  	else if(arcos>98.0) //Originalmente 95
    	qpt.angle = 1; //obtuse
  	else
    	qpt.angle = 0; //right-angled
  }
  else if (version == 1)
  {
  	if((arcos > 0.0) && (arcos <= 40.0))
    	qpt.angle = -2; //very_acute
  	else if ((arcos > 40.0) && (arcos <= 85.0))
    	qpt.angle = -1; //acute
  	else if ((arcos > 85.0) && (arcos <= 95.0))
    	qpt.angle = 0; //right-angled
  	else if ((arcos > 95.0) && (arcos <= 130.0))
    	qpt.angle = 1; //obtuse
  	else  //entre (130,180]
    	qpt.angle = 2; //very_obtuse
	}


  /* Se calcula la concavidad */
  /*
  Point2D da = prvPt.pt - rearPt.pt;
  da.x = rearPt.pt.x + ((da.x)/2);
  da.y = rearPt.pt.y + ((da.y)/2);

  if (pointInPolygon(&da, vertices))
    qpt.convexity = 1; //convex
  else
    qpt.convexity = 0; //concave
  */

  double f = (actPt.pt.x - prvPt.pt.x) * (rearPt.pt.y - prvPt.pt.y) - (actPt.pt.y - prvPt.pt.y) * (rearPt.pt.x - prvPt.pt.x);
  if (f > 0)
    qpt.convexity = 1; //convex
  else
    qpt.convexity = 0; //concave


  /* Se calcula el tamaño */
  Point2D vec_dir1 = prvPt.pt - actPt.pt;
  double dist1 = round(vec_dir1.modulo());

  Point2D vec_dir2 = rearPt.pt - actPt.pt;
  double dist2 = round(vec_dir2.modulo());

	double q = dist1 / dist2;
	int sz;

	if (version == 1)
	{
		if (q < 0.4)
			sz = -3;
		else if (q <= 0.6)
			sz = -2;
		else if (q < 0.8) //Originalmente 0.95
			sz = -1;
		else if (q <= 1.20) //Originalmente 1.05
			sz = 0;
		else if (q < 1.9)
			sz = 1;
		else if (q <= 2.1)
			sz = 2;
		else
			sz = 3;
	}
	else if (version == 0)
	{
		if (q < 0.8) //Originalmente 0.9
			sz = -1;
		else if (q <= 1.25) //Originalmente 1.1
			sz = 0;
		else
			sz = 1;
	}

	qpt.size = sz;

	if (version == 0)
		qpt.shape = 11; //curve (max curvature)

  return qpt;
}



QPoint QualitativeDescriptor::describeCurve(shapePt prvPt, shapePt actPt, shapePt rearPt)
{
  QPoint qpt;
  Point2D da, db;
  //prvPt.pt: inicio de la curva
  //actPt.pt: punto de maxima curvatura
  //rearPt.pt: fin de la curva

  qpt.pt = actPt.pt;

  double f = (actPt.pt.x - prvPt.pt.x) * (rearPt.pt.y - prvPt.pt.y) - (actPt.pt.y - prvPt.pt.y) * (rearPt.pt.x - prvPt.pt.x);
  if (f > 0)
    qpt.convexity = 1; //convex
  else
    qpt.convexity = 0; //concave

  /* Se calcula el tipo de curvatura */
  da = prvPt.pt - rearPt.pt;
  da.x /= 2.0;
  da.y /= 2.0;

  double dist1 = round(da.modulo());

  db = actPt.pt - prvPt.pt;

  double dist2 = (da.moduloProductoVectorial(db))/da.modulo();

	double q = dist1 / dist2; // da / db

	int tc;

	if (version == 1)
	{
		if (q <= 0.5)
			tc = 2;
		else if (q < 0.95)
			tc = 1;
		else if (q <= 1.05)
			tc = 0;
		else if (q < 2)
			tc = -1;
		else
			tc = -2;
	}
	else if (version == 0)
	{
		if (q < 0.95)
			tc = 1;
		else if (q <= 1.05)
			tc = 0;
		else
			tc = -1;
	}

	qpt.angle = tc;


	/* Se calcula el tamaño */
  Point2D vec_dir1 = prvPt.pt - actPt.pt;
  dist1 = round(vec_dir1.modulo());

  Point2D vec_dir2 = rearPt.pt - actPt.pt;
  dist2 = round(vec_dir2.modulo());

	q = dist1 / dist2;
	int sz;

	if (version == 1)
	{
		if (q < 0.4)
			sz = -3;
		else if (q <= 0.6)
			sz = -2;
		else if (q < 0.8) //Originalmente 0.9
			sz = -1;
		else if (q <= 1.20) //Originalmente 1.1
			sz = 0;
		else if (q < 1.9)
			sz = 1;
		else if (q <= 2.1)
			sz = 2;
		else
			sz = 3;
	}

	else if (version == 0)
	{
		if (q < 0.8) //Originalmente 0.9
			sz = -1;
		else if (q <= 1.20) //Originalmente 1.1
			sz = 0;
		else
			sz = 1;
	}

	qpt.size = sz;

	if (version == 0)
		qpt.shape = 2; //curve (max curvature)

  return qpt;
}

string QualitativeDescriptor::HSV2qColor(int * hsv)
{
  string color = "", c = "", l = "", in = "";
  int h = hsv[0];
  int s = hsv[1];
  int v = hsv[2];

  if (v < 20)
    color = "black";
  else if (s < 20)
  {
    if (v < 40)
      color = "dark-grey";
    else if (v < 70)
      color = "grey";
    else if (v < 90)
      color = "light-grey";
    else
      color = "white";
  }
  else
  {
    if (h <= 40 || h > 320)
      c = "red";
    else if (BTW(h, 40, 80))
      c = "yellow";
    else if (BTW(h, 80, 160))
      c = "green";
    else if (BTW(h, 160, 200))
      c = "turquoise";
    else if (BTW(h, 200, 280))
      c = "blue";
		else if (BTW(h, 320, 335))
			c = "purple";

    /*
    if (v < 60)
      l = "dark-";

    if (s < 50)
      in = "pale-";
    */
    color = l + c;

    // Extra combinations
    /*
    if ((c == "orange") && BTW(v, 20, 60))
      color = "brown";
    if (((c == "violet") || (c == "lillac")) && BTW(v, 20, 60))
			color = "purple";
		if (c == "pink" && BTW(v, 25, 60))
      color = "burgundy";
		*/
    color = in + color;

  }

  return color;
}

