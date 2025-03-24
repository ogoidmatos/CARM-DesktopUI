#ifndef BENCHMARKMODAL_H
#define BENCHMARKMODAL_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QLabel;
class QComboBox;
class QListWidget;
class QSpinBox;

#include "benchmarkdata.h"

class BenchmarkModal : public QDialog
{
    Q_OBJECT
public:
    BenchmarkModal(QWidget *parent = 0);
    void setGPU();
    void setCPU();

private slots:
    void prepareBenchmarks();

signals:
    void sendBenchmarkData(BenchmarkData data);

private:
    DEVICE device;
    QLabel *name;
    QLineEdit *nameEdit;
    QLabel *test;
    QComboBox *testBox;
    QLabel *cuda;
    QListWidget *cudaList;
    QLabel *tensor;
    QListWidget *tensorList;
    QLabel *threads;
    QSpinBox *threadsBox;
    QLabel *blocks;
    QSpinBox *blocksBox;
    QPushButton *runButton;
    QPushButton *closeButton;

    void initializeLists(QListWidget *cudaList, QListWidget *tensorList);
};

#endif // BENCHMARKMODAL_H
