#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BenchmarkModal;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionRun_GPU_Benchmark_triggered();

private:
    Ui::MainWindow *ui;
    BenchmarkModal *dialog;
};
#endif // MAINWINDOW_H
