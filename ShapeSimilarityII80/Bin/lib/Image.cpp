#include "Image.h"

#define TAM_JUNTA	20.0

using namespace std;

Image::Image(string f, CImg<float> srcImg)
{
	img = srcImg;
	fName = f;
	fResName = "";
	nfigures = 0;
	hgt = img.dimy();
	wdt = img.dimx();
	area = hgt * wdt;
	imgRes = srcImg;
	imgRes.fill(255.0f);

}

void Image::setSourceImg(string f, CImg<float> srcImg)
{
	img = srcImg;
	fName = f;
	fResName = "";
	nfigures = 0;
	hgt = img.dimy();
	wdt = img.dimx();
	imgRes = srcImg;
	imgRes.fill(255.0f);
}

string Image::fileName()
{
	return fName;
}

void Image::drawID()
{
	int x, y;
	char text[3];
	unsigned char color[] = {0, 0, 255};

	for (unsigned int i = 0; i < figV.size(); i++)
	{
		sprintf(text, "%d", figV[i].id+1);
		//color[0] = figV[i].RGB[0];
		//color[1] = figV[i].RGB[1];
		//color[2] = figV[i].RGB[2];

		x = (int) round(figV[i].centroid.x);
		y = (int) round(figV[i].centroid.y);

		imgRes.draw_text(x, y, text, color, 0, 1, 18);
	}
	//imgRes.display(map->fResName.c_str());
}

void Image::obtaining_all_slopes_for_each_figure(void)
{

	cout << "##### Obtaining Slopes..." << endl;
	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{
		cout << "Fig " << j << endl;
		figV[j].set_slopesVector();
	}

}

float euclidean_distance(Point2D c1, Point2D c2)
{

	float euclidean_distance, resta_x, resta_y = 0.0;

	resta_x = c2.getX() - c1.getX();
	resta_y = c2.getY() - c1.getY();

	euclidean_distance = sqrt(resta_x * resta_x + resta_y * resta_y);

	return euclidean_distance;

}

void Image::obtaining_neighbours_of_all_figures(void)
{

	float distance = 0.0;
	int neighbour_added = 0;

	cout << "##### Obtaining Neighbours..." << endl;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{

		for (unsigned int f = 0; f < figV.size(); f++)
		{

			if (f != j)
			{

				neighbour_added = 0;

				for (unsigned int vj = 0; vj < figV[j].vertices.size(); vj++)
				{
					for (unsigned int vf = 0; vf < figV[f].vertices.size(); vf++)
					{

						distance = euclidean_distance(figV[j].vertices[vj],
								figV[f].vertices[vf]);
						if ((!neighbour_added) && (distance < TAM_JUNTA))
						{
							//figuras vecinas
							cout << "Fig " << j << " and Fig " << f << " neighbours --";
							cout << "distance (vj" << vj << ", vf" << vf << ") = "
									<< distance << endl;
							figV[j].neighboursVector.push_back(f);
							neighbour_added = 1;
						}
					}
				}
			}
		}
	}

}

void Image::obtaining_topological_relations(void)
{

	float distance = 0.0;
	int neighbour_added = 0;

	cout << "##### Obtaining Topological Relations..." << endl;

	//Para cada figura detectada dentro de una imagen
	//Cuando tengamos esto por niveles, lo tendremos que hacer para cada figura dentro de un nivel
	for (unsigned int j = 0; j < figV.size(); j++)
	{

		figV[j].topologicalRelVector.clear();

		for (unsigned int f = 0; f < figV.size(); f++)
		{

			if (f == j)
			{
				figV[j].topologicalRelVector.push_back(SAME);
			}
			else
			{

				neighbour_added = 0;

				for (unsigned int vj = 0; vj < figV[j].vertices.size(); vj++)
				{
					for (unsigned int vf = 0; vf < figV[f].vertices.size(); vf++)
					{

						distance = euclidean_distance(figV[j].vertices[vj],
								figV[f].vertices[vf]);
						if ((!neighbour_added) && (distance < TAM_JUNTA))
						{
							//figuras vecinas
							cout << "Fig " << j << " and Fig " << f << " neighbours --";
							cout << "distance (vj" << vj << ", vf" << vf << ") = "
									<< distance << endl;
							figV[j].neighboursVector.push_back(f);
							figV[j].topologicalRelVector.push_back(TOUCHING);
							neighbour_added = 1;
						}
					}
				}

				//Si estan dentro del mismo nivel y no son vecinos, estaran disjoint.
				//Más adelante comprobaremos lo del mismo nivel
				if (!neighbour_added)
				{
					figV[j].disjointsVector.push_back(f);
					figV[j].topologicalRelVector.push_back(DISJOINT);
				}
			}
		}
	}

}

QSize_wrt_Image_Type Obtaining_figure_size_wrt_image_size(float image_size,
		float figure_area)
{

	float relation = figure_area / image_size;
	float relation2 = image_size / figure_area;

	cout << "ComparedSize_Relation: " << relation << ", inverse: " << relation2
			<< endl;

	if ((relation > 0.0) && (relation < 0.1))
	{
		return small;
	}
	else if ((relation >= 0.1) && (relation < 0.250))
	{
		return medium;
	}
	else if ((relation >= 0.250) && (relation < 1.0))
	{
		return large;
	}
	else
		return none_size_wrt_image;

}

void Image::obtaining_compared_size_wrt_image()
{

	float figure_area = 0.0;
	QSize_wrt_Image_Type size_wrt_image;

	cout << "Image_Area (wdt:" << wdt << ", hgt:" << hgt << ")= " << area << endl;
	//cout << "Image_Centroid = (" << centroid.getX() << ", " << centroid.getY() <<")"<< endl;
	cout << "Image_Centroid = (" << centroid_x << ", " << centroid_y << ")"
			<< endl;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{

		figure_area = figV[j].area;
		size_wrt_image = Obtaining_figure_size_wrt_image_size(area, figure_area);
		figV[j].set_Size_wrt_Image(size_wrt_image);

		cout << "ComparedSize_Relation[" << j << ", image]:";
		switch (figV[j].size_wrt_image)
		{
			case (none_size_wrt_image):
				cout << "none" << endl;
				break;
			case (small):
				cout << "small" << endl;
				break;
			case (medium):
				cout << "medium" << endl;
				break;
			case (large):
				cout << "large" << endl;
				break;
			default:
				cout << "error" << endl;
				break;
		}
	}

}

