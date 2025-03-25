#ifndef PROGRESSMODAL_H
#define PROGRESSMODAL_H

#include <QDialog>
#include "benchmarkdata.h"

class WaitingSpinnerWidget;
class QDialogButtonBox;
class QTextEdit;

class ProgressModal : public QDialog
{
    Q_OBJECT
public:
    ProgressModal(const BenchmarkData &data, QWidget *parent = 0);

private:
    WaitingSpinnerWidget *spinner;
    QDialogButtonBox *buttonBox;
    QTextEdit *textBox;

    void reject();
};

#endif // PROGRESSMODAL_H
