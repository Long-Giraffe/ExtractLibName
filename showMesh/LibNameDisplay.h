#pragma once

#include <QObject>
#include <QFileDialog>
#include <QMessageBox>
#include"ui_libTool.h"
class LibNameDisplay : public QWidget
{
    Q_OBJECT

public:
    LibNameDisplay(QWidget* parent = nullptr);
    ~LibNameDisplay();

public slots:
    void on_BTopenPath_clicked();
    void on_BTrun_clicked();
    void on_BTclear_clicked();
    void on_BTreleaseCopy_clicked();
    void on_BTdebugCopy_clicked();

private:
    Ui_libToolWidget* ui;
    QString libPath;
};

