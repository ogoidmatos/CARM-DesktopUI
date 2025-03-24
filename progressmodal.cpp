#include "progressmodal.h"
#include "waitingspinnerwidget.h"

#include <QMessageBox>

ProgressModal::ProgressModal(const BenchmarkData &data, QWidget *parent)
    : QDialog(parent)
{
    spinner = new WaitingSpinnerWidget(this);
    spinner->setRoundness(70.0);
    spinner->setMinimumTrailOpacity(15.0);
    spinner->setTrailFadePercentage(70.0);
    spinner->setNumberOfLines(12);
    spinner->setLineLength(10);
    spinner->setLineWidth(5);
    spinner->setInnerRadius(10);
    spinner->setRevolutionsPerSecond(1);
    spinner->setColor(QColor(81, 4, 71));

    setWindowTitle("Executing Benchmarks");
    //setFixedSize(sizeHint());
}

void ProgressModal::reject()
{
    QMessageBox::StandardButton resBtn = QMessageBox::Yes;
    resBtn = QMessageBox::question(this,
                                   "Are you sure?",
                                   "This will interrupt the current execution of benchmarks.\n",
                                   QMessageBox::No | QMessageBox::Yes,
                                   QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes) {
        QDialog::reject();
    }
}
