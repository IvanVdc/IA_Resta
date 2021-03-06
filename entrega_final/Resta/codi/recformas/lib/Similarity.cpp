//
// Zfalomir & JGrande
//
// Marzo-Abril-Mayo 2009
//

#include "Similarity.h"

Similarity::Similarity()
{
	//Inicializamos las tablas de distancias

	//Para la conexion de bordes
	kind_edges_connected[0][0] = 0;
	kind_edges_connected[0][1] = 1;
	kind_edges_connected[0][2] = 1;
	kind_edges_connected[0][3] = 2;
	kind_edges_connected[0][4] = 3;
	kind_edges_connected[0][5] = 4;

	kind_edges_connected[1][0] = 1;
	kind_edges_connected[1][1] = 0;
	kind_edges_connected[1][2] = 2;
	kind_edges_connected[1][3] = 1;
	kind_edges_connected[1][4] = 2;
	kind_edges_connected[1][5] = 4;

	kind_edges_connected[2][0] = 1;
	kind_edges_connected[2][1] = 2;
	kind_edges_connected[2][2] = 0;
	kind_edges_connected[2][3] = 1;
	kind_edges_connected[2][4] = 2;
	kind_edges_connected[2][5] = 4;

	kind_edges_connected[3][0] = 2;
	kind_edges_connected[3][1] = 1;
	kind_edges_connected[3][2] = 1;
	kind_edges_connected[3][3] = 0;
	kind_edges_connected[3][4] = 1;
	kind_edges_connected[3][5] = 4;

	kind_edges_connected[4][0] = 3;
	kind_edges_connected[4][1] = 2;
	kind_edges_connected[4][2] = 2;
	kind_edges_connected[4][3] = 1;
	kind_edges_connected[4][4] = 0;
	kind_edges_connected[4][5] = 4;

	kind_edges_connected[5][0] = 4;
	kind_edges_connected[5][1] = 4;
	kind_edges_connected[5][2] = 4;
	kind_edges_connected[5][3] = 4;
	kind_edges_connected[5][4] = 4;
	kind_edges_connected[5][5] = 4;

	//Para los angulos
	angle3[0][0] = 0;
	angle3[0][1] = 1;
	angle3[0][2] = 2;
	angle3[0][3] = 3;

	angle3[1][0] = 1;
	angle3[1][1] = 0;
	angle3[1][2] = 1;
	angle3[1][3] = 3;

	angle3[2][0] = 2;
	angle3[2][1] = 1;
	angle3[2][2] = 0;
	angle3[2][3] = 3;

	angle3[3][0] = 3;
	angle3[3][1] = 3;
	angle3[3][2] = 3;
	angle3[3][3] = 3;

	//Para las curvas
	curvature_angle5[0][0] = 0;
	curvature_angle5[0][1] = 1;
	curvature_angle5[0][2] = 2;
	curvature_angle5[0][3] = 3;
	curvature_angle5[0][4] = 4;
	curvature_angle5[0][5] = 5;

	curvature_angle5[1][0] = 1;
	curvature_angle5[1][1] = 0;
	curvature_angle5[1][2] = 1;
	curvature_angle5[1][3] = 2;
	curvature_angle5[1][4] = 3;
	curvature_angle5[1][5] = 5;

	curvature_angle5[2][0] = 2;
	curvature_angle5[2][1] = 1;
	curvature_angle5[2][2] = 0;
	curvature_angle5[2][3] = 1;
	curvature_angle5[2][4] = 2;
	curvature_angle5[2][5] = 5;

	curvature_angle5[3][0] = 3;
	curvature_angle5[3][1] = 2;
	curvature_angle5[3][2] = 1;
	curvature_angle5[3][3] = 0;
	curvature_angle5[3][4] = 1;
	curvature_angle5[3][5] = 5;

	curvature_angle5[4][0] = 4;
	curvature_angle5[4][1] = 3;
	curvature_angle5[4][2] = 2;
	curvature_angle5[4][3] = 1;
	curvature_angle5[4][4] = 0;
	curvature_angle5[4][5] = 5;

	curvature_angle5[5][0] = 5;
	curvature_angle5[5][1] = 5;
	curvature_angle5[5][2] = 5;
	curvature_angle5[5][3] = 5;
	curvature_angle5[5][4] = 5;
	curvature_angle5[5][5] = 5;

	//Longitud
	length[0][0] = 0;
	length[0][1] = 1;
	length[0][2] = 2;
	length[0][3] = 3;
	length[0][4] = 4;
	length[0][5] = 5;
	length[0][6] = 6;
	length[0][7] = 7;

	length[1][0] = 1;
	length[1][1] = 0;
	length[1][2] = 1;
	length[1][3] = 2;
	length[1][4] = 3;
	length[1][5] = 4;
	length[1][6] = 5;
	length[1][7] = 7;

	length[2][0] = 2;
	length[2][1] = 1;
	length[2][2] = 0;
	length[2][3] = 1;
	length[2][4] = 2;
	length[2][5] = 3;
	length[2][6] = 4;
	length[2][7] = 7;

	length[3][0] = 3;
	length[3][1] = 2;
	length[3][2] = 1;
	length[3][3] = 0;
	length[3][4] = 1;
	length[3][5] = 2;
	length[3][6] = 3;
	length[3][7] = 7;

	length[4][0] = 4;
	length[4][1] = 3;
	length[4][2] = 2;
	length[4][3] = 1;
	length[4][4] = 0;
	length[4][5] = 1;
	length[4][6] = 2;
	length[4][7] = 7;

	length[5][0] = 5;
	length[5][1] = 4;
	length[5][2] = 3;
	length[5][3] = 2;
	length[5][4] = 1;
	length[5][5] = 0;
	length[5][6] = 1;
	length[5][7] = 7;

	length[6][0] = 6;
	length[6][1] = 5;
	length[6][2] = 4;
	length[6][3] = 3;
	length[6][4] = 2;
	length[6][5] = 1;
	length[6][6] = 0;
	length[6][7] = 7;

	length[7][0] = 7;
	length[7][1] = 7;
	length[7][2] = 7;
	length[7][3] = 7;
	length[7][4] = 7;
	length[7][5] = 7;
	length[7][6] = 7;
	length[7][7] = 7;

	//Convexidad
	convexity[0][0] = 0;
	convexity[0][1] = 1;
	convexity[0][2] = 2;

	convexity[1][0] = 1;
	convexity[1][1] = 0;
	convexity[1][2] = 2;

	convexity[2][0] = 2;
	convexity[2][1] = 2;
	convexity[2][2] = 2;

}

