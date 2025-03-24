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

    DEVICE getDevice() const;
    int getThreads() const;
    int getBlocks() const;
    string getMachine_name() const;
    vector<string> getCuda() const;
    vector<string> getTensor() const;
    string getTest() const;

private:
    DEVICE device;
    int threads;
    int blocks;
    string machine_name;
    vector<string> cuda;
    vector<string> tensor;
    string test;
};

inline DEVICE BenchmarkData::getDevice() const
{
    return device;
}

inline int BenchmarkData::getThreads() const
{
    return threads;
}

inline int BenchmarkData::getBlocks() const
{
    return blocks;
}

inline string BenchmarkData::getMachine_name() const
{
    return machine_name;
}

inline vector<string> BenchmarkData::getCuda() const
{
    return cuda;
}

inline vector<string> BenchmarkData::getTensor() const
{
    return tensor;
}

inline string BenchmarkData::getTest() const
{
    return test;
}

#endif // BENCHMARKDATA_H
