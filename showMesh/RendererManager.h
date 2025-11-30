#pragma once
#include "vtkRenderWindow.h"
#include <vtkRenderer.h>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>

class RendererManager
{
public:
    RendererManager(vtkRenderWindow* RenderWindow);

    void setImageData(vtkNew<vtkImageData>& imageData);

private:
    vtkNew<vtkRenderer> m_renderer;
    vtkNew<vtkActor> m_meshActor;
    vtkNew<vtkAxesActor> m_axesActor;
    vtkNew<vtkTransform> m_transform;
};