QSize_wrt_Fig_Type Obtaining_figure_size_wrt_figure_size(int current_fig_id,
		int id_fig_wrt, float current_figure_area, float other_figure_area)
{

	float relation = current_figure_area / other_figure_area;

	cout << "Relation[" << current_fig_id << ", " << id_fig_wrt << "]: "
			<< relation << endl;

	if ((relation > 0.0) && (relation < 0.49))
	{
		return much_smaller;
	}
	else if ((relation >= 0.49) && (relation <= 0.51))
	{
		return half_size;
	}
	else if ((relation > 0.51) && (relation < 0.99))
	{
		return a_bit_smaller;
	}
	else if ((relation >= 0.99) && (relation <= 1.1))
	{
		return similar_size;
	}
	else if ((relation > 1.1) && (relation < 1.99))
	{
		return a_bit_bigger;
	}
	else if ((relation >= 1.99) && (relation <= 2.1))
	{
		return double_size;
	}
	else if (relation > 2.1)
	{
		return much_bigger;
	}
	else
		return none_size_wrt_figure;

}

void Image::obtaining_compared_size_wrt_figures()
{

	float current_figure_area = 0.0, other_figure_area = 0.0;
	QSize_wrt_Fig_Type size_wrt_fig;
	ComparedSize comSizeObject;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{

		current_figure_area = figV[j].area;

		for (unsigned int f = 0; f < figV.size(); f++)
		{

			if (f != j)
			{
				other_figure_area = figV[f].area;
				size_wrt_fig = Obtaining_figure_size_wrt_figure_size(j, f,
						current_figure_area, other_figure_area);
				comSizeObject.set_ComparedSize(f, size_wrt_fig);
				figV[j].sizeVector_wrt_fig.push_back(comSizeObject);
			}
		}
	}

}

void Image::obtaining_compared_size_wrt_neighbours()
{

	float current_figure_area = 0.0, other_figure_area = 0.0;
	QSize_wrt_Fig_Type size_wrt_fig;
	ComparedSize comSizeObject;
	unsigned int vecino;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{

		current_figure_area = figV[j].area;

		for (unsigned int f = 0; f < figV[j].neighboursVector.size(); f++)
		{

			vecino = figV[j].neighboursVector[f];

			other_figure_area = figV[vecino].area;
			size_wrt_fig = Obtaining_figure_size_wrt_figure_size(j, vecino,
					current_figure_area, other_figure_area);
			comSizeObject.set_ComparedSize(vecino, size_wrt_fig);
			figV[j].sizeVector_wrt_fig.push_back(comSizeObject);
		}
	}

}

QFixed_Orientation_Type obtaining_fixed_orientation(int x0, int y0, int x,
		int y)
{

	double pte; //Pendiente

	//Pendiente 0 o infinita --> una coordenada coincide con la coordenada del centroide
	if ((x == x0) || (y == y0))
	{

		if ((x == x0) && (y == y0))
			return _centre;
		else if ((y == y0) && (x > x0))
			return _right;
		else if ((y == y0) && (x < x0))
			return _left;
		else if ((x == x0) && (y > y0))
			return _back;
		else if ((x == x0) && (y < y0))
			return _front;
		else
			return none_orientation;
	}
	else
	{

		//Calculamos la pendiente del vértice actual al centroide
		pte = ((double) y - (double) y0) / ((double) x - (double) x0);
		//cout << "pte = ("<< y <<" - " << y0 <<") / ("<< x << " - "<< x0 << ") = " << pte << endl;

		//cuadrante I
		if ((x > x0) && (y < y0))
		{
			if ((abs(pte) > 0.0) && (abs(pte) <= 0.5))
				return _right;
			else if ((abs(pte) > 0.5) && (abs(pte) <= 2.0))
				return _front_right;
			else if (abs(pte) > 2.0)
				return _front;
			else
				return none_orientation;
		}
		//cuadrante II
		else if ((x < x0) && (y < y0))
		{
			if ((abs(pte) > 0.0) && (abs(pte) <= 0.5))
				return _left;
			else if ((abs(pte) > 0.5) && (abs(pte) <= 2.0))
				return _front_left;
			else if (abs(pte) > 2.0)
				return _front;
			else
				return none_orientation;
		}
		//cuadrante III
		else if ((x < x0) && (y > y0))
		{
			if ((abs(pte) > 0.0) && (abs(pte) <= 0.5))
				return _left;
			else if ((abs(pte) > 0.5) && (abs(pte) <= 2.0))
				return _back_left;
			else if (abs(pte) > 2.0)
				return _back;
			else
				return none_orientation;
		}
		//cuadrante IV
		else if ((x > x0) && (y > y0))
		{
			if ((abs(pte) > 0.0) && (abs(pte) <= 0.5))
				return _right;
			else if ((abs(pte) > 0.5) && (abs(pte) <= 2.0))
				return _back_right;
			else if (abs(pte) > 2.0)
				return _back;
			else
				return none_orientation;
		}
		else
			return none_orientation;
	}

}

void Image::obtaining_fixed_orientation_wrt_image()
{

	int x, y = -1;
	QFixed_Orientation_Type fOrient;

	cout << "Fixed Orientation wrt Image " << endl;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{

		//Para cada vértice de la figura
		for (unsigned int v = 0; v < figV[j].vertices.size(); v++)
		{
			x = figV[j].vertices[v].getX();
			y = figV[j].vertices[v].getY();
			fOrient = obtaining_fixed_orientation(centroid_x, centroid_y, x, y);
			figV[j].adding_fixed_orient_wrt_image(fOrient); //mirar si la orientación no está en el vector y entonces añadirla.
		}

		figV[j].simplifying_fixed_orient_wrt_image(); //Añade la etiqueta "centre"
	}

}

void Image::obtaining_fixed_orientation_of_all_vertices()
{

	int x, y = -1;
	QFixed_Orientation_Type fOrient;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{

		//Para cada vértice de la figura
		for (unsigned int v = 0; v < figV[j].vertices.size(); v++)
		{
			x = figV[j].vertices[v].getX();
			y = figV[j].vertices[v].getY();
			fOrient = obtaining_fixed_orientation(figV[j].centroid.getX(),
					figV[j].centroid.getY(), x, y);
			figV[j].VFixed_Orient_vertices.push_back(fOrient);
		}
	}

}

void Image::obtaining_fixed_orientation_wrt_image_centroid_version()
{

	int x, y = -1;
	QFixed_Orientation_Type fOrient;

	cout << "Fixed Orientation wrt Image " << endl;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{

		//Para cada el centroide de cada figura
		x = figV[j].centroid.getX();
		y = figV[j].centroid.getY();
		fOrient = obtaining_fixed_orientation(centroid_x, centroid_y, x, y);
		figV[j].VFixed_Orient_wrt_image.push_back(fOrient);
		figV[j].simplifying_fixed_orient_wrt_image();
	}

}

