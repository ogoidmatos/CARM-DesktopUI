#include "mainwindow.h"
#include "benchmarkmodal.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dialog(new BenchmarkModal)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dialog;
}

void MainWindow::on_actionRun_GPU_Benchmark_triggered()
{
    dialog->setGPU();
    dialog->exec();
}
