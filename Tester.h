#ifndef TESTER
#define TESTER

#include <memory>
#include <windows.h>
#include "GraphGenerator.h"
#include "Graph.h"
#include "GAlgorithm.h"
#include "StructLib.h"
#include "FileHandler.h"

#define N 1000
#define STEP 7
#define CYCLES 100

class Tester {
private:
    std::unique_ptr<Graph> graph = nullptr;
    std::unique_ptr<GAlgorithm> galgo = nullptr;
    
    std::vector<std::vector<long long>> res;
    int res_count = 0;
public: 
    Tester() {}
    Tester(GAlgorithm* _galgo) : galgo(_galgo) {}

    void write_res();
    void test_efficiency(double density, represent_type r_type);
};



#endif