int Similarity::index(QPoint *p, int option)
{
	int index;

	switch (option)
	{
		case TABLE_KEC:
			switch (p->shape)
			{

				//LINE-LINE
				case 11:
					index = 0;
					break;
					//LINE-CURVE
				case 12:
					index = 1;
					break;
					//POINT_CURVATURE
				case 2:
					index = 2;
					break;
					//CURVE_LINE
				case 21:
					index = 3;
					break;
					//CURVE_CURVE
				case 22:
					index = 4;
					break;
					//EMPTY
				case EMPTY:
					index = 5;
					break;
			}
			break;

		case TABLE_ANGLE_3:
			switch (p->angle)
			{
				//ACUTE_ANGLE
				case -1:
					index = 0;
					break;
					//RIGHT_ANGLE
				case 0:
					index = 1;
					break;
					//OBTUSE_ANGLE
				case 1:
					index = 2;
					break;
					//EMPTY
				case EMPTY:
					index = 3;
					break;
			}
			break;

		case TABLE_CURVATURE_OR_ANGLE_5:
			switch (p->angle)
			{
				//VERY_ACUTE_CURVE
				case -2:
					index = 0;
					break;
					//ACUTE_CURVE
				case -1:
					index = 1;
					break;
					//SEMICIRCULAR_CURVE
				case 0:
					index = 2;
					break;
					//PLANE_CURVE
				case 1:
					index = 3;
					break;
					//VERY_PLANE_CURVE
				case 2:
					index = 4;
					break;
					//EMPTY
				case EMPTY:
					index = 5;
					break;
			}
			break;

		case TABLE_LENGTH:
			switch (p->size)
			{
				//STH_EDGE
				case -3:
					index = 0;
					break;
					//H_EDGE
				case -2:
					index = 1;
					break;
					//LTH_EDGE
				case -1:
					index = 2;
					break;
					//E_EDGE
				case 0:
					index = 3;
					break;
					//STD_EDGE
				case 1:
					index = 4;
					break;
					//D_EDGE
				case 2:
					index = 5;
					break;
					//LTD_EDGE
				case 3:
					index = 6;
					break;
					//EMPTY
				case EMPTY:
					index = 7;
					break;
			}
			break;

		case TABLE_CONVEXITY:
			switch (p->convexity)
			{
				//CONCAVE
				case 0:
					index = 0;
					break;
					//CONVEX
				case 1:
					index = 1;
					break;
					//EMPTY
				case EMPTY:
					index = 2;
					break;
			}
			break;
	}
	return index;
}

