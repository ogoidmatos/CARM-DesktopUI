#include "mainwindow.h"
#include "benchmarkmodal.h"
#include "progressmodal.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dialog(new BenchmarkModal(this))
{
    ui->setupUi(this);

    connect(dialog,
            SIGNAL(sendBenchmarkData(BenchmarkData)),
            this,
            SLOT(runBenchmarks(BenchmarkData)));
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

void MainWindow::runBenchmarks(BenchmarkData data)
{
    ProgressModal progressDialog(data, this);
    progressDialog.exec();
}
