#include <QtDebug>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core.h"
//#include<stdio.h> //    //system("google-chrome");
//#include<iostream>



//#include "debug.h"
static CoreProcessing CoreApp;


MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),

    ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    ui->CoreUse_Label->setText("Nbr Core : " + QString::fromStdString(std::to_string(CoreApp.UseCore)));
    ui->CoreUse_horizontalSlider->setSliderPosition(CoreApp.UseCore);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Bouton OK";
    qDebug() << "============================================================";
    CoreApp.exec();
    //QString tt = CoreApp.exec("p7zip -h");
    qDebug() << QString::fromStdString("");
    qDebug() << "============================================================";
    ui->progressBar->setValue(ui->progressBar->value()+1);
    //qDebug() << QString::number(CoreApp.CPUThreadCount());
}


void MainWindow::on_actionDivers_2_triggered()
{
    const std::string Compilator_Version = std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__) + "." + std::to_string(__GNUC_PATCHLEVEL__);
    QString CPP_Info = QString::fromStdString(std::to_string(__cplusplus));

    QString QCompilator_Version = "Compiler Version :" + QString::fromStdString(Compilator_Version);

    QMessageBox msgBox;

    msgBox.setText("<b>Build informations</b>");
    QString Message = QString("Build by: ") + QCompilator_Version + "\n" + "C++ version: " + CPP_Info;
    msgBox.setInformativeText(Message);
    msgBox.exec();
}

void MainWindow::on_CoreUse_horizontalSlider_sliderMoved(int position)
{
    qDebug() << "CoreUse_horizontalSlider_sliderMoved :"+ QString::fromStdString(std::to_string(position));
    CoreApp.UseCore = (unsigned int)position;
    QString s = QString::fromStdString(std::to_string(position));
    ui->CoreUse_Label->setText("Nbr Core : " + s);

}

void MainWindow::on_CoreUse_horizontalSlider_actionTriggered(int action)
{
    qDebug() << "CoreUse_horizontalSlider_actionTriggered :"+ QString::fromStdString(std::to_string(action));
    qDebug() << "CoreUse_horizontalSlider_actionTriggered2 :"+ QString::fromStdString(std::to_string(ui->CoreUse_horizontalSlider->value()));
}





void MainWindow::on_CoreUse_horizontalSlider_sliderPressed()
{
    qDebug() <<"CoreUse_horizontalSlider_sliderPressed :" + QString::fromStdString(std::to_string(ui->CoreUse_horizontalSlider->value()));
    CoreApp.UseCore = (unsigned int)ui->CoreUse_horizontalSlider->value();
    ui->CoreUse_Label->setText("Nbr Core : " + QString::fromStdString(std::to_string(ui->CoreUse_horizontalSlider->value())));
}