float Similarity::dissimilarity_between_points(QPoint qpt1, QPoint qpt2,
		float *dist_points, float *dist_angle_curvature, float *dist_length,
		float *dist_convexity)
{

	int index1 = 0, index2 = 0;
	//float dist_points = 0.0, dist_angle_curvature = 0.0, dist_length = 0.0, dist_convexity = 0.0;
	float disimilarity_vertex = 0.0;

	//Calculamos las distancias de los puntos en la tabla KEC
	index1 = index(&qpt1, TABLE_KEC);
	index2 = index(&qpt2, TABLE_KEC);
	*dist_points = kind_edges_connected[index1][index2];

	//Calculamos la distancia entre los angulos
	index1 = index(&qpt1, TABLE_CURVATURE_OR_ANGLE_5);
	index2 = index(&qpt2, TABLE_CURVATURE_OR_ANGLE_5);
	*dist_angle_curvature = curvature_angle5[index1][index2];

	//Calculamos las distancias de los puntos
	index1 = index(&qpt1, TABLE_LENGTH);
	index2 = index(&qpt2, TABLE_LENGTH);
	*dist_length = length[index1][index2];

	//Calculamos la convexidad
	index1 = index(&qpt1, TABLE_CONVEXITY);
	index2 = index(&qpt2, TABLE_CONVEXITY);
	*dist_convexity = convexity[index1][index2];

	//Calculamos la distancia teniendo en cuenta todas las propiedades de la forma
	disimilarity_vertex = (PESO_KEC * (100 / MAX_DIST_KEC) * (*dist_points))
			+ (PESO_A_OR_TC * (100 / MAX_DIST_A_OR_TC) * (*dist_angle_curvature))
			+ (PESO_L * (100 / MAX_DIST_L) * (*dist_length)) + (PESO_C * (100
			/ MAX_DIST_C) * (*dist_convexity));

	return disimilarity_vertex;

}

float Similarity::dissimilarity_between_points_v2(QPoint qpt1, QPoint qpt2,
		float *dist_points, float *dist_angle_curvature, float *dist_length,
		float *dist_convexity)
{

	int index1 = 0, index2 = 0;
	//float dist_points = 0.0, dist_angle_curvature = 0.0, dist_length = 0.0, dist_convexity = 0.0;
	float disimilarity_vertex = 0.0;

	//Calculamos las distancias de los puntos en la tabla KEC
	index1 = index(&qpt1, TABLE_KEC);
	index2 = index(&qpt2, TABLE_KEC);
	*dist_points = kind_edges_connected[index1][index2];

	//Calculamos la distancia entre los angulos
	index1 = index(&qpt1, TABLE_CURVATURE_OR_ANGLE_5);
	index2 = index(&qpt2, TABLE_CURVATURE_OR_ANGLE_5);
	*dist_angle_curvature = curvature_angle5[index1][index2];

	//Calculamos las distancias de los puntos
	index1 = index(&qpt1, TABLE_LENGTH);
	index2 = index(&qpt2, TABLE_LENGTH);
	*dist_length = length[index1][index2];

	//Calculamos la convexidad
	index1 = index(&qpt1, TABLE_CONVEXITY);
	index2 = index(&qpt2, TABLE_CONVEXITY);
	*dist_convexity = convexity[index1][index2];

	//Calculamos la distancia teniendo en cuenta todas las propiedades de la forma
	disimilarity_vertex = ((100 / MAX_DIST_A_OR_TC) * (*dist_angle_curvature)
			+ (100 / MAX_DIST_C) * (*dist_convexity)) / 2;

	//disimilarity_vertex = (100/ MAX_DIST_C) * (*dist_convexity);

	return disimilarity_vertex;

}

