/*******************************************************************/
/*													RECFORMAS						   		             */
/*	 Shape detector, qualitative descriptor and figure matcher  	 */
/*												        						   		           		 */
/*	 Based on the original theory by: Lledó Museros              	 */
/*	 Theory extended by: Zoe Falomir and Jon Almazán             	 */
/*												        						   		           		 */
/*	 Developed by: 		Lledó Museros, Jon Almazán, Zoe Falomir   	 */
/*										and Pablo Rodenas                        		 */
/*												        						   		           		 */
/*	 Version: 2.6.0.1                                              */
/*******************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>

#include "lib/CImg.h"
#include "lib/Image.h"
#include "lib/FiguresExtractor.h"
#include "lib/QualitativeDescriptor.h"
#include "lib/Matching.h"
#include "lib/Similarity.h"

using namespace std;
using namespace cimg_library;

#ifndef DISTANCE
#define DISTANCE(x1, y1, x2, y2) (double) sqrt(pow(x1-x2, 2) + pow(y1-y2, 2))
#endif

int main(int argc, char ** argv)
{
	string text, flag, path, ext;
	int init, m, version, edgesAlgorithm, distest;
	clock_t startFE, finishFE, startQD, finishQD, startDesc, finishDesc, startMatch, finishMatch,
			startDescMap, finishDescMap;
	double FElenght, QDlenght, totalLenght, descLenght, matchLenght, descMapLenght;
	bool testing, matching, orientation, curDetection, opUnion;

	if (argc < 2)
	{
		cerr << "\nInvoking error: Arguments missed\n\nTry: " << argv[0] << " help\n" << endl;
		return -1;
	}

	string temparg = argv[1];
	if (temparg == "help")
	{
		cout << "\nSYNOPSIS\n\t" << argv[0] << " [-ipgmeocfF] [file1 file2 ... fileN]\n" << endl;
		cout << "DESCRIPTION\n\tThe following options are available:\n" << endl;
		cout << "\t-i\tSelect the \"images\" folder. Selected by default." << endl;
		cout << "\t-p\tSelect the \"photos\" folder." << endl;
		cout << "\t-g\tSelece the \"MPEG7_CE\" folder." << endl;
		cout << "\t-m\tEnable the matching process." << endl;
		cout << "\t-e\tEnable the extended version. Enabled by default." << endl;
		cout << "\t-o\tEnable the original version." << endl;
		cout << "\t-c\tEnable the Canny Edge Detection algorithm. Enabled by default." << endl;
		cout << "\t-C\tDesactivate the curves detection." << endl;
		cout << "\t-f\tEnable the Felzenswalb algorithm." << endl;
		cout << "\t-F\tEnable the Felzenswalb algorithm and asks for parameters." << endl;
		cout << "\t-r\tEnable the Orientation Libraries." << endl << endl;
		return 0;
	}

	//Syntax: "<<argv[0]<<" -[Image,Photo] img0 img1 ... imgN\nMatching syntax: "<<argv[0]<<" -[IM,PM] imageMap imgToCompare0 ... imageToCompareN\n"

	// Opciones por defecto
	version = 1;
	path = "";
	matching = false;
	orientation = false;
	init = 1;
	testing = false;
	curDetection = true;
	opUnion = false;
	edgesAlgorithm = 0; //Canny
	distest = 0;

	for (int i = 1; i < argc; i++)
	{
		char c = argv[i][0];
		if (c == '-')
		{
			init = i + 1;
			int j = 1;
			flag = argv[i];

			while (flag[j])
			{
				if (flag[j] == 'i')
					path = "../images/";
				else if (flag[j] == 'p')
					path = "../photos/";
				else if (flag[j] == 't')
					path = "../images/test/";
				else if (flag[j] == 'g')
					path = "../MPEG7_CE/";
				else if (flag[j] == 'm')
					matching = true;
				else if (flag[j] == 'o')
					version = 0;
				else if (flag[j] == 'e')
					version = 1;
				else if (flag[j] == 'x')
					testing = true;
				else if (flag[j] == 'c')
					edgesAlgorithm = 0;
				else if (flag[j] == 'C')
					curDetection = false;
				else if (flag[j] == 'f')
					edgesAlgorithm = 1;
				else if (flag[j] == 'F')
					edgesAlgorithm = 11;
				else if (flag[j] == 'r')
					orientation = true;
				else if (flag[j] == 'u')
					opUnion = true;
				else if (flag[j] == 'd')
					distest = 1;
				else if (flag[j] == 'D')
					distest = 2;
				else
				{
					cerr << "\nInvalid flag: -" << flag[j] << "\n" << endl;
					return -1;
				}
				j++;
			}
		}
		else
			break;
	}

	int numimages = argc - init;

	if (numimages < 2)
	{
		if (matching)
		{
			cerr << "\nMatching invoking error: Not enough images specified\n\nSyntax: " << argv[0]
					<< "-m -[ipgeocfF] imageMap imgToCompare0 ... imageToCompareN\n" << endl;
			return -1;
		}
		else if (numimages == 0)
		{
			cerr << "\nInvoking error: No input images\n\nSyntax: " << argv[0]
					<< " -[ipgmeocfF] image0 ... imageN\n" << endl;
			return -1;
		}
	}

	if (!matching)
	{
		vector<Image> imgV(argc - init);
		FiguresExtractor fe(curDetection);
		QualitativeDescriptor qd;

		//Jorge
		Similarity sim;
		float disimilitud;
		FILE *fichero;

		qd.setVersion(version);
		fe.setEdgeAlgorithm(edgesAlgorithm);

		for (int k = init; k < argc; k++)
		{
			m = k - init;
			text = argv[k];

			if (text.find(".jpg") == string::npos && text.find(".bmp") == string::npos && text.find(
					".JPG") == string::npos && text.find(".BMP") == string::npos && text.find(".gif")
					== string::npos)
				//text += ".jpg";
			//text = path + text;

			try
			{
				CImg<float> sourceImg(text.c_str());
				//Image image(text, sourceImg);
				imgV[m].setSourceImg(text, sourceImg);

				fe.clear();
				fe.setSourceImage(&(imgV[m]));

				/**** Figures Extraction ****/
				startFE = clock();
				fe.Extract();
				finishFE = clock();
				FElenght = (double) (finishFE - startFE);
				/****************************/

				//cout << imgV[m].figV.size() << endl;

				qd.clear();
				qd.setSourceImage(&(imgV[m]));

				//imgV[m].imgRes.display(imgV[m].fResName.c_str());

				/*
				 string resImgFile2 = text;
				 resImgFile2.insert(resImgFile2.size()-4, "_result");
				 imgV[m].fResName = resImgFile2;
				 imgV[m].imgRes.save(resImgFile2.c_str());
				 */

				/**** Qualitative Description ****/
				startQD = clock();

				if (orientation)
				{
					//imgV[m].obtaining_all_slopes_for_each_figure();
					imgV[m].obtaining_topological_relations();
					//imgV[m].obtaining_neighbours_of_all_figures();
					//imgV[m].obtaining_compared_size_wrt_image();
					imgV[m].obtaining_compared_size_wrt_figures();
					//imgV[m].obtaining_compared_size_wrt_neighbours();
					imgV[m].obtaining_fixed_orientation_wrt_image();
					imgV[m].obtaining_fixed_orientation_of_all_vertices();
					//imgV[m].obtaining_fixed_orientation_wrt_figures();
					//imgV[m].obtaining_fixed_orientation_wrt_figures_centroid_version();
					//imgV[m].obtaining_fixed_orientation_wrt_neighbours();
					imgV[m].obtaining_fixed_orientation_wrt_figures_object_centred();
					imgV[m].obtaining_all_relative_orientations(); //Freksa
					//imgV[m].obtaining_all_relative_orientations_wrt_neighbours();
					//imgV[m].obtaining_compared_distances();
				}

				qd.generateDescription(orientation);
				finishQD = clock();
				QDlenght = (double) (finishQD - startQD);
				/*********************************/

				//cout << imgV[m].figV.size() << endl;

				//cout << "Image " << argv[k] << " finished" << endl;

				totalLenght = FElenght + QDlenght;
				

				string resImgFile = text;
				resImgFile.insert(resImgFile.size() - 4, "_result");
				imgV[m].drawID();
				imgV[m].fResName = resImgFile;
					
				imgV[m].imgRes.save(resImgFile.c_str());
			}
			catch (string err)
			{
				cout << err << endl;
				cerr << "ERROR" << endl;
				cerr << err << endl;
				return -1;
			}
		}

		/****************** UNION *****************

		 string opUnion(Figure f1, Figure f2)
		 {
		 Figure f;

		 }


		 /*
		 * La descripcion de todas las figuras ya está hecha
		 */

		/*
		 if (opUnion)
		 opUnion(imgV[0].figV[0], imgV[0].figV[1]);


		 for (int i = 0; i<imgV[0].figV.size(); i++)
		 for (int j = 0; j<imgV[0].figV[i].qualPtV.size(); j++)
		 imgV[0].figV[i].qualPtV[j].angle;
		 */

		/*********************************************/

		//Se muestran todas las imagenes analizadas y la descripcion de las figuras
		for (unsigned int m = 0; m < imgV.size(); m++)
		{
			for (int i = 0; i < imgV[m].figV.size(); i++)
			{
				cout << imgV[m].figV[i];
				//cout<<"\t"<<imgV[m].figV[i].stringDescription()<<endl;
			}
			//imgV[m].imgRes.display(imgV[m].fResName.c_str());
		}

		if (testing)
		{
			Figure * f;
			f = &(imgV[0].figV[0]);
			vector<double> xv(f->border.size());
			//f->setAreaCentroid();
			int x1, x2, xc, yc;
			xc = f->centroid.x;
			yc = f->centroid.y;
			cout << endl;
		}

		//Jorge
		fichero = fopen("file", "w");
		if (distest == 1)
		{

			for (unsigned int i1 = 0; i1 < imgV.size() - 1; i1++)
			{
				for (unsigned int j1 = 0; j1 < imgV[i1].figV.size(); j1++)
				{
					disimilitud = sim.similarity_shape(&(imgV[i1].figV[j1]), &(imgV[i1 + 1].figV[j1]));
					printf("La disimilitud entre la imagen %d y %d es de %.2f\n", i1, i1 + 1, disimilitud);
				}
			}

		}
		else if (distest == 2)
		{
			printf("**********************************\n");
			for (unsigned int i1 = 0; i1 < imgV.size(); i1++)
			{

				printf("**** Comparacion de la imagen %s ****\n", imgV[i1].fName.c_str());
				for (unsigned int j1 = i1; j1 < imgV.size(); j1++)
				{
					printf("\nCon la imagen %s\n", imgV[j1].fName.c_str());

					disimilitud = sim.similarity_shape(&(imgV[i1].figV[1]), &(imgV[j1].figV[1]));
					/*
					 fprintf(fichero, "%s\n", imgV[i1].figV[1].description.c_str());
					 printf("%s\n", imgV[i1].figV[1].description.c_str());
					 fprintf(fichero, "%s\n", imgV[j1].figV[1].description.c_str());
					 printf("%s\n", imgV[j1].figV[1].description.c_str());
					 printf("La disimilitud entre la imagen %s y %s es de %.2f %\n",
					 imgV[i1].fName.c_str(), imgV[j1].fName.c_str(), disimilitud);
					 fprintf(fichero,
					 "La disimilitud entre la imagen %s y %s es de %.2f %\n",
					 imgV[i1].fName.c_str(), imgV[j1].fName.c_str(), disimilitud);
					 */
				}
				printf("\n");
			}

		}
		fclose(fichero);
	}

	else if (matching)
	{
		Image map;
		Matching mch;
		FiguresExtractor fe;
		QualitativeDescriptor qd;

		qd.setVersion(version);
		mch.setVersion(version);
		fe.setEdgeAlgorithm(edgesAlgorithm);

		/*** Se calcula la descripcion cualitativa del mapa ***/
		text = argv[init];

		if (text.find(".jpg") == string::npos && text.find(".bmp") == string::npos && text.find(".JPG")
				== string::npos && text.find(".BMP") == string::npos && text.find(".gif") == string::npos)
			text += ".jpg";
		text = path + text;

		CImg<float> srcImg(text.c_str());
		map.setSourceImg(text, srcImg);

		try
		{
			fe.setSourceImage(&map);
			qd.setSourceImage(&map);

			startDescMap = clock();
			fe.Extract();
			qd.generateDescription();
			finishDescMap = clock();

			map.nfigures = map.figV.size();

			string resImgFile = text;
			resImgFile.insert(resImgFile.size() - 4, "_result");
			map.fResName = resImgFile;
			map.imgRes.save(map.fResName.c_str());
		}
		catch (string err)
		{
			cout << err << endl;
			cerr << "ERROR" << endl;
			cerr << err << endl;
			return -1;
		}
		cout << "Mapa descrito" << endl;

		descMapLenght = (double) (finishDescMap - startDescMap) / (double) CLOCKS_PER_SEC;

		/*** Se calcula la descripcion cualitativa de todas las imagenes a comparar ***/
		init++;
		int nIm = argc - init;
		vector<Image> imgV(nIm);
		descLenght = 0;
		for (int i = 0; i < nIm; i++)
		{
			text = argv[init + i];
			if (text.find(".jpg") == string::npos && text.find(".bmp") == string::npos && text.find(
					".JPG") == string::npos && text.find(".BMP") == string::npos && text.find(".gif")
					== string::npos)
				text += ".jpg";
			text = path + text;
			try
			{
				CImg<float> sourceImg(text.c_str());
				imgV[i].setSourceImg(text, sourceImg);

				fe.clear();
				fe.setSourceImage(&(imgV[i]));
				qd.clear();
				qd.setSourceImage(&(imgV[i]));

				startDesc = clock();
				fe.Extract();
				qd.generateDescription();
				finishDesc = clock();
				descLenght += (double) (finishDesc - startDesc) / (double) CLOCKS_PER_SEC;

				string resImgFile = text;
				resImgFile.insert(resImgFile.size() - 4, "_result");
				imgV[i].fResName = resImgFile;
				imgV[i].drawID();
				imgV[i].imgRes.save(imgV[i].fResName.c_str());
			}
			catch (string err)
			{
				cout << err << endl;
				cerr << "ERROR" << endl;
				cerr << err << endl;
				return -1;
			}
		}

		startMatch = clock();
		/*** Se realiza el proceso de Matching ***/
		mch.setMap(&map);
		int numFound = 0;
		string auxMapName, auxS, auxResName;
		auxMapName = map.fName.substr(map.fName.rfind("/") + 1);

		for (unsigned int i = 0; i < imgV.size(); i++)
		{
			for (unsigned int j = 0; j < imgV[i].figV.size(); j++)
			{
				numFound = mch.qualitativeMatch(&(imgV[i].figV[j]));
				if (!testing)
				{
					if (numFound)
						cout << "Figure(s) matched: " << numFound << endl;
					else
						cout << "Figure not matched" << endl;
				}
			}
			if (testing)
			{
				auxS = imgV[i].fName;
				auxS.erase(auxS.end() - 4, auxS.end());
				auxResName = auxS + "_vs_" + auxMapName;
				mch.drawResult(auxResName);
				mch.clear();
			}
		}
		finishMatch = clock();

		matchLenght = (double) (finishMatch - startMatch) / (double) CLOCKS_PER_SEC;

		totalLenght = descLenght + matchLenght;

		cout << endl << "Total time to detect and describe the figures in the map: " << descMapLenght
				<< endl;
		cout << "Total time to detect and describe the figures to match: " << descLenght << endl;
		cout << "Total time to complete the matching process: " << matchLenght << endl;
		cout << "Total time: " << descMapLenght + descLenght + matchLenght << endl;

	}

	return 0;
}
