#pragma once
#include"RendererManager.h"
#include"InteractionManager.h"
#include"AxesManager.h"
#include"ColorMapManager.h"
#include"ScaleBarManager.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>

class MeshViewerWidget : public QVTKOpenGLNativeWidget
{
    Q_OBJECT
public:
    MeshViewerWidget(QWidget* parent = nullptr);

    void setMesh(vtkSmartPointer<vtkPolyData> mesh);
    void setColorMap(vtkSmartPointer<vtkLookupTable> lut);
    void enableAxes(bool enabled);
    void enableScaleBar(bool enabled);
    void setZScale(double scale);   // ¿≠…Ï

private:
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;

    RendererManager* rendererManager;
    InteractionManager* interactionManager;
    AxesManager* axesManager;
    ColorMapManager* colorMapManager;
    ScaleBarManager* scaleBarManager;

    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkActor> meshActor;
};