void Image::obtaining_fixed_orientation_wrt_neighbours()
{

	int x, y, fig_centroid_x, fig_centroid_y = -1;
	QFixed_Orientation_Type fOrient;
	unsigned int vecino;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int i = 0; i < figV.size(); i++)
	{

		fig_centroid_x = figV[i].centroid.getX();
		fig_centroid_y = figV[i].centroid.getY();

		cout << "\nFixed Orientation wrt Figure " << i << " Centroid ("
				<< fig_centroid_x << ", " << fig_centroid_y << ")" << endl;

		FixedOrientation FOrientObject;
		FOrientObject.set_Figure_id(i);

		for (unsigned int j = 0; j < figV[i].neighboursVector.size(); j++)
		{

			vecino = figV[i].neighboursVector[j];

			//Para cada vértice de la figura
			for (unsigned int v = 0; v < figV[vecino].vertices.size(); v++)
			{
				cout << "Figure " << vecino;
				x = figV[vecino].vertices[v].getX();
				y = figV[vecino].vertices[v].getY();
				cout << " vert(" << x << ", " << y << ")" << endl;
				fOrient = obtaining_fixed_orientation(fig_centroid_x, fig_centroid_y,
						x, y);
				//FOrientObject.VFixed_orient.push_back(fOrient);
				FOrientObject.add_FixedOrientation(fOrient); //Añadimos sólo etiquetas no repetidas

			}

			figV[vecino].VFixed_Orient_wrt_figures.push_back(FOrientObject);
			cout << FOrientObject << endl;
			FOrientObject.VFixed_orient.clear();

		}

	}

}

void Image::obtaining_fixed_orientation_wrt_figures_centroid_version()
{

	int x, y, fig_centroid_x, fig_centroid_y = -1;
	QFixed_Orientation_Type fOrient;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int i = 0; i < figV.size(); i++)
	{

		fig_centroid_x = figV[i].centroid.getX();
		fig_centroid_y = figV[i].centroid.getY();

		cout << "\nFixed Orientation wrt Figure " << i << " Centroid ("
				<< fig_centroid_x << ", " << fig_centroid_y << ")" << endl;

		FixedOrientation FOrientObject;
		FOrientObject.set_Figure_id(i);

		for (unsigned int j = 0; j < figV.size(); j++)
		{

			if (j != i)
			{
				//Para cada vértice de la figura
				cout << "Figure " << j;
				x = figV[j].centroid.getX();
				y = figV[j].centroid.getY();
				cout << " vert(" << x << ", " << y << ")" << endl;
				fOrient = obtaining_fixed_orientation(fig_centroid_x, fig_centroid_y,
						x, y);
				FOrientObject.VFixed_orient.push_back(fOrient);
				figV[j].VFixed_Orient_wrt_figures.push_back(FOrientObject);
				cout << FOrientObject << endl;
				FOrientObject.VFixed_orient.clear();
			}
		}

	}

}

void Image::obtaining_fixed_orientation_wrt_figures_object_centred()
{

	int x, y, fig_centroid_x, fig_centroid_y = -1;
	QFixed_Orientation_Type fOrient;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int i = 0; i < figV.size(); i++)
	{

		fig_centroid_x = figV[i].centroid.getX();
		fig_centroid_y = figV[i].centroid.getY();

		cout << "\nFixed Orientation wrt Figure " << i << " Centroid ("
				<< fig_centroid_x << ", " << fig_centroid_y << ")" << endl;

		for (unsigned int j = 0; j < figV.size(); j++)
		{

			if (j != i)
			{
				FixedOrientation FOrientObject;
				FOrientObject.set_Figure_id(j);

				//Para cada vértice de la figura
				for (unsigned int v = 0; v < figV[j].vertices.size(); v++)
				{
					cout << "Figure " << j;
					x = figV[j].vertices[v].getX();
					y = figV[j].vertices[v].getY();
					cout << " vert(" << x << ", " << y << ")" << endl;
					fOrient = obtaining_fixed_orientation(fig_centroid_x, fig_centroid_y,
							x, y);
					//FOrientObject.VFixed_orient.push_back(fOrient);
					FOrientObject.add_FixedOrientation(fOrient); //Añadimos sólo etiquetas no repetidas

				}

				//figV[j].VFixed_Orient_wrt_figures.push_back(FOrientObject);
				figV[i].VFixed_Orient_wrt_figures.push_back(FOrientObject);
				cout << FOrientObject << endl;
				FOrientObject.VFixed_orient.clear();
			}

		}

	}

}

void Image::obtaining_fixed_orientation_wrt_figures()
{

	int x, y, fig_centroid_x, fig_centroid_y = -1;
	QFixed_Orientation_Type fOrient;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int i = 0; i < figV.size(); i++)
	{

		fig_centroid_x = figV[i].centroid.getX();
		fig_centroid_y = figV[i].centroid.getY();

		cout << "\nFixed Orientation wrt Figure " << i << " Centroid ("
				<< fig_centroid_x << ", " << fig_centroid_y << ")" << endl;

		FixedOrientation FOrientObject;
		FOrientObject.set_Figure_id(i);

		for (unsigned int j = 0; j < figV.size(); j++)
		{

			if (j != i)
			{
				//Para cada vértice de la figura
				for (unsigned int v = 0; v < figV[j].vertices.size(); v++)
				{
					cout << "Figure " << j;
					x = figV[j].vertices[v].getX();
					y = figV[j].vertices[v].getY();
					cout << " vert(" << x << ", " << y << ")" << endl;
					fOrient = obtaining_fixed_orientation(fig_centroid_x, fig_centroid_y,
							x, y);
					//FOrientObject.VFixed_orient.push_back(fOrient);
					FOrientObject.add_FixedOrientation(fOrient); //Añadimos sólo etiquetas no repetidas

				}

				//figV[j].VFixed_Orient_wrt_figures.push_back(FOrientObject);
				figV[i].VFixed_Orient_wrt_figures.push_back(FOrientObject);
				cout << FOrientObject << endl;
				FOrientObject.VFixed_orient.clear();
			}

		}

	}

}

