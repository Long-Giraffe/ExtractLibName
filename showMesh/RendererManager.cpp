#include "RendererManager.h"
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkProperty.h>

RendererManager::RendererManager(vtkRenderWindow* renderWindow)
{
    // renderer
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(m_renderer);

    // mesh
    m_meshActor = vtkSmartPointer<vtkActor>::New();

    // outline（包围盒）
    m_outlineActor = vtkSmartPointer<vtkActor>::New();

    // cube axes (刻度尺)
    m_cubeAxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();
    m_cubeAxesActor->SetCamera(m_renderer->GetActiveCamera());
    m_cubeAxesActor->SetFlyModeToClosestTriad();

    // transform 用于 Z-scale 拉伸
    m_transform = vtkSmartPointer<vtkTransform>::New();

    // warp（Z 拉伸核心）
    m_warp = vtkSmartPointer<vtkWarpScalar>::New();
    m_warp->SetScaleFactor(1.0);

    // add initial actors
    m_renderer->AddActor(m_meshActor);
}

void RendererManager::setImageData(vtkImageData* imageData)
{
    // Surface
    vtkSmartPointer<vtkDataSetSurfaceFilter> surface =
        vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
    surface->SetInputData(imageData);
    surface->Update();

    // Warp
    m_warp->SetInputConnection(surface->GetOutputPort());
    m_warp->Update();

    // Mesh mapper
    vtkSmartPointer<vtkPolyDataMapper> meshMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    meshMapper->SetInputConnection(m_warp->GetOutputPort());

    m_meshActor->SetMapper(meshMapper);
    m_meshActor->SetUserTransform(m_transform);

    // Outline
    vtkSmartPointer<vtkOutlineFilter> outline =
        vtkSmartPointer<vtkOutlineFilter>::New();
    outline->SetInputConnection(m_warp->GetOutputPort());

    vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    outlineMapper->SetInputConnection(outline->GetOutputPort());

    m_outlineActor->SetMapper(outlineMapper);
    m_outlineActor->SetUserTransform(m_transform);
    m_outlineActor->GetProperty()->SetColor(1, 1, 1);
    m_outlineActor->GetProperty()->SetLineWidth(2);
    m_renderer->AddActor(m_outlineActor);

    // Cube axes（刻度尺）
    m_cubeAxesActor->SetBounds(m_warp->GetOutput()->GetBounds());
    m_cubeAxesActor->SetCamera(m_renderer->GetActiveCamera());
    m_renderer->AddActor(m_cubeAxesActor);

    // Reset camera
    m_renderer->ResetCamera();
}

/// 设置 Z 拉伸（核心函数）
void RendererManager::setZScale(double scale)
{
    m_transform->Identity();
    m_transform->Scale(1.0, 1.0, scale);

    updateCubeAxesBounds();

    m_renderer->ResetCamera();
    m_renderer->GetRenderWindow()->Render();
}

/// 刷新刻度尺（因为刻度尺不参与 transform）
void RendererManager::updateCubeAxesBounds()
{
    double bounds[6];
    m_warp->GetOutput()->GetBounds(bounds);
    m_cubeAxesActor->SetBounds(bounds);
}

/// 开关包围盒
void RendererManager::enableOutline(bool enabled)
{
    m_outlineActor->SetVisibility(enabled);
}

/// 开关刻度尺
void RendererManager::enableScaleBar(bool enabled)
{
    m_cubeAxesActor->SetVisibility(enabled);
}

void RendererManager::adjustZScale(double delta)
{
    double cur = m_warp->GetScaleFactor();
    double next = std::max(0.0001, cur + delta);

    m_warp->SetScaleFactor(next);
    m_warp->Update();

    m_cubeAxesActor->SetBounds(m_warp->GetOutput()->GetBounds());
    m_renderer->GetRenderWindow()->Render();
}

