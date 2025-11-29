#pragma once
#include<vtkImageData.h>
#include<vtkPolyData.h>
#include<opencv2/opencv.hpp>
class DataProcess
{
public:
    static vtkSmartPointer<vtkImageData>
        convertToVTKImage(const cv::Mat& depth);

    static vtkSmartPointer<vtkPolyData>
        convertToPointCloud(const cv::Mat& depth);

};

