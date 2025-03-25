#ifndef INTERFACEGPU_H
#define INTERFACEGPU_H

#include <QThread>
#include "benchmarkdata.h"
#include "progressmodal.h"

class InterfaceGPU : public QThread
{
    Q_OBJECT
public:
    InterfaceGPU(const BenchmarkData &data, ProgressModal *dialog);
    void run() override;

signals:
    void terminateBenchmarks();

private:
    BenchmarkData data;
    ProgressModal *dialog;
};

#endif // INTERFACEGPU_H
