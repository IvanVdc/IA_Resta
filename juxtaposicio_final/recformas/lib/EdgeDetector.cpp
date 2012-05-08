#include "EdgeDetector.h"

//struct colorComp {
//  bool operator() (const rgb& c1, const rgb& c2) const
//  {return c1<c2;}
//};


EdgeDetector::EdgeDetector(void)
{
  sigma = 1.5;
	threshold = 7.0;
  support = (int)(3.0*sigma+0.5);
}

void EdgeDetector::clear(void)
{
  //borderPts.clear();
  in = NULL;
  inGS.clear();
  out.clear();
  outS.clear();
  outG.clear();
  outO.clear();
  outT.clear();
  outNMS.clear();
}

void EdgeDetector::setSrcImg(CImg<float> * srcImg)
{
  in = srcImg;
	wdt = in->dimx();
	hgt = in->dimy();
	if ( wdt == 0 || hgt == 0 ) {
		cerr << "Error when loading input image." << endl;
	}

}

int EdgeDetector::Canny(vector<Point2D> * borderPts)
{
	string outfileS = "smooth.jpg";			// gaussian smoothed image
	string outfileG = "gradient.jpg";		// gradient image
	string outfileO = "orientation.jpg";		// orientation map
	string outfileT = "threshold.jpg";		// image after thresholding
	string outfileNMS = "canny_result.jpg";	// image after non-max-suppression

  inGS = in->get_pointwise_norm(1)/(float)in->dimv(); //Ensure greyscale image
  outS = inGS; //Copy "in" size
  outG = inGS;
  outO = inGS;
  outT = inGS;
  outNMS = inGS;
  outS.fill(0.0f);
  outG.fill(0.0f);
  outO.fill(0.0f);
  outT.fill(0.0f);
  outNMS.fill(0.0f);

	CannyDiscrete(borderPts);

  out = outNMS; //Final result of Canny Algorithm

	//outS.save(outfileS.c_str());
	//outG.save(outfileG.c_str());
	//outO.save(outfileO.c_str());
	//outT.save(outfileT.c_str());
	outNMS.save(outfileNMS.c_str());

  //***** display output images ******//
//	char  header[100];
//	sprintf(header, "Gaussian smoothed image: sigma = %f", sigma);
//	outS.display(header);
//	sprintf(header, "Gradient image");
//	outG.display(header);
//	sprintf(header, "Orientation map");
//	outO.display(header);
//	sprintf(header, "Image after thresholding: threshold = %f", threshold);
//	outT.display(header);
//	sprintf(header, "Image after non-max-suppression (final)");
//  outNMS.display(header);

	return 0; //Todo correcto
}

