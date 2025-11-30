#include "MeshGenerator.h"

vtkNew<vtkImageData> MeshGenerator::convertToVTKImage(const cv::Mat& depth)
{
    vtkNew<vtkImageData> image;

    if (depth.empty())
    {
        std::cerr << "Warning: Input depth image is empty." << std::endl;
        return image;
    }

    if (depth.type() != CV_32FC1)
    {
        std::cerr << "Warning: Input depth image must be of type CV_32FC1 (single channel 32-bit float). Got type: " << depth.type() << std::endl;
        return image;
    }

    image->SetDimensions(depth.cols, depth.rows, 1);
    image->AllocateScalars(VTK_FLOAT, 1);

    for (int y = 0; y < depth.rows; y++)
    {
        const float* ptr = depth.ptr<float>(y);
        for (int x = 0; x < depth.cols; x++)
        {
            float* pixel = static_cast<float*>(image->GetScalarPointer(x, y, 0));
            pixel[0] = ptr[x];
        }
    }

    return image;
}
