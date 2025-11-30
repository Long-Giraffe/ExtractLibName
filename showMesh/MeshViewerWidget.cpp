#include "MeshViewerWidget.h"
#include <vtkInteractorStyleTrackballCamera.h>
#include "vtkImageData.h"
#include "vtkNew.h"

MeshViewerWidget::MeshViewerWidget(QWidget* parent):QVTKOpenGLNativeWidget(parent),ui(new Ui::vtkShowWidget)   
{
    ui->setupUi(this);

   auto vtkWidget = new QVTKOpenGLNativeWidget(this);
    ui->verticalLayout->addWidget(vtkWidget);

    rendererManager = new RendererManager(vtkWidget->renderWindow());
  vtkNew<vtkInteractorStyleTrackballCamera> style;
    vtkWidget->interactor()->SetInteractorStyle(style);
}

void MeshViewerWidget::setImageData(vtkNew<vtkImageData>& imageData)
{
    rendererManager->setImageData(imageData);
}

void MeshViewerWidget::enableAxes(bool enabled)
{
}

void MeshViewerWidget::enableScaleBar(bool enabled)
{
}

void MeshViewerWidget::setZScale(double scale)
{
}
