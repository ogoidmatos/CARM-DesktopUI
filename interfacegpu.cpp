#include "interfacegpu.h"
#include <iostream>

using namespace std;

InterfaceGPU::InterfaceGPU(const BenchmarkData &data, ProgressModal *dialog)
    : data(data)
    , dialog(dialog)
{
}

void InterfaceGPU::run()
{
    // Check if GPU is available
    int check = system("nvidia-smi");
    if (check != 0) {
        cerr << "NVIDIA GPU not detected" << endl;
        dialog->addText("[WARN] - GPU not detected. Stopping benchmarks.");
        dialog->addText("[INFO] - This window will close in 5 seconds.");
        QThread::sleep(5);
        emit terminateBenchmarks();
        quit();
    } else {
        dialog->addText("[INFO] - GPU detected.");
    }
}
