#pragma once
#include"InteractionManager.h"
#include "RendererManager.h"
#include"vtkRenderWindowInteractor.h"

vtkStandardNewMacro(ScaleInteractorStyle);

// 左键：旋转
void ScaleInteractorStyle::OnLeftButtonDown()
{
    this->StartRotate();
}
void ScaleInteractorStyle::OnLeftButtonUp()
{
    this->EndRotate();
}

// 右键：平移
void ScaleInteractorStyle::OnRightButtonDown()
{
    this->StartPan();
}
void ScaleInteractorStyle::OnRightButtonUp()
{
    this->EndPan();
}

// 中键按下：准备拉伸
void ScaleInteractorStyle::OnMiddleButtonDown()
{
    middlePressed = true;
    lastY = this->Interactor->GetEventPosition()[1];
    this->StartDolly(); // VTK 需要一个状态，但我们不用 dolly
}

void ScaleInteractorStyle::OnMiddleButtonUp()
{
    middlePressed = false;
    this->EndDolly();
}

// 移动鼠标
void ScaleInteractorStyle::OnMouseMove()
{
    if (middlePressed && Manager)
    {
        int y = this->Interactor->GetEventPosition()[1];
        int dy = y - lastY;
        lastY = y;
        // 鼠标向上 dy<0 → 增大 scale（拉伸）
        double deltaScale = dy * stretchSensitivity;

        Manager->adjustZScale(deltaScale);
        return; // 不交给父类处理
    }

    // 默认处理：旋转/平移等
    vtkInteractorStyleTrackballCamera::OnMouseMove();
}

// 滚轮：缩放
void ScaleInteractorStyle::OnMouseWheelForward()
{
    this->Dolly(1.1);
}
void ScaleInteractorStyle::OnMouseWheelBackward()
{
    this->Dolly(0.9);
}
