/****************************************************************
 Doc    :   mainwindow.h
 Author :   BingLee
 Date   :   2018-12-12
 Info   :   StlLoad
 https://blog.csdn.net/Bing_Lee (C)All rights reserved.
******************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVTKWidget.h>
#include <vtkAssembly.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void LoadStl(std::string stlPath);          //load STL model
    void Visualization3D();                     //8 daily use model creat method
    void AxisShow();                            //show global axis
    void RotateModel();                         //auto rotate model
    void LodShowModel();                        //set level of vision show
    void AssemblyModel();                       //combine component together
    void Tool3DModel();                         //mechine tool model creat
    void ThreeLink();                           //use slider do motion control
    vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName);
    Ui::MainWindow *ui;
    QVTKWidget *widget;

private:
    vtkSmartPointer<vtkUnstructuredGrid> MakeHexagonalPrism();
    vtkSmartPointer<vtkUnstructuredGrid> MakeHexahedron();
    vtkSmartPointer<vtkUnstructuredGrid> MakePentagonalPrism();
    vtkSmartPointer<vtkUnstructuredGrid> MakePolyhedron();
    vtkSmartPointer<vtkUnstructuredGrid> MakePyramid();
    vtkSmartPointer<vtkUnstructuredGrid> MakeTetrahedron();
    vtkSmartPointer<vtkUnstructuredGrid> MakeVoxel();
    vtkSmartPointer<vtkUnstructuredGrid> MakeWedge();
    vtkSmartPointer<vtkActor> modelActor;
    vtkSmartPointer<vtkLODActor> lodModelActor;
    QTimer mDataTimer;
    double mRotateAngle;
    vtkSmartPointer<vtkTransformPolyDataFilter> pTransformPolyDataFilter;
    vtkSmartPointer<vtkAssembly> joint1;
    vtkSmartPointer<vtkAssembly> joint2;
    vtkSmartPointer<vtkAssembly> joint3;
    int joint1Angle;
    int joint2Angle;
    int joint3Angle;
private slots:
    void RotateData();
    void Rotate1();
    void Rotate2();
    void Rotate3();
};


#endif // MAINWINDOW_H
