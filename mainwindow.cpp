#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cstdlib>
#include <string>
//#include <vector>

#include "animateactor.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2);



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mRotateAngle(0)
{
    ui->setupUi(this);

//    RotateModel();
//    LodShowModel();
//    AssemblyModel();

    LoadStl("StanfordBunny.stl");
//        AxisShow();
//   Visualization3D();
//    Tool3DModel();
//    ThreeLink();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadStl(std::string stlPath)
{
    widget = new QVTKWidget(this);
//    QRect rect = ui->verticalLayout_4->geometry();
//    widget->setGeometry(rect);
    ui->gridLayout_2->addWidget(widget);

    vtkSmartPointer<vtkRenderer> stlrenderer=vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderer> pCubeRenderer=vtkSmartPointer<vtkRenderer>::New();
//    vtkSmartPointer<vtkRenderWindow> stlrenderWindow=vtkSmartPointer<vtkRenderWindow>::New();
//    stlrenderWindow->AddRenderer(stlrenderer);
//    widget->SetRenderWindow(stlrenderWindow);
    widget->GetInteractor()->GetRenderWindow()->AddRenderer(stlrenderer);
    widget->GetInteractor()->GetRenderWindow()->AddRenderer(pCubeRenderer);
//    vtkSmartPointer<vtkCubeSource> pCube = vtkSmartPointer<vtkCubeSource>::New();
//    vtkSmartPointer<vtkPolyDataMapper> pCubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    pCubeMapper->SetInputConnection(pCube->GetOutputPort());
//    vtkSmartPointer<vtkActor> pCubeActor = vtkSmartPointer<vtkActor>::New();
//    pCubeActor->SetMapper(pCubeMapper);
//    pCubeActor->GetProperty()->SetColor(0.2, 0.63, 0.79);
//    pCubeActor->GetProperty()->SetDiffuse(0.7);
//    pCubeActor->GetProperty()->SetSpecular(0.4);
//    pCubeActor->GetProperty()->SetSpecularPower(20);

    vtkSmartPointer<vtkPolyData> pCube = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkPoints> pCubePoints = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> pCubePolys = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkFloatArray> pCubeScalars = vtkSmartPointer<vtkFloatArray>::New();


    static float x[8][3] =
    { {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1} };
    static vtkIdType pts[6][4] =
    { {0,1,2,3}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {2,3,7,6}, {3,0,4,7} };

    for(int i = 0; i < 8; i++)
    {
        pCubePoints->InsertPoint(i, x[i]);
    }
    for(int i = 0; i < 6; i++)
    {
        pCubePolys->InsertNextCell(4);
        for(int j = 0; j < 4; j++)
        {
            pCubePolys->InsertCellPoint(pts[i][j]);
        }
    }
    for(int i = 0; i < 8; i++)
    {
        pCubeScalars->InsertTuple1(i,i);
    }
    pCube->SetPoints(pCubePoints);
    pCube->SetPolys(pCubePolys);
    pCube->GetPointData()->SetScalars(pCubeScalars);

    vtkSmartPointer<vtkExtractEdges> pCubeExtract = vtkSmartPointer<vtkExtractEdges>::New();
    vtkSmartPointer<vtkPolyDataMapper> pCubeMapEdges = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> pCubeActorEdges = vtkSmartPointer<vtkActor>::New();

    pCubeExtract->SetInputData(pCube);
    pCubeMapEdges->SetInputConnection(pCubeExtract->GetOutputPort());
    pCubeMapEdges->SetScalarVisibility(0);
    pCubeActorEdges->SetMapper(pCubeMapEdges);
    pCubeActorEdges->VisibilityOn();

    vtkSmartPointer<vtkPolyDataMapper> pCubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    pCubeMapper->SetInputData(pCube);
    pCubeMapper->SetScalarRange(0,7);

    for(int p = 0; p < 3; p++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
                cubeActor->SetPosition(p,j,k);
//                vtkSmartPointer<vtkActor> tempActor = vtkSmartPointer<vtkActor>::New();
                cubeActor->SetMapper(pCubeMapper);
                pCubeRenderer->AddActor(cubeActor);
            }
        }
    }
    vtkSmartPointer<vtkCamera> pCubeCamera = vtkSmartPointer<vtkCamera>::New();
    pCubeCamera->SetPosition(3,3,3);
    pCubeCamera->SetFocalPoint(0,0,0);
    pCubeRenderer->SetBackground(.3, .6, .3);
    pCubeRenderer->SetActiveCamera(pCubeCamera);
    pCubeRenderer->ResetCamera();


    vtkSmartPointer<vtkSTLReader> stlReader = vtkSmartPointer<vtkSTLReader>::New();
//    stlReader->SetOutput(stlReader->GetOutput());
    stlReader->SetFileName(stlPath.c_str());
    stlReader->Update();
////under comment code is use to control auto rotate lilinxin 2018/09/20
//    connect(&mDataTimer,SIGNAL(timeout()),this,SLOT(RotateData()));
//    mDataTimer.start(0);

//    vtkSmartPointer<vtkShrinkPolyData> pShrink = vtkSmartPointer<vtkShrinkPolyData>::New();
//    pShrink->SetInputData(stlReader->GetOutput());
//    pShrink->SetShrinkFactor(0.9);

//    vtkSmartPointer<vtkInteractorStyleTrackballCamera> pTrackBallCamera =
//            vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//    widget->GetInteractor()->SetInteractorStyle(pTrackBallCamera);

    vtkSmartPointer<vtkInteractorStyleTrackballActor> pTrackBallActor =
            vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();
    widget->GetInteractor()->SetInteractorStyle(pTrackBallActor);

    pTransformPolyDataFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    pTransformPolyDataFilter->SetInputData(stlReader->GetOutput());
    pTransformPolyDataFilter->Update();
    vtkSmartPointer<vtkPolyDataMapper> stlMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    stlMapper->SetInputData(pTransformPolyDataFilter->GetOutput());
    stlMapper->SetInputData(stlReader->GetOutput());
    stlMapper->Update();
    vtkSmartPointer<vtkActor> stlActor = vtkSmartPointer<vtkActor>::New();
    stlActor->SetMapper(stlMapper);
    stlrenderer->AddActor(stlActor);
    stlrenderer->SetBackground(.3, .6, .3);


}