//Modificar
void Image::obtaining_fixed_orientation_of_vertices_wrt_centroid()
{

	int x, y, fig_centroid_x, fig_centroid_y = -1;
	QFixed_Orientation_Type fOrient;

	//Para cada figura detectada dentro de una imagen
	for (unsigned int i = 0; i < figV.size(); i++)
	{

		fig_centroid_x = figV[i].centroid.getX();
		fig_centroid_y = figV[i].centroid.getY();

		cout << "\nFixed Orientation wrt Figure " << i << " Centroid ("
				<< fig_centroid_x << ", " << fig_centroid_y << ")" << endl;

		FixedOrientation FOrientObject;
		FOrientObject.set_Figure_id(i);

		for (unsigned int j = 0; j < figV.size(); j++)
		{

			if (j != i)
			{
				//Para cada vértice de la figura
				for (unsigned int v = 0; v < figV[j].vertices.size(); v++)
				{
					cout << "Figure " << j;
					x = figV[j].vertices[v].getX();
					y = figV[j].vertices[v].getY();
					cout << " vert(" << x << ", " << y << ")" << endl;
					fOrient = obtaining_fixed_orientation(fig_centroid_x, fig_centroid_y,
							x, y);
					//FOrientObject.VFixed_orient.push_back(fOrient);
					FOrientObject.add_FixedOrientation(fOrient); //Añadimos sólo etiquetas no repetidas

				}

				figV[j].VFixed_Orient_wrt_figures.push_back(FOrientObject);
				cout << FOrientObject << endl;
				FOrientObject.VFixed_orient.clear();
			}

		}

	}

}

QComparedDistance_Type obtaining_qualitative_compared_distance(
		float distance_from_i_to_j, float distance_from_i_to_k)
{

	if (distance_from_i_to_j == distance_from_i_to_k)
		return nearby;
	else if (distance_from_i_to_j > distance_from_i_to_k)
		return further_than;
	else if (distance_from_i_to_j < distance_from_i_to_k)
		return closer_than;
	else
		return none_distance;
}

void Image::obtaining_numerical_distances()
{

	float distance = -1;

	//Para cada figura detectada dentro de una imagen
	//calculamos la distancia de su centroide al resto de centroides
	//del resto de las figuras.
	for (unsigned int i = 0; i < figV.size(); i++)
	{

		cout << "Fig " << i;

		for (unsigned int j = 0; j < figV.size(); j++)
		{

			if (i != j)
			{

				distance = euclidean_distance(figV[i].centroid, figV[j].centroid);

			}
			else
			{
				distance = 0.0;
			}

			figV[i].set_distance(j, distance);
			cout << "\tdistance to " << j << " is " << figV[i].distanceVector[j]
					<< endl;
		}

	}

}

void Image::obtaining_qualitative_distances()
{

	float distance_from_i_to_j, distance_from_i_to_k = 0.0;
	QComparedDistance_Type qComparedDist;

	for (unsigned int i = 0; i < figV.size(); i++)
	{

		for (unsigned int j = 0; j < figV[i].distanceVector.size(); j++)
		{

			for (unsigned int k = 0; k < figV[i].distanceVector.size(); k++)
			{

				if (j != k)
				{

					distance_from_i_to_j = figV[i].distanceVector[j];
					distance_from_i_to_k = figV[i].distanceVector[k];

					//No comparamos las distancias con respecto al mismo objecto (distancia 0.0)
					if ((distance_from_i_to_j != 0.0) && (distance_from_i_to_k != 0.0))
					{

						cout << "distance_from_i_to_j: " << distance_from_i_to_j << endl;
						cout << "distance_from_i_to_k: " << distance_from_i_to_k << endl;

						qComparedDist = obtaining_qualitative_compared_distance(
								distance_from_i_to_j, distance_from_i_to_k);

						ComparedDistance cd_object;
						cd_object.set_ComparedDistance(j, k, distance_from_i_to_j,
								distance_from_i_to_k, qComparedDist);

						figV[i].VCompared_distances.push_back(cd_object);
						cout << "CompareDistanceObject:" << cd_object << endl;
					}
				}

			}
		}
	}

}

void Image::obtaining_compared_distances()
{

	obtaining_numerical_distances();
	obtaining_qualitative_distances();

}

void Image::obtaining_all_RS_in_the_image()
{

	cout << "All RSs in the image..." << endl;

	for (unsigned int i = 0; i < figV.size(); i++)
	{

		for (unsigned int j = 0; j < figV.size(); j++)
		{

			if (i != j)
			{

				RS rs(i, j);

				vRS.push_back(rs);
				cout << "RS: " << rs << endl;
			}

		}
	}

}

void Image::obtaining_all_RS_in_the_image_without_inverses()
{

	cout << "All RSs in neighbours..." << endl;

	for (unsigned int i = 0; i < figV.size(); i++)
	{

		for (unsigned int j = i; j < figV.size(); j++)
		{

			if (i != j)
			{

				RS rs(i, j);

				vRS.push_back(rs);
				cout << "RS: " << rs << endl;
			}

		}
	}

}

int vertex_in_rta_a_b(Point2D vertex, Point2D fig_a_centroid,
		Point2D fig_b_centroid)
{

	float lambda1, lambda2 = 0.0;
	double xa, ya, xb, yb, x, y = 0.0;

	xa = fig_a_centroid.getX();
	ya = fig_a_centroid.getY();
	xb = fig_b_centroid.getX();
	yb = fig_b_centroid.getY();
	x = vertex.getX();
	y = vertex.getY();

	lambda1 = (y - ya) / (yb - ya);
	lambda2 = (x - xa) / (xb - xa);

	if (lambda1 == lambda2)
		return 1;
	else
		return 0;

}

int vertex_in_rta_x_a(Point2D vertex, Point2D fig_a_centroid,
		Point2D fig_b_centroid)
{

	float lambda1, lambda2 = 0.0;
	double xa, ya, xb, yb, x, y = 0.0;

	xa = fig_a_centroid.getX();
	ya = fig_a_centroid.getY();
	xb = fig_b_centroid.getX();
	yb = fig_b_centroid.getY();
	x = vertex.getX();
	y = vertex.getY();

	lambda1 = (y - ya) / (xb - xa);
	lambda2 = (xa - x) / (yb - ya);

	if (lambda1 == lambda2)
		return 1;
	else
		return 0;

}

int vertex_in_rta_x_b(Point2D vertex, Point2D fig_a_centroid,
		Point2D fig_b_centroid)
{

	float lambda1, lambda2 = 0.0;
	double xa, ya, xb, yb, x, y = 0.0;

	xa = fig_a_centroid.getX();
	ya = fig_a_centroid.getY();
	xb = fig_b_centroid.getX();
	yb = fig_b_centroid.getY();
	x = vertex.getX();
	y = vertex.getY();

	lambda1 = (y - yb) / (xb - xa);
	lambda2 = (xb - x) / (yb - ya);

	if (lambda1 == lambda2)
		return 1;
	else
		return 0;

}

