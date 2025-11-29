#include <QApplication>
#include "LibNameDisplay.h"  // 你的窗口类头文件

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    LibNameDisplay window;  // 实例化窗口

    window.show();          // 显示窗口

    return app.exec();      // 进入事件循环
}
