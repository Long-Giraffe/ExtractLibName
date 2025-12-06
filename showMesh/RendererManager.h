#pragma once

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkWarpScalar.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCubeAxesActor.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>

class RendererManager
{
public:
    RendererManager(vtkRenderWindow* renderWindow);

    void setImageData(vtkImageData* imageData);
    void setZScale(double scale);

    void enableAxes(bool enabled);
    void enableOutline(bool enabled);
    void enableScaleBar(bool enabled);
    void adjustZScale(double delta);

private:
    void updateCubeAxesBounds();

private:
    vtkSmartPointer<vtkRenderer> m_renderer;

    vtkSmartPointer<vtkActor> m_meshActor;
    vtkSmartPointer<vtkActor> m_outlineActor;
    vtkSmartPointer<vtkCubeAxesActor> m_cubeAxesActor;
    vtkSmartPointer<vtkTransform> m_transform;
    vtkSmartPointer<vtkWarpScalar> m_warp;
};