Point2D obtaining_proyeccion_pto_rta_a_b(Point2D vertex,
		Point2D fig_a_centroid, Point2D fig_b_centroid, float *distancia)
{

	double xp, yp, xa, ya, xb, yb = 0.0;
	float lambda, a, b = 0.0;
	double xp_prima, yp_prima = 0.0;

	//Coordenadas de todos los puntos
	xp = vertex.getX();
	yp = vertex.getY();
	xa = fig_a_centroid.getX();
	ya = fig_a_centroid.getY();
	xb = fig_b_centroid.getX();
	yb = fig_b_centroid.getY();

	//Parámetros intermedios
	a = xb - xa;
	b = yb - ya;
	lambda = (a * (xp - xa) + b * (yp - ya)) / (a * a + b * b);

	//Pto en frente de vertex que pertenece a la recta a_b
	xp_prima = xa + a * lambda;
	yp_prima = ya + b * lambda;

	Point2D p_prima(xp_prima, yp_prima);

	*distancia = euclidean_distance(vertex, p_prima);

	return p_prima;
}

Point2D obtaining_proyeccion_pto_rta_x_a(Point2D vertex,
		Point2D fig_a_centroid, Point2D fig_b_centroid, float *distancia)
{

	double xp, yp, xa, ya, xb, yb = 0.0;
	float lambda, a, b = 0.0;
	double xp_prima, yp_prima = 0.0;

	//Coordenadas de todos los puntos
	xp = vertex.getX();
	yp = vertex.getY();
	xa = fig_a_centroid.getX();
	ya = fig_a_centroid.getY();
	xb = fig_b_centroid.getX();
	yb = fig_b_centroid.getY();

	//Parámetros intermedios
	a = ya - yb;
	b = xb - xa;
	lambda = (a * (xp - xa) + b * (yp - ya)) / (a * a + b * b);

	//Pto en frente de vertex que pertenece a la recta a_b
	xp_prima = xa + a * lambda;
	yp_prima = ya + b * lambda;

	Point2D p_prima(xp_prima, yp_prima);

	*distancia = euclidean_distance(vertex, p_prima);

	return p_prima;
}

Point2D obtaining_proyeccion_pto_rta_x_b(Point2D vertex,
		Point2D fig_a_centroid, Point2D fig_b_centroid, float *distancia)
{

	double xp, yp, xa, ya, xb, yb = 0.0;
	float lambda, a, b = 0.0;
	double xp_prima, yp_prima = 0.0;

	//Coordenadas de todos los puntos
	xp = vertex.getX();
	yp = vertex.getY();
	xa = fig_a_centroid.getX();
	ya = fig_a_centroid.getY();
	xb = fig_b_centroid.getX();
	yb = fig_b_centroid.getY();

	//Parámetros intermedios
	a = ya - yb;
	b = xb - xa;
	lambda = (a * (xp - xb) + b * (yp - yb)) / (a * a + b * b);

	//Pto en frente de vertex que pertenece a la recta a_b
	xp_prima = xb + a * lambda;
	yp_prima = yb + b * lambda;

	Point2D p_prima(xp_prima, yp_prima);

	*distancia = euclidean_distance(vertex, p_prima);

	return p_prima;
}

QRelative_Orientation_Type obtaining_relative_orientation_wrt_cross_A(
		Point2D pa, Point2D pb, Point2D pp_a_b, Point2D pp_x_a)
{

	//cout << "Entramos en wrt cross A"<<endl;
	//cout << "a:" <<pa <<", b:"<<pb<<", pp_a_b:"<<pp_a_b<<", pp_x_a:"<<pp_x_a<<endl<<endl;

	//Tendencia 1: x e y disminuyen
	if ((pb.getX() < pa.getX()) && (pb.getY() < pa.getY()))
	{

		//Pto delante de a
		if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() < pa.getY()))
		{

			if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return rm; //right-middle
			else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de a
		if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() > pa.getY()))
		{

			if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return br; //back-right
			else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return bl; //back-left
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 2: x cte e y disminuye
	if ((pb.getX() == pa.getX()) && (pb.getY() < pa.getY()))
	{

		//Pto delante de a
		if ((pp_a_b.getX() == pa.getX()) && (pp_a_b.getY() < pa.getY()))
		{

			if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() == pa.getY()))
				return rm; //right-middle
			else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() == pa.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de a
		if ((pp_a_b.getX() == pa.getX()) && (pp_a_b.getY() > pa.getY()))
		{

			if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() == pa.getY()))
				return br; //back-right
			else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() == pa.getY()))
				return bl; //back-left
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 3: x aumenta e y disminuye
	if ((pb.getX() > pa.getX()) && (pb.getY() < pa.getY()))
	{

		//Pto delante de a
		if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() < pa.getY()))
		{

			if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return rm; //right-middle
			else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de a
		if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() > pa.getY()))
		{

			if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return br; //back-right
			else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return bl; //back-left
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 4: x aumenta e y cte
	if ((pb.getX() > pa.getX()) && (pb.getY() == pa.getY()))
	{

		//Pto delante de a
		if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() == pa.getY()))
		{

			if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return rm; //right-middle
			else if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de a
		if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() == pa.getY()))
		{

			if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return br; //back-right
			else if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return bl; //back-left
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else //Tendencia 5: x aumenta e y aumenta
	if ((pb.getX() > pa.getX()) && (pb.getY() > pa.getY()))
	{

		//Pto delante de a
		if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() > pa.getY()))
		{

			if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return rm; //right-middle
			else if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de a
		if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() < pa.getY()))
		{

			if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return br; //back-right
			else if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return bl; //back-left
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else //Tendencia 6: x cte e y aumenta
	if ((pb.getX() == pa.getX()) && (pb.getY() > pa.getY()))
	{

		//Pto delante de a
		if ((pp_a_b.getX() == pa.getX()) && (pp_a_b.getY() > pa.getY()))
		{

			if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() == pa.getY()))
				return rm; //right-middle
			else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() == pa.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de a
		if ((pp_a_b.getX() == pa.getX()) && (pp_a_b.getY() < pa.getY()))
		{

			if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() == pa.getY()))
				return br; //back-right
			else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() == pa.getY()))
				return bl; //back-left
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else //Tendencia 7: x disminuye e y aumenta
	if ((pb.getX() < pa.getX()) && (pb.getY() > pa.getY()))
	{

		//Pto delante de a
		if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() > pa.getY()))
		{

			if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return rm; //right-middle
			else if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de a
		if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() < pa.getY()))
		{

			if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return br; //back-right
			else if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return bl; //back-left
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else //Tendencia 8: x disminuye e y cte
	if ((pb.getX() < pa.getX()) && (pb.getY() == pa.getY()))
	{

		//Pto delante de a
		if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() == pa.getY()))
		{

			if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return rm; //right-middle
			else if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de a
		if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() == pa.getY()))
		{

			if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() < pa.getY()))
				return br; //back-right
			else if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() > pa.getY()))
				return bl; //back-left
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else
		return none_rel_orientation;

}