void EdgeDetector::CannyDiscrete(vector<Point2D> * borderPts)
{
  const int nx = wdt;
  const int ny = hgt;

  GaussianSmoothing(); // --> OutS
  //outS.display("OutS");

	CImg<float> derivative[4];
	CImg<float> gradient_noscale(inGS);
	CImg<int>   dirmax(wdt, hgt); // direction of max derivative
	gradient_noscale.fill(0.0);
	float angle, max_gradient = 0.0;
	float fct = 1.0 / (2.0*M_SQRT2);

	for(int i = 0; i < 4; i++)
	{
		derivative[i] = CImg<float> (inGS);
		derivative[i].fill(0.0);
	}

	max_gradient = 0.0;
	for (int y = support+1; y < ny-support-1; y++) {
		for(int x = support+1; x < nx-support-1; x++) {
			//***** directional derivatives ****//
			derivative[0](x,y) = (outS(x-1,y  ) - outS(x+1,y  ))*0.5; // E
			derivative[1](x,y) = (outS(x-1,y-1) - outS(x+1,y+1))*fct; // NE
			derivative[2](x,y) = (outS(x,  y-1) - outS(x,  y+1))*0.5; // N
			derivative[3](x,y) = (outS(x+1,y-1) - outS(x-1,y+1))*fct; // SE

			//***** gradient magnitude *********//
			gradient_noscale(x,y) = hypot(derivative[0](x,y),derivative[2](x,y));
			if (gradient_noscale(x,y) > max_gradient) max_gradient = gradient_noscale(x,y);

			//***** gradient orientation *******//
			angle = (gradient_noscale(x,y) == 0.0) ? 0.0 : atan2(derivative[2](x,y), derivative[0](x,y));
			if (angle < 0.0) angle += M_PI;
			outO(x,y) = angle*255.0/M_PI + 0.5; // -> outOrientation

			//***** absolute derivations *******//
			derivative[0](x,y) = fabs(derivative[0](x,y));
			derivative[1](x,y) = fabs(derivative[1](x,y));
			derivative[2](x,y) = fabs(derivative[2](x,y));
			derivative[3](x,y) = fabs(derivative[3](x,y));

			//***** direction of max derivative //
			if      (derivative[0](x,y)>derivative[1](x,y) && derivative[0](x,y)>derivative[2](x,y) && derivative[0](x,y)>derivative[3](x,y))
				dirmax(x,y) = 0; // E
			else if (derivative[1](x,y)>derivative[2](x,y) && derivative[1](x,y)>derivative[3](x,y))
				dirmax(x,y) = 1; // NE
			else if (derivative[2](x,y)>derivative[3](x,y))
				dirmax(x,y) = 2; // N
			else
				dirmax(x,y) = 3; // SE
		}
	}

	//***** scale gradients ************//
	float scale = (max_gradient > 0.0) ? 255.0/max_gradient : 0.0;

	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
		{
			outG(x,y) = gradient_noscale(x,y) * scale;// -> outGradient
			//cout << outGradient(x,y)<<endl;
		}

	//***** thresholding and non-max-supression *//
	int dir;	// direction of max derivative
	int dir1, dir2; // directions of max derivative of neighbouring in the direction 'dir' pixels
	int dir_vector[4][2] = {{1,0}, {1,1}, {0,1}, {-1,1}};	// directing vectors (E, NE, N, SE)

	for (int y = support+2; y < ny-support-2; y++) {
		for (int x = support+2; x < nx-support-2; x++) {
			dir = dirmax(x,y);
			if (derivative[dir](x,y) < threshold) {
				outT(x,y) = 0.0f;
				outNMS(x,y) = 0.0f;
			}
			else {
				outT(x,y) = 255.0f;
				dir1 = dirmax(x + dir_vector[dir][0],y + dir_vector[dir][1]);
				dir2 = dirmax(x - dir_vector[dir][0],y - dir_vector[dir][1]);
				outNMS(x,y) = ((derivative[dir](x,y) >  derivative[dir1](x + dir_vector[dir][0],y + dir_vector[dir][1]) && derivative[dir](x,y) >= derivative[dir2](x - dir_vector[dir][0],y - dir_vector[dir][1]))) ? 255.0f : 0.0f;
			}
      if (outNMS.atXY(x,y) == 255.0f) {
        borderPts->push_back(Point2D (x,y));
      }
      // -> outThreshold, outNMS
      //(outNMS(x, y) > 0) ? cout << "*" : cout << 0;
		}
    //cout << endl;
	} // for x, y...

} // CannyDiscrete


void EdgeDetector::GaussianSmoothing(void)
{
 	CImg<float> derivative(inGS);
	derivative.fill(0.0);
	float mask[support+1];
	float sum = 1.0;
  const int nx = wdt;
  const int ny = hgt;

	//***** init 1D filter mask ********//
	float scale = 1.0/(2.0*sigma*sigma);
	mask[0] = 1.0;
	for (int i = 1; i <= support; i++) {
		mask[i] = exp(-i*i*scale);
		sum += 2.0*mask[i];
	}

	//***** normalize mask *************//
	for (int i = 0; i <= support; i++) {
		mask[i] /= sum;
	}

	//***** column filter **************//
	for (int y = support; y < ny-support; y++) {
		for (int x = 0; x < nx; x++) {
			sum = mask[0] * inGS(x,y);
			for (int i = 1; i <= support; i++) {
				sum += mask[i] * (inGS(x,y-i) + inGS(x,y+i));
			}
			derivative(x,y) = sum;
		}
	}

	//***** row filter *****************//
	for (int y = support; y < ny-support; y++) {
		for (int x = support; x < nx-support; x++) {
			sum = mask[0] * derivative(x,y);
			for (int i = 1; i <= support; i++) {
				sum += mask[i] * (derivative(x-i,y) + derivative(x+i,y));
			}
			outS(x,y) = sum;
		}
	}
}

