#include <QApplication>
#include <QMainWindow>
#include <vtkImageData.h>
#include"MeshViewerWidget.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
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
    MeshViewerWidget  viewer;
    viewer.setImageData(image);
    viewer.show();
   
    return app.exec(); // Qt 主事件循环，保证交互
}