QRelative_Orientation_Type obtaining_relative_orientation_wrt_cross_B(
		Point2D pa, Point2D pb, Point2D pp_a_b, Point2D pp_x_b)
{

	//cout << "Entramos en wrt cross B"<<endl;
	//cout << "a:" <<pa <<", b:"<<pb<<", pp_a_b:"<<pp_a_b<<", pp_x_b:"<<pp_x_b<<endl<<endl;

	//Tendencia 1: x e y disminuyen
	if ((pb.getX() < pa.getX()) && (pb.getY() < pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{

			if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return rf; //right-front
			else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return lf; //left-front
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{

			if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return rm; //right-middle
			else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 2: x cte e y disminuye
	if ((pb.getX() == pa.getX()) && (pb.getY() < pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() == pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{

			if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() == pb.getY()))
				return rf; //right-front
			else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() == pb.getY()))
				return lf; //left-front
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() == pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{

			if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() == pb.getY()))
				return rm; //right-middle
			else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() == pb.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 3: x aumenta e y disminuye
	if ((pb.getX() > pa.getX()) && (pb.getY() < pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{

			if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return rf; //right-front
			else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return lf; //left-front
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{

			if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return rm; //right-middle
			else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 4: x aumenta e y cte
	if ((pb.getX() > pa.getX()) && (pb.getY() == pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() == pb.getY()))
		{

			if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return rf; //right-front
			else if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return lf; //left-front
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() == pb.getY()))
		{

			if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return rm; //right-middle
			else if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else //Tendencia 5: x aumenta e y aumenta
	if ((pb.getX() > pa.getX()) && (pb.getY() > pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{

			if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return rf; //right-front
			else if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return lf; //left-front
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{

			if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return rm; //right-middle
			else if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else //Tendencia 6: x cte e y aumenta
	if ((pb.getX() == pa.getX()) && (pb.getY() > pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() == pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{

			if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() == pb.getY()))
				return rf; //right-front
			else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() == pb.getY()))
				return lf; //left-front
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() == pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{

			if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() == pb.getY()))
				return rm; //right-middle
			else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() == pb.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else //Tendencia 7: x disminuye e y aumenta
	if ((pb.getX() < pa.getX()) && (pb.getY() > pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{

			if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return rf; //right-front
			else if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return lf; //left-front
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{

			if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return rm; //right-middle
			else if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else //Tendencia 8: x disminuye e y cte
	if ((pb.getX() < pa.getX()) && (pb.getY() == pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() == pb.getY()))
		{

			if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return rf; //right-front
			else if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return lf; //left-front
			else
				return none_rel_orientation;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() == pb.getY()))
		{

			if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() < pb.getY()))
				return rm; //right-middle
			else if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() > pb.getY()))
				return lm; //left-middle
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else
		return none_rel_orientation;

}

QRelative_Orientation_Type obtaining_relative_orientation_wrt_rta_a_b(
		Point2D pa, Point2D pb, Point2D pp_a_b)
{

	//cout << "Entramos en wrt rta a_b"<<endl;

	//El pto es b
	if ((pb.getX() == pp_a_b.getX()) && (pb.getY() == pp_a_b.getY()))
		return idf;
	else
	//El pto es a
	if ((pa.getX() == pp_a_b.getX()) && (pa.getY() == pp_a_b.getY()))
		return ib;
	else
	//Tendencia 1: x e y disminuyen
	if ((pb.getX() < pa.getX()) && (pb.getY() < pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{
			return sf;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{
			//Pto delante de a
			if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() < pa.getY()))
			{
				return sm;
			}
			else
			//Pto detrás de a
			if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() > pa.getY()))
			{
				return sb;
			}
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 2: x cte e y disminuye
	if ((pb.getX() == pa.getX()) && (pb.getY() < pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() == pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{
			return sf;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() == pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{
			//Pto delante de a
			if ((pp_a_b.getX() == pa.getX()) && (pp_a_b.getY() < pa.getY()))
			{
				return sm;
			}
			else
			//Pto detrás de a
			if ((pp_a_b.getX() == pa.getX()) && (pp_a_b.getY() > pa.getY()))
			{
				return sb;
			}
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 3: x aumenta e y disminuye
	if ((pb.getX() > pa.getX()) && (pb.getY() < pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{
			return sf;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{
			//Pto delante de a
			if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() < pa.getY()))
			{
				return sm;
			}
			else
			//Pto detrás de a
			if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() > pa.getY()))
			{
				return sb;
			}
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 4: x aumenta e y cte
	if ((pb.getX() > pa.getX()) && (pb.getY() == pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() == pb.getY()))
		{
			return sf;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() == pb.getY()))
		{
			//Pto delante de a
			if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() == pa.getY()))
			{
				return sm;
			}
			else
			//Pto detrás de a
			if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() == pa.getY()))
			{
				return sb;
			}
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 5: x aumenta e y aumenta
	if ((pb.getX() > pa.getX()) && (pb.getY() > pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{
			return sf;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{
			//Pto delante de a
			if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() > pa.getY()))
			{
				return sm;
			}
			else
			//Pto detrás de a
			if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() < pa.getY()))
			{
				return sb;
			}
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 6: x cte e y aumenta
	if ((pb.getX() == pa.getX()) && (pb.getY() > pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() == pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{
			return sf;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() == pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{
			//Pto delante de a
			if ((pp_a_b.getX() == pa.getX()) && (pp_a_b.getY() > pa.getY()))
			{
				return sm;
			}
			else
			//Pto detrás de a
			if ((pp_a_b.getX() == pa.getX()) && (pp_a_b.getY() < pa.getY()))
			{
				return sb;
			}
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 7: x disminuye e y aumenta
	if ((pb.getX() < pa.getX()) && (pb.getY() > pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() > pb.getY()))
		{
			return sf;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() < pb.getY()))
		{
			//Pto delante de a
			if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() > pa.getY()))
			{
				return sm;
			}
			else
			//Pto detrás de a
			if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() < pa.getY()))
			{
				return sb;
			}
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;

	}
	else //Tendencia 8: x disminuye e y cte
	if ((pb.getX() < pa.getX()) && (pb.getY() == pa.getY()))
	{

		//Pto delante de b
		if ((pp_a_b.getX() < pb.getX()) && (pp_a_b.getY() == pb.getY()))
		{
			return sf;
		}
		else
		//Pto detras de b
		if ((pp_a_b.getX() > pb.getX()) && (pp_a_b.getY() == pb.getY()))
		{
			//Pto delante de a
			if ((pp_a_b.getX() < pa.getX()) && (pp_a_b.getY() == pa.getY()))
			{
				return sm;
			}
			else
			//Pto detrás de a
			if ((pp_a_b.getX() > pa.getX()) && (pp_a_b.getY() == pa.getY()))
			{
				return sb;
			}
			else
				return none_rel_orientation;
		}
		else
			return none_rel_orientation;
	}
	else
		return none_rel_orientation;

}

QRelative_Orientation_Type obtaining_relative_orientation_wrt_rta_x_a(
		Point2D pa, Point2D pb, Point2D pp_x_a)
{

	//cout << "Entramos en wrt rta x_a"<<endl;

	//Tendencia 1: x e y disminuyen
	if ((pb.getX() < pa.getX()) && (pb.getY() < pa.getY()))
	{

		if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() < pa.getY()))
			return ibr; //identity-back-right
		else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() > pa.getY()))
			return ibl; //identity-back-left
		else
			return none_rel_orientation;

	}
	else //Tendencia 2: x cte e y disminuye
	if ((pb.getX() == pa.getX()) && (pb.getY() < pa.getY()))
	{

		if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() == pa.getY()))
			return ibr; //identity-back-right
		else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() == pa.getY()))
			return ibl; //identity-back-left
		else
			return none_rel_orientation;

	}
	else //Tendencia 3: x aumenta e y disminuye
	if ((pb.getX() > pa.getX()) && (pb.getY() < pa.getY()))
	{

		if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() > pa.getY()))
			return ibr; //identity-back-right
		else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() < pa.getY()))
			return ibl; //identity-back-left
		else
			return none_rel_orientation;

	}
	else //Tendencia 4: x aumenta e y cte
	if ((pb.getX() > pa.getX()) && (pb.getY() == pa.getY()))
	{

		if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() > pa.getY()))
			return ibr; //identity-back-right
		else if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() < pa.getY()))
			return ibl; //identity-back-left
		else
			return none_rel_orientation;

	}
	else //Tendencia 5: x aumenta e y aumenta
	if ((pb.getX() > pa.getX()) && (pb.getY() > pa.getY()))
	{

		if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() > pa.getY()))
			return ibr; //identity-back-right
		else if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() < pa.getY()))
			return ibl; //identity-back-left
		else
			return none_rel_orientation;
	}
	else //Tendencia 6: x cte e y aumenta
	if ((pb.getX() == pa.getX()) && (pb.getY() > pa.getY()))
	{

		if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() == pa.getY()))
			return ibr; //identity-back-right
		else if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() == pa.getY()))
			return ibl; //identity-back-left
		else
			return none_rel_orientation;
	}
	else //Tendencia 7: x disminuye e y aumenta
	if ((pb.getX() < pa.getX()) && (pb.getY() > pa.getY()))
	{

		if ((pp_x_a.getX() < pa.getX()) && (pp_x_a.getY() < pa.getY()))
			return ibr; //identity-back-right
		else if ((pp_x_a.getX() > pa.getX()) && (pp_x_a.getY() > pa.getY()))
			return ibl; //identity-back-left
		else
			return none_rel_orientation;
	}
	else //Tendencia 8: x disminuye e y cte
	if ((pb.getX() < pa.getX()) && (pb.getY() == pa.getY()))
	{

		if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() < pa.getY()))
			return ibr; //identity-back-right
		else if ((pp_x_a.getX() == pa.getX()) && (pp_x_a.getY() > pa.getY()))
			return ibl; //identity-back-left
		else
			return none_rel_orientation;

	}
	else
		return none_rel_orientation;

}

