#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>

#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include<vtkProperty.h>
#include <vector>
#include <cmath>
#include<vtkImageData.h>
#include<vtkDataSetSurfaceFilter.h>
#include<vtkWarpScalar.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // 1️⃣ Qt 窗口和 QVTK Widget
    QMainWindow window;
    QVTKOpenGLNativeWidget* vtkWidget = new QVTKOpenGLNativeWidget(&window);
    window.setCentralWidget(vtkWidget);
    window.resize(800, 600);
    window.setWindowTitle("2.5D Mesh Qt + VTK");

    // 2️⃣ VTK 渲染窗口
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkWidget->setRenderWindow(renderWindow);

    vtkNew<vtkRenderer> renderer;
    renderWindow->AddRenderer(renderer);

    vtkNew<vtkNamedColors> colors;
    renderer->SetBackground(colors->GetColor3d("PowderBlue").GetData());

    // --------------------------
    // 3️⃣ 生成 2.5D 数据
    // --------------------------
    const int width = 250;
    const int height = 250;
    std::vector<float> heightMap(width * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const int idx = y * width + x;
            if (x > 50 && x < 60 && y > 50 && y < 60) {
                heightMap[idx] = std::numeric_limits<float>::quiet_NaN();
            }
            else {
                heightMap[idx] = 5.0f * std::sin(x * 0.2f) * std::cos(y * 0.2f);
            }
        }
    }

    vtkNew<vtkImageData> image;
    image->SetDimensions(width, height, 1);
    image->AllocateScalars(VTK_FLOAT, 1);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float* pixel = static_cast<float*>(image->GetScalarPointer(x, y, 0));
            pixel[0] = heightMap[y * width + x];
        }
    }

    vtkNew<vtkDataSetSurfaceFilter> surface;
    surface->SetInputData(image);
    surface->Update();

    // ⚠ 将标量转为高度（Z）——关键！
    vtkNew<vtkWarpScalar> warp;
    warp->SetInputConnection(surface->GetOutputPort());
    warp->SetScaleFactor(1.0);  // 控制 Z 高度比例
    warp->Update();

    vtkNew<vtkPolyDataMapper> meshMapper;
    meshMapper->SetInputConnection(warp->GetOutputPort());


    vtkNew<vtkActor> meshActor;
    meshActor->SetMapper(meshMapper);
    meshActor->GetProperty()->SetColor(colors->GetColor3d("LightGoldenrodYellow").GetData());
    meshActor->GetProperty()->EdgeVisibilityOn();
    meshActor->GetProperty()->SetEdgeColor(colors->GetColor3d("CornflowerBlue").GetData());

    // --------------------------
    // 7️⃣ 添加到渲染器
    // --------------------------
    renderer->AddActor(meshActor);

    // 设置交互模式
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    vtkWidget->interactor()->SetInteractorStyle(style);

    // 初始化相机
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCamera();

    window.show();
    return app.exec(); // Qt 主事件循环，保证交互
}
