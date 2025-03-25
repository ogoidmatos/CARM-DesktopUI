#include "progressmodal.h"
#include "interfacegpu.h"
#include "waitingspinnerwidget.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include <QThread>
#include <QVBoxLayout>

ProgressModal::ProgressModal(const BenchmarkData &data, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Executing Benchmarks");

    spinner = new WaitingSpinnerWidget(0, false, false);
    spinner->setRoundness(70.0);
    spinner->setMinimumTrailOpacity(15.0);
    spinner->setTrailFadePercentage(70.0);
    spinner->setNumberOfLines(10);
    spinner->setLineLength(5);
    spinner->setLineWidth(2);
    spinner->setInnerRadius(5);
    spinner->setRevolutionsPerSecond(1);
    spinner->setColor(QColor(81, 4, 71));
    spinner->start();

    QLabel *label = new QLabel;
    label->setText("Benchmark Output:");

    textBox = new QTextEdit;
    textBox->setReadOnly(true);
    textBox->setFixedWidth(500);
    textBox->setFixedHeight(300);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(spinner);
    buttonLayout->addWidget(buttonBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(textBox);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setFixedSize(sizeHint());

    //create thread here
    interface = new InterfaceGPU(data, this);
    connect(interface, SIGNAL(terminateBenchmarks()), this, SLOT(closeDialog()));

    interface->start();
}

void ProgressModal::addText(const QString &text)
{
    textBox->append(text);
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

void ProgressModal::closeDialog()
{
    QDialog::reject();
}
