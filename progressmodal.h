#ifndef PROGRESSMODAL_H
#define PROGRESSMODAL_H

#include <QDialog>
#include "benchmarkdata.h"

class WaitingSpinnerWidget;
class QDialogButtonBox;
class QTextEdit;
class InterfaceGPU;

class ProgressModal : public QDialog
{
    Q_OBJECT
public:
    ProgressModal(const BenchmarkData &data, QWidget *parent = 0);
    void addText(const QString &text);

private slots:
    void closeDialog();

private:
    WaitingSpinnerWidget *spinner;
    QDialogButtonBox *buttonBox;
    QTextEdit *textBox;

    InterfaceGPU *interface;

    void reject();
};

#endif // PROGRESSMODAL_H
