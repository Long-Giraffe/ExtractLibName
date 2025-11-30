#include "RendererManager.h"
#include "vtkWarpScalar.h"
#include "vtkPolyDataMapper.h"
#include "vtkDataSetSurfaceFilter.h"
#include "vtkImageData.h"
#include "vtkProperty.h"
#include <vtkNamedColors.h>
#include <vtkCamera.h>

RendererManager::RendererManager(vtkRenderWindow* RenderWindow)
{
    RenderWindow->AddRenderer(m_renderer);
    vtkNew<vtkNamedColors> colors;
    m_meshActor->GetProperty()->SetColor(colors->GetColor3d("LightGoldenrodYellow").GetData());
    m_meshActor->GetProperty()->EdgeVisibilityOn();
    m_meshActor->GetProperty()->SetEdgeColor(colors->GetColor3d("CornflowerBlue").GetData());
    m_renderer->AddActor(m_meshActor);
    m_renderer->AddActor(m_axesActor);

}

void RendererManager::setImageData(vtkNew<vtkImageData>& imageData)
{
    //1.从 3D 数据 或 ImageData 提取外表面形成 PolyData（三角网格）
    vtkNew<vtkDataSetSurfaceFilter> surface;
    surface->SetInputData(imageData);
    surface->Update();

    //2.根据某个标量字段（比如 Z 值、深度、灰度）沿法向方向拉伸网格
    vtkNew<vtkWarpScalar> warp;
    warp->SetInputConnection(surface->GetOutputPort());
    warp->SetScaleFactor(1);  // 控制 Z 高度比例
    warp->Update();

    //3.把你的三角网格变成 GPU 可以显示的内容。
    vtkNew<vtkPolyDataMapper> meshMapper;
    meshMapper->SetInputConnection(warp->GetOutputPort());

    //4.将mesh添加到actor中以便渲染
    m_meshActor->SetMapper(meshMapper);

    m_meshActor->SetUserTransform(m_transform);
    // 初始化相机
    m_renderer->GetActiveCamera()->Azimuth(30);
    m_renderer->GetActiveCamera()->Elevation(30);
    m_renderer->ResetCamera();
}