float Similarity::similarity_shape(Figure *fig1, Figure *fig2)
{
	int vertice_fig2, figTemp2;
	float dist_points, dist_angle_curvature, dist_length, dist_convexity,
			disimilarity, disimilarity_vertex;
	int Qsimilar_vert;
	int nvert1, nvert2;
	float finalDisimilarity = 101.0;
	vector<int> vTemp;
	Figure * f1;
	Figure * f2;
	int dif;

	if (fig1->nqpts >= fig2->nqpts)
	{
		f1 = fig1;
		f2 = fig2;
	}
	else
	{
		f1 = fig2;
		f2 = fig1;
	}

	nvert1 = f1->nqpts;
	nvert2 = f2->nqpts;
	dif = nvert1 - nvert2;

	/*
	 * Caso en que las figuras no tienen el mismo numero de vertices
	 * Se utiliza un vector v donde se encuentran los indices de la figura
	 * con mayor numero de vertices que se van a comparar con el punto vacio.
	 * Estos indices se actualizan hasta contemplar todas las combinaciones.
	 */
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
			/*
			 * Comparamos f1 con todas las posiciones de f2 pero siempre comparando
			 * los indices que hay en v de f1 con un QPoint EMPTY
			 */

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

				for (int i = 0; i < nvert1; i++)
				{
					//cout<<i<<" "<<k<<endl;
					//Nos guardamos los indices por donde empezamos a mirar la figura
					//if (i == 0)
					//	vertice_fig2 = j;

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
						disimilarity_vertex = dissimilarity_between_points(f1->qualPtV[i],
								f2->qualPtV[k], &dist_points, &dist_angle_curvature,
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
				/*
				 printf("---------------------------------------------\n");
				 printf("Shape comparison starting (fig1: %d, fig2: %d)\n", 0,
				 vertice_fig2);
				 printf("disimilarity_acumulated: %.2f, disimilarity_final: %.2f\n",
				 disimilarity, (disimilarity / nvert1));
				 printf("Qequal_vertices: %d from %d \n\n", Qsimilar_vert, nvert1);
				 */

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


			/*
			 cout << "Comparacion realizada con EMPTYs en: ";
			 for (int i = 0; i < v.size(); i++)
			 cout << v[i] << " ";
			 cout << endl;
			 */

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

			//Recorremos todos los vertices de las dos imagenes
			for (int i = 0; i < nvert1; i++)
			{
				j = (i + k) % nvert1;

				//Nos guardamos los indices por donde empezamos a mirar la figura
				if (i == 0)
					vertice_fig2 = j;

				disimilarity_vertex = dissimilarity_between_points(f1->qualPtV[i],
						f2->qualPtV[j], &dist_points, &dist_angle_curvature, &dist_length,
						&dist_convexity);

				if (disimilarity_vertex == 0.0)
				{
					Qsimilar_vert = Qsimilar_vert + 1;
				}

				disimilarity = disimilarity + disimilarity_vertex;

				/*
				 printf("%d - %d: ", i, j);
				 printf(
				 "p:%.2f\t a_c:%.2f\t l:%.2f\t c: %.2f\t dis_point: %.2f\t dis_total: %.2f\n",
				 dist_points, dist_angle_curvature, dist_length, dist_convexity,
				 disimilarity_vertex, disimilarity);
				 */
			}

			/*
			 printf("---------------------------------------------\n");
			 printf("Shape comparison starting (fig1: %d, fig2: %d)\n", 0,
			 vertice_fig2);
			 printf("disimilarity_acumulated: %.2f, disimilarity_final: %.2f\n",
			 disimilarity, (disimilarity / nvert1));
			 printf("Qequal_vertices: %d from %d \n\n", Qsimilar_vert, nvert1);
			 */

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

	cout << "Diferencia de vertices: " << dif << endl;
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

	return finalDisimilarity;
}

int Similarity::minimum_of_3_distances(int value1, int value2, int value3)
{

	if ((value1 <= value2) && (value1 <= value3))
		return value1;
	else if ((value2 <= value1) && (value2 <= value3))
		return value2;
	else
		//if ((value3 <= value1) && (value3 <= value2))
		return value3;

}

float Similarity::Levenshtein_distance(Figure *f1, Figure *f2)
{

	int cost = 0, minimum = 0, k = 1, j_figura = 0;
	int deletion_distance = 0, insertion_distance = 0, substitution_distance = 0,
			LDistance = 0.0;
	int num_insertions = 0, num_deletions = 0, num_substitutions = 0;
	float dist_points, dist_angle_curvature, dist_length, dist_convexity,
			disimilarity_vertex;

	int nvert1 = f1->qualPtV.size();
	int nvert2 = f2->qualPtV.size();

	vector<vector<int> > LMatrix(nvert1 + 1, vector<int> (nvert2 + 1));

	//Inicializamos la primiera fila
	for (int i = 0; i < nvert1 + 1; i++)
	{
		LMatrix[i][0] = i;
	}

	//Inicializamos la primera columna
	for (int j = 0; j < nvert2 + 1; j++)
	{
		LMatrix[0][j] = j;
	}

	while (k <= nvert1)
	{
		//Consideramos el número de filas mayor que el de columnas
		//Sino, deberíamos cambiarlo
		dist_points = 0.0;
		dist_angle_curvature = 0.0;
		dist_length = 0.0;
		dist_convexity = 0.0;
		disimilarity_vertex = 0.0;

		for (int i = 1; i < nvert1 + 1; i++)
		{

			num_substitutions = 0;
			num_insertions = 0;
			num_deletions = 0;

			j_figura = ((i - 1) + k) % (nvert2);
			printf("Figura  i:%d, j: %d\n", i - 1, j_figura);

			for (int j = 1; j < nvert2 + 1; j++)
			{

				disimilarity_vertex = dissimilarity_between_points(f1->qualPtV[i - 1],
						f2->qualPtV[j_figura], &dist_points, &dist_angle_curvature,
						&dist_length, &dist_convexity);

				if (disimilarity_vertex == 0.0)
					cost = 0;
				else
					cost = 1;

				deletion_distance = LMatrix[i - 1][j] + 1; //Coste de la casilla de arriba en la matriz + 1
				insertion_distance = LMatrix[i][j - 1] + 1; //Coste de la casilla de la izquierda en la matriz + 1
				substitution_distance = LMatrix[i - 1][j - 1] + cost; //Coste de la casilla diagonal arriba de la matriz + coste transformación

				minimum = minimum_of_3_distances(deletion_distance, insertion_distance,
						substitution_distance);

				LMatrix[i][j] = minimum;

				//if ((cost > 0) && ((i == j)||(i == nvert1)||(j == nvert2))){ //puntos no similares
				if (cost > 0)
				{ //puntos no similares
					if (minimum == insertion_distance)
						num_insertions++;
					else if (minimum == deletion_distance)
						num_deletions++;
					else
						num_substitutions++;
				}

			}
			//printf (" %d inserciones, %d borrados, %d sustituciones\n", num_insertions, num_deletions, num_substitutions);
		}

		for (int i = 0; i < nvert1 + 1; i++)
		{
			for (int j = 0; j < nvert2 + 1; j++)
			{
				printf("%d \t", LMatrix[i][j]);
			}
			printf("\n");
		}

		LDistance = LMatrix[nvert1][nvert2];
		printf("La distancia de Levenshtein es: %d \n", LDistance);

		k++;

	}

	//LMatrix.clear();

	//Esto modificarlo
	return LDistance;

}

void Similarity::aligment_matrix(Figure *f1, Figure *f2)
{

	int cost = 0, k = 1, j_figura = 0;
	float dist_points, dist_angle_curvature, dist_length, dist_convexity,
			disimilarity_vertex;

	int nvert1 = f1->qualPtV.size();
	int nvert2 = f2->qualPtV.size();

	vector<vector<int> > LMatrix(nvert1, vector<int> (nvert2));

	while (k <= nvert1)
	{
		//Consideramos el número de filas mayor que el de columnas
		//Sino, deberíamos cambiarlo
		dist_points = 0.0;
		dist_angle_curvature = 0.0;
		dist_length = 0.0;
		dist_convexity = 0.0;
		disimilarity_vertex = 0.0;

		for (int i = 0; i < nvert1; i++)
		{

			j_figura = (i + k) % (nvert2);
			printf("Figura  i:%d, j: %d\n", i, j_figura);

			for (int j = 0; j < nvert2; j++)
			{

				disimilarity_vertex = dissimilarity_between_points(f1->qualPtV[i],
						f2->qualPtV[j_figura], &dist_points, &dist_angle_curvature,
						&dist_length, &dist_convexity);

				if (disimilarity_vertex == 0.0)
					cost = 0;
				else
					cost = 1;

				LMatrix[i][j] = cost;

			}
			//printf (" %d inserciones, %d borrados, %d sustituciones\n", num_insertions, num_deletions, num_substitutions);
		}

		printf("Matriz de correspondencias:\n");
		for (int i = 0; i < nvert1; i++)
		{
			for (int j = 0; j < nvert2; j++)
			{
				printf("%d \t", LMatrix[i][j]);
			}
			printf("\n");
		}

		k++;

	}

	//LMatrix.clear();

}

