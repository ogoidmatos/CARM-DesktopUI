#ifndef BENCHMARKDATA_H
#define BENCHMARKDATA_H

#include <string>
#include <vector>

using namespace std;

enum DEVICE { CPU, GPU };

class BenchmarkData
{
public:
    explicit BenchmarkData(DEVICE device,
                           int threads,
                           int blocks,
                           const string &machine_name,
                           const vector<string> &cuda,
                           const vector<string> &tensor,
                           const string &test)
        : device(device)
        , threads(threads)
        , blocks(blocks)
        , machine_name(machine_name)
        , cuda(cuda)
        , tensor(tensor)
        , test(test)
    {}

    ~BenchmarkData() {}

    BenchmarkData(const BenchmarkData &other)
    {
        device = other.device;
        threads = other.threads;
        blocks = other.blocks;
        machine_name = other.machine_name;
        cuda = other.cuda;
        tensor = other.tensor;
        test = other.test;
    }

    BenchmarkData &operator=(const BenchmarkData &other)
    {
        device = other.device;
        threads = other.threads;
        blocks = other.blocks;
        machine_name = other.machine_name;
        cuda = other.cuda;
        tensor = other.tensor;
        test = other.test;
        return *this;
    }

private:
    DEVICE device;
    int threads;
    int blocks;
    string machine_name;
    vector<string> cuda;
    vector<string> tensor;
    string test;
};

#endif // BENCHMARKDATA_H