QRelative_Orientation_Type obtaining_relative_orientation_wrt_rta_x_b(
		Point2D pa, Point2D pb, Point2D pp_x_b)
{

	//cout << "Entramos en wrt rta x_b"<<endl;

	//Tendencia 1: x e y disminuyen
	if ((pb.getX() < pa.getX()) && (pb.getY() < pa.getY()))
	{

		if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() < pb.getY()))
			return r; //right
		else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() > pb.getY()))
			return l; //left
		else
			return none_rel_orientation;

	}
	else //Tendencia 2: x cte e y disminuye
	if ((pb.getX() == pa.getX()) && (pb.getY() < pa.getY()))
	{

		if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() == pb.getY()))
			return r; //right
		else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() == pb.getY()))
			return l; //left
		else
			return none_rel_orientation;

	}
	else //Tendencia 3: x aumenta e y disminuye
	if ((pb.getX() > pa.getX()) && (pb.getY() < pa.getY()))
	{

		if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() > pb.getY()))
			return r; //right
		else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() < pb.getY()))
			return l; //left
		else
			return none_rel_orientation;

	}
	else //Tendencia 4: x aumenta e y cte
	if ((pb.getX() > pa.getX()) && (pb.getY() == pa.getY()))
	{

		if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() > pb.getY()))
			return r; //right
		else if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() < pb.getY()))
			return l; //left
		else
			return none_rel_orientation;

	}
	else //Tendencia 5: x aumenta e y aumenta
	if ((pb.getX() > pa.getX()) && (pb.getY() > pa.getY()))
	{

		if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() > pb.getY()))
			return r; //right
		else if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() < pb.getY()))
			return l; //left
		else
			return none_rel_orientation;

	}
	else //Tendencia 6: x cte e y aumenta
	if ((pb.getX() == pa.getX()) && (pb.getY() > pa.getY()))
	{

		if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() == pb.getY()))
			return r; //right
		else if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() == pb.getY()))
			return l; //left
		else
			return none_rel_orientation;

	}
	else //Tendencia 7: x disminuye e y aumenta
	if ((pb.getX() < pa.getX()) && (pb.getY() > pa.getY()))
	{

		if ((pp_x_b.getX() < pb.getX()) && (pp_x_b.getY() < pb.getY()))
			return r; //right
		else if ((pp_x_b.getX() > pb.getX()) && (pp_x_b.getY() > pb.getY()))
			return l; //left
		else
			return none_rel_orientation;

	}
	else //Tendencia 8: x disminuye e y cte
	if ((pb.getX() < pa.getX()) && (pb.getY() == pa.getY()))
	{

		if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() < pb.getY()))
			return r; //right
		else if ((pp_x_b.getX() == pb.getX()) && (pp_x_b.getY() > pb.getY()))
			return l; //left
		else
			return none_rel_orientation;
	}
	else
		return none_rel_orientation;

}

