/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: Cone.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This example creates a polygonal model of a cone, and then renders it to
// the screen. It will rotate the cone 360 degrees and then exit. The basic
// setup of source -> mapper -> actor -> renderer -> renderwindow is
// typical of most VTK programs.
//

// First include the required header files for the VTK classes we are using.
#include <vtkSmartPointer.h>
#include <vtkPolygon.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkWindowToImageFilter.h"
#include "vtkPNGWriter.h"

#include "vtkCamera.h"



#include <vtkPolyDataMapper2D.h>
#include <vtkActor2D.h>
#include <vtkMath.h>
#include <vtkProperty2D.h>


#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

#include <vtkProperty.h>
#include <vtkActor.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>



#define WSIZE 420

using namespace std;

int main(int argc, char *argv[]) {
	int RGB2[3], RGB1[3];
    char auxi[128];
    /*
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int num3 = atoi(argv[3]);
    int num4 = atoi(argv[4]);
    */
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;

    vector<float> v_x;
    vector<float> v_y;
    vector<float> v2_x;
    vector<float> v2_y;



    ifstream fe("resta.txt");
    char cadena[128];
    // Leeremos mediante getline, si lo hiciéramos
    // mediante el operador >> sólo leeríamos
    // parte de la cadena:
    fe.getline(cadena, 128);


    int n_ver1 = atoi(cadena);

    for (int aux = 0; aux < n_ver1; aux++) {
        char aux_x[128], aux_y[128];
        fe.getline(aux_x, 128);
        v_x.push_back(atoi(aux_x));
        fe.getline(aux_y, 128);
        v_y.push_back(atoi(aux_y));


    }
	fe.getline(auxi, 128);
        
    RGB1[0]=atoi(auxi);
fe.getline(auxi, 128);
        
    RGB1[1]=atoi(auxi);
fe.getline(auxi, 128);
        
    RGB1[2]=atoi(auxi);

    fe.close();
    
    for (int aux = 0; aux <= n_ver1; aux++) {
        cout << v_x[aux] << " " << v_y[aux] << endl;
    }

    cout << "kkk " << num1 << endl;

    //Setup four points
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
   
    for (int aux = 0; aux < n_ver1; aux++) {
        points->InsertNextPoint((v_x[aux] + 300) / 3, (v_y[aux] + 600) / 3, 0.0);
       }


    //Create the polygon
    vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
    polygon->GetPointIds()->SetNumberOfIds(n_ver1); //make a quad

    for (int cont = 0; cont < (n_ver1); cont++) {

        polygon->GetPointIds()->SetId(cont, cont);
    }



    vtkSmartPointer<vtkCellArray> polygons = vtkSmartPointer<vtkCellArray>::New();
    polygons->InsertNextCell(polygon);

    //Create a PolyData
    vtkSmartPointer<vtkPolyData> polygonPolyData = vtkSmartPointer<vtkPolyData>::New();
    polygonPolyData->SetPoints(points);
    polygonPolyData->SetPolys(polygons);


    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    /*transform->RotateWXYZ(45,1,1,0);

    vtkSmartPointer<vtkTransformPolyDataFilter>  transformFilter= vtkSmartPointer<vtkTransformPolyDataFilter> ::New();
    transformFilter->SetTransform(transform);
    transformFilter->SetInput(polygonPolyData);
    transformFilter->Update();
     */
    cout << "Aci estem" << endl;
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    // vtkSmartPointer<vtkActor2D> actor = vtkSmartPointer<vtkActor2D>::New();
    //double color[3] = {RGB1[0],RGB1[1], RGB1[2]};
	double color[3] = {0,0,0};
    /*
      vtkSmartPointer<vtkPolyDataMapper2D> mapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
      mapper->SetInput( polygonPolyData );
      //mapper->SetInput(transformFilter->GetOutput());
      mapper->ScalarVisibilityOn();
      actor->SetMapper( mapper );
      actor->GetProperty()->SetColor( color );
     */

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInput(polygonPolyData);
    //mapper->SetInput(transformFilter->GetOutput());
    mapper->ScalarVisibilityOn();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color);
    actor->RotateZ(180);



    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    // Renderer and RenderWindow
    renderer->SetBackground(1, 1, 1);
    //renderer->ResetCamera();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    renderWindow->SetSize(400, 400);
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindow->Render();
    //renderWindow->Finalize();

    //renderWindow->Start();
    //  renderWindowInteractor->EnableRenderOff();

    //renderWindowInteractor->Stop();


    vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
            vtkSmartPointer<vtkWindowToImageFilter>::New();
    windowToImageFilter->SetInput(renderWindow);
    windowToImageFilter->Update();

    vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName("resultat.png");
    writer->SetInput(windowToImageFilter->GetOutput());
    writer->Write();

    //renderWindowInteractor->Start();
    //renderWindowInteractor->SetTimerDuration(0);
    //renderWindowInteractor->TerminateApp();

}