int EdgeDetector::Felzenswalb(float sigma, int k, int min, vector<vector<Point2D> > * v)
{
  char * filename = (char *) "img_tmp.ppm";
  in->save_pnm(filename);

  int num_ccs;

  //cout << "Loading PPM image..." << endl;
  image<rgb> * input = loadPPM(filename);
  image<rgb> * output;
  //cout << "Starting segmentation process..." << endl;
  output = segment_image(input, sigma, k, min, &num_ccs);
  //cout << "Segmentation finished\t" << num_ccs << " parts segmentated"<<endl;
  savePPM(output, filename);
  findBorders(output, v);
  //cout << "borderPts maked" << endl;

  return 0; //Todo correcto
}

void EdgeDetector::findBorders(image<rgb> *img, vector<vector<Point2D> > * v)
{
	int w = img->width();
	int h = img->height();
  image<rgb> * result = new image<rgb>(w, h);
  rgb curCol;
  curCol.r = 0; curCol.g = 0; curCol.b = 0;
  result->init(curCol);

  map<rgb, int> m;
  map<rgb, int>::iterator pos;
  int index, count;

  for (int y = 0; y < h; y++)
  {
  	for (int x = 0; x < w; x++)
  	{
	  	curCol = imRef(img, x, y);
  		if (x == 0 || y == 0 || x == w-1 || y == h-1)
  		{
  			imRef(result, x, y).r = curCol.r;
				imRef(result, x, y).g = curCol.g;
				imRef(result, x, y).b = curCol.b;

				pos = m.find(curCol);
				if (pos != m.end())
				{
					index = pos->second;
					(*v)[index].push_back(Point2D (x,y));
				}
				else
				{
					index = m.size();
					m[curCol] = index;
					v->push_back(vector<Point2D> (1, Point2D(x,y)));
				}
  		}
  		else if (curCol != imRef(img,x-1,y) || curCol != imRef(img,x+1,y) || curCol != imRef(img,x,y-1) || curCol != imRef(img,x,y+1)) // || curCol != imRef(img,x-1,y-1) || curCol != imRef(img,x+1,y+1) || curCol != imRef(img,x+1,y-1) || curCol != imRef(img,x-1,y+1))
  		{
  			count = 0;
  			if (curCol == imRef(img,x-1,y-1)) count++;
  			if (curCol == imRef(img,x-1,y)) count++;
  			if (curCol == imRef(img,x-1,y+1)) count++;
  			if (curCol == imRef(img,x,y-1)) count++;
  			if (curCol == imRef(img,x,y+1)) count++;
  			if (curCol == imRef(img,x+1,y-1)) count++;
  			if (curCol == imRef(img,x+1,y)) count++;
  			if (curCol == imRef(img,x+1,y+1)) count++;

  			if (count >= 3)
  			{
	  			imRef(result, x, y).r = curCol.r;
					imRef(result, x, y).g = curCol.g;
					imRef(result, x, y).b = curCol.b;

					pos = m.find(curCol);
					if (pos != m.end())
					{
						index = pos->second;
						(*v)[index].push_back(Point2D (x,y));
					}
					else
					{
						index = m.size();
						m[curCol] = index;
						v->push_back(vector<Point2D> (1, Point2D(x,y)));
					}
				}
  		}
  	}
  }

  savePPM(result, (char *) "bordersResult.ppm");
}

//vector<Point2D> EdgeDetector::getCannyBorders(void)
//{
//	return borderPts;
//}
//void EdgeDetector::getFelzenswalbBorders(vector<vector<Point2D> > * v)
//{

//}
