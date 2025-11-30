#pragma once
#include<vtkPolyData.h>
#include<vtkImageData.h>
#include<opencv2/opencv.hpp>>
class MeshGenerator {
public:
public:
    static vtkNew<vtkImageData>
        convertToVTKImage(const cv::Mat& depth);
};


