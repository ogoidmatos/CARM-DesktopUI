#ifndef PROGRESSMODAL_H
#define PROGRESSMODAL_H

#include <QDialog>
#include "benchmarkdata.h"

class WaitingSpinnerWidget;

class ProgressModal : public QDialog
{
    Q_OBJECT
public:
    ProgressModal(const BenchmarkData &data, QWidget *parent = 0);

private:
    WaitingSpinnerWidget *spinner;

    void reject();
};

#endif // PROGRESSMODAL_H
