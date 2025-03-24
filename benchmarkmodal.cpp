#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

#include "benchmarkdata.h"
#include "benchmarkmodal.h"

BenchmarkModal::BenchmarkModal(QWidget *parent)
    : QDialog(parent)
    , device(CPU)
{
    name = new QLabel("Machine Name:");
    nameEdit = new QLineEdit;

    test = new QLabel("Test:");
    testBox = new QComboBox();
    testBox->setMinimumContentsLength(15);
    testBox->addItems({"Roofline"});

    cuda = new QLabel("Cuda Core Precisions:");
    cudaList = new QListWidget;

    tensor = new QLabel("Tensor Core Precisions:");
    tensorList = new QListWidget;

    initializeLists(cudaList, tensorList);

    threads = new QLabel("# Threads:");
    threadsBox = new QSpinBox;
    threadsBox->setRange(1, 1024);
    threadsBox->setValue(1024);

    blocks = new QLabel("# Blocks:");
    blocksBox = new QSpinBox;
    blocksBox->setRange(1, 32768);
    blocksBox->setValue(32768);

    runButton = new QPushButton("Run");
    runButton->setDefault(true);

    closeButton = new QPushButton("Close");

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(runButton, SIGNAL(clicked()), this, SLOT(prepareBenchmarks()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(name);
    topLeftLayout->addWidget(nameEdit);

    QHBoxLayout *topRightLayout = new QHBoxLayout;
    topRightLayout->addWidget(test);
    topRightLayout->addWidget(testBox);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(topLeftLayout);
    topLayout->addLayout(topRightLayout);

    QHBoxLayout *middleLeftLayout = new QHBoxLayout;
    middleLeftLayout->addWidget(threads);
    middleLeftLayout->addWidget(threadsBox);

    QHBoxLayout *middleRightLayout = new QHBoxLayout;
    middleRightLayout->addWidget(blocks);
    middleRightLayout->addWidget(blocksBox);

    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->addLayout(middleLeftLayout);
    middleLayout->addLayout(middleRightLayout);

    QVBoxLayout *bottomLeftLayout = new QVBoxLayout;
    bottomLeftLayout->addWidget(cuda);
    bottomLeftLayout->addWidget(cudaList);

    QVBoxLayout *bottomRightLayout = new QVBoxLayout;
    bottomRightLayout->addWidget(tensor);
    bottomRightLayout->addWidget(tensorList);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addLayout(bottomLeftLayout);
    bottomLayout->addLayout(bottomRightLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(runButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle("Configure Benchmarks");
    setFixedSize(sizeHint());
}

void BenchmarkModal::setGPU()
{
    device = GPU;
}

void BenchmarkModal::setCPU()
{
    device = CPU;
}

void BenchmarkModal::initializeLists(QListWidget *cudaList, QListWidget *tensorList)
{
    QListWidgetItem *newItem = new QListWidgetItem("HP");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    cudaList->addItem(newItem);

    newItem = new QListWidgetItem("BF16");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    cudaList->addItem(newItem);

    newItem = new QListWidgetItem("SP");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    cudaList->addItem(newItem);

    newItem = new QListWidgetItem("DP");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    cudaList->addItem(newItem);

    newItem = new QListWidgetItem("FP16 16");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    tensorList->addItem(newItem);

    newItem = new QListWidgetItem("FP16 32");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    tensorList->addItem(newItem);

    newItem = new QListWidgetItem("BF16");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    tensorList->addItem(newItem);

    newItem = new QListWidgetItem("TF32");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    tensorList->addItem(newItem);

    newItem = new QListWidgetItem("INT8");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    tensorList->addItem(newItem);

    newItem = new QListWidgetItem("INT4");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    tensorList->addItem(newItem);

    newItem = new QListWidgetItem("INT1");
    newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
    newItem->setCheckState(Qt::Checked);
    tensorList->addItem(newItem);
}

void BenchmarkModal::prepareBenchmarks()
{
    const int threads = threadsBox->value();
    const int blocks = blocksBox->value();
    std::string name = nameEdit->text().toStdString();
    std::string test = testBox->currentText().toLower().toStdString();
    std::vector<std::string> cuda;
    std::vector<std::string> tensor;
    for (int i = 0; i < cudaList->count(); i++) {
        QListWidgetItem *item = cudaList->item(i);
        if (item->checkState() & Qt::Checked) {
            cuda.push_back(item->text().toLower().toStdString());
        }
    }

    for (int i = 0; i < tensorList->count(); i++) {
        QListWidgetItem *item = tensorList->item(i);
        if (item->checkState() & Qt::Checked) {
            tensor.push_back(item->text().toLower().replace(" ", "_").toStdString());
        }
    }

    BenchmarkData data(device, threads, blocks, name, cuda, tensor, test);

    // cleanup
    threadsBox->setValue(1024);
    blocksBox->setValue(32768);
    nameEdit->clear();
    testBox->setCurrentIndex(0);
    for (int i = 0; i < cudaList->count(); i++) {
        cudaList->item(i)->setCheckState(Qt::Checked);
    }

    for (int i = 0; i < tensorList->count(); i++) {
        tensorList->item(i)->setCheckState(Qt::Checked);
    }

    close();
}
