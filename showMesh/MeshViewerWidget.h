#pragma once
#include"ui_vtkMeshShow.h"
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

    void setImageData(vtkNew<vtkImageData>& imageData);
    //void setColorMap(vtkSmartPointer<vtkLookupTable> lut);
    void enableAxes(bool enabled);
    void enableScaleBar(bool enabled);
    void setZScale(double scale);   // ¿≠…Ï

private:

    RendererManager* rendererManager;
    //InteractionManager* interactionManager;
    Ui_vtkShowWidget * ui;
};

