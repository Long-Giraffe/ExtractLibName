#include "LibNameDisplay.h"
#include <QFileDialog>
#include <QMessageBox>
#include<filesystem>
#include <iostream>
#include <QClipboard>
namespace fs = std::filesystem;

LibNameDisplay::LibNameDisplay(QWidget* parent)
    : QWidget(parent), libPath(""), ui(nullptr)
{
    ui = new Ui_libToolWidget();
    ui->setupUi(this);
}

LibNameDisplay::~LibNameDisplay()
{
}

void LibNameDisplay::on_BTrun_clicked()
{
    if (!fs::exists(libPath.toStdString())) {
        ui->textEditLog->setText("path not exist!");
    }

    for (const auto& file : fs::directory_iterator(libPath.toStdString())) {
        if (file.path().extension() == ".lib")
        {
            auto a = file.path().filename().string().find("d.lib");
            if (a == std::string::npos)
            {
                ui->relaseText->append(file.path().filename().string().c_str());
            }
        }
    }

    for (const auto& file : fs::directory_iterator(libPath.toStdString())) {
        auto a = file.path().filename().string().find("d.lib");
        if (a != std::string::npos)
        {
            ui->debugText->append(file.path().filename().string().c_str());
        }
    }
}

void LibNameDisplay::on_BTclear_clicked()
{
    ui->relaseText->clear();
    ui->debugText->clear();
}

void LibNameDisplay::on_BTreleaseCopy_clicked()
{
    QString text = ui->relaseText->toPlainText();
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void LibNameDisplay::on_BTdebugCopy_clicked()
{
    QString text = ui->debugText->toPlainText();

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void LibNameDisplay::on_BTopenPath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,
        tr("Select Path"),
        QDir::currentPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty())
    {
        ui->textEditLog->setText("Select Path Success:" + dir);
        libPath = dir;
        on_BTrun_clicked();
    }
    else
    {
        ui->textEditLog->setText("Select Path Filled:" + dir);
        libPath = "";
    }
}