QRelative_Orientation_Type Image::obtaining_relative_orientation_of_a_vertex(
		Point2D vertex, Point2D fig_a_centroid, Point2D fig_b_centroid)
{

	int pto_in_rta_a_b, pto_in_rta_x_a, pto_in_rta_x_b = 0;
	float dist_pto_rta_a_b, dist_pto_rta_x_a, dist_pto_rta_x_b = 0.0;

	//Proyecciones vértice en las rectas a_b, perpendicular a a_b y que pasa x a, perpendicular a a_b y que pasa por b
	Point2D pp_a_b, pp_x_a, pp_x_b;
	QRelative_Orientation_Type relOrient;

	pto_in_rta_a_b = vertex_in_rta_a_b(vertex, fig_a_centroid, fig_b_centroid);
	pto_in_rta_x_a = vertex_in_rta_x_a(vertex, fig_a_centroid, fig_b_centroid);
	pto_in_rta_x_b = vertex_in_rta_x_b(vertex, fig_a_centroid, fig_b_centroid);

	if ((!pto_in_rta_a_b) && (!pto_in_rta_x_a) && (!pto_in_rta_x_b))
	{

		pp_a_b = obtaining_proyeccion_pto_rta_a_b(vertex, fig_a_centroid,
				fig_b_centroid, &dist_pto_rta_a_b);
		//cout << "a [" << pp_a_b.getX() << ", "<< pp_a_b.getY() <<"] " << "dist= " << dist_pto_rta_a_b << endl;

		pp_x_a = obtaining_proyeccion_pto_rta_x_a(vertex, fig_a_centroid,
				fig_b_centroid, &dist_pto_rta_x_a);
		//cout << "a [" << pp_x_a.getX() << ", "<< pp_x_a.getY() <<"] " << "dist= " << dist_pto_rta_x_a << endl;

		pp_x_b = obtaining_proyeccion_pto_rta_x_b(vertex, fig_a_centroid,
				fig_b_centroid, &dist_pto_rta_x_b);
		//cout << "a [" << pp_x_b.getX() << ", "<< pp_x_b.getY() <<"] " << "dist= " << dist_pto_rta_x_b << endl;

		//Nos quedamos siempre con la proyección del pto en la recta a_b, pero hemos de elegir la proyección
		//del punto a la recta perpendicular a a_b que esté más cerca de éste (la que pasa x_a o la que pasa x_b)
		if (dist_pto_rta_x_a < dist_pto_rta_x_b)
		{

			relOrient = obtaining_relative_orientation_wrt_cross_A(fig_a_centroid,
					fig_b_centroid, pp_a_b, pp_x_a);

		}
		else
		{
			relOrient = obtaining_relative_orientation_wrt_cross_B(fig_a_centroid,
					fig_b_centroid, pp_a_b, pp_x_b);

		}

	}
	else
	{

		if (pto_in_rta_a_b)
		{
			//cout << "Pto in rta a_b"<<endl;
			relOrient = obtaining_relative_orientation_wrt_rta_a_b(fig_a_centroid,
					fig_b_centroid, vertex);
		}
		else if (pto_in_rta_x_a)
		{
			//cout << "Pto in rta perpendicular a a_b y que pasa por a"<<endl;
			relOrient = obtaining_relative_orientation_wrt_rta_x_a(fig_a_centroid,
					fig_b_centroid, vertex);
		}
		else if (pto_in_rta_x_b)
		{
			//cout << "Pto in rta perpendicular a a_b y que pasa por b"<<endl;
			relOrient = obtaining_relative_orientation_wrt_rta_x_b(fig_a_centroid,
					fig_b_centroid, vertex);
		}
		else
			relOrient = none_rel_orientation;

	}

	return relOrient;
}

void Image::obtaining_relative_orientation_of_a_figure(unsigned int fig_id,
		unsigned int id_fig_a, unsigned int id_fig_b)
{

	QRelative_Orientation_Type q_rel_orient;
	RelativeOrientation ro;

	ro.rs.set_RS(id_fig_a, id_fig_b);

	//cout << "--- Fig[" << fig_id << "]" <<endl;

	for (unsigned int id_vertex = 0; id_vertex < figV[fig_id].vertices.size(); id_vertex++)
	{

		//cout << "v" << id_vertex << "[" << figV[fig_id].vertices[id_vertex].getX() <<"," << figV[fig_id].vertices[id_vertex].getY()<< "]: ";

		q_rel_orient = obtaining_relative_orientation_of_a_vertex(
				figV[fig_id].vertices[id_vertex], figV[id_fig_a].centroid,
				figV[id_fig_b].centroid);

		ro.add_RelOrientation(q_rel_orient);
	}

	figV[fig_id].VRelative_Orientations.push_back(ro);

}

void Image::obtaining_all_relative_orientations()
{

	//obtaining_all_RS_in_the_image();

	obtaining_all_RS_in_the_image_without_inverses();

	for (unsigned int rs_id = 0; rs_id < vRS.size(); rs_id++)
	{

		//cout << "#### RS[" << vRS[rs_id].id_fig_a << ", " << vRS[rs_id].id_fig_b << "]: " <<endl;

		for (unsigned int fig_id = 0; fig_id < figV.size(); fig_id++)
		{

			if ((fig_id != vRS[rs_id].id_fig_a) && (fig_id != vRS[rs_id].id_fig_b))
			{

				obtaining_relative_orientation_of_a_figure(fig_id, vRS[rs_id].id_fig_a,
						vRS[rs_id].id_fig_b);

			}

		}

	}

}

void Image::obtaining_all_relative_orientations_wrt_neighbours()
{

	for (unsigned int i = 0; i < figV.size(); i++)
	{

		figV[i].obtaining_all_RS_in_neighboursVector_without_inverses();

		for (unsigned int rs_id = 0; rs_id < figV[i].vneighboursRS.size(); rs_id++)
		{

			cout << "#### RS[" << figV[i].vneighboursRS[rs_id].id_fig_a << ", "
					<< figV[i].vneighboursRS[rs_id].id_fig_b << "]: " << endl;
			obtaining_relative_orientation_of_a_figure(i,
					figV[i].vneighboursRS[rs_id].id_fig_a,
					figV[i].vneighboursRS[rs_id].id_fig_b);

		}
	}
}

void Image::printFile_Qdescription()
{

	ofstream out("imag_Qdesc.txt");

	out << "[IMG, SpatialDescription, \n";

	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{
		out << figV[j].SpatialDescription;
	}

	out << "] \n";

	out << "[IMG, VisualDescription, \n";

	//Para cada figura detectada dentro de una imagen
	for (unsigned int j = 0; j < figV.size(); j++)
	{
		out << figV[j].VisualDescription;
	}

	out << "] \n";

	out.close();
}
