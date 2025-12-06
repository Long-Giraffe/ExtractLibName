#pragma once
#include <vtkInteractorStyleTrackballCamera.h>

class RendererManager;

class ScaleInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static ScaleInteractorStyle* New();
    vtkTypeMacro(ScaleInteractorStyle, vtkInteractorStyleTrackballCamera);

    void SetRendererManager(RendererManager* manager) { Manager = manager; }

    // 鼠标事件
    void OnLeftButtonDown() override;
    void OnRightButtonDown() override;
    void OnMiddleButtonDown() override;

    void OnLeftButtonUp() override;
    void OnRightButtonUp() override;
    void OnMiddleButtonUp() override;

    void OnMouseMove() override;

    void OnMouseWheelForward() override;
    void OnMouseWheelBackward() override;

private:
    RendererManager* Manager = nullptr;

    bool middlePressed = false;
    int lastY = 0;

    double stretchSensitivity = 0.01; // 中键拖动拉伸灵敏度
};
