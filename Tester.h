#ifndef TESTER
#define TESTER

#include <memory>
#include <windows.h>
#include "GraphGenerator.h"
#include "Graph.h"
#include "GAlgorithm.h"

#define N 100
#define STEP 5
#define CYCLES 100


long long int read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
} 



class Tester {
private:
    std::unique_ptr<Graph> graph = nullptr;
    std::unique_ptr<GAlgorithm> galgo = nullptr;

public: 
    Tester() {}
    Tester(GAlgorithm* _galgo) : galgo(_galgo) {}

    void test_efficiency();
};

void Tester::test_efficiency() {
    int res_count = 0;
    std::vector<std::vector<long long>> res;
    long long int frequency, start, elapsed, sum, avg; 
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);


    // test 25%
    sum = 0;
    res_count++;
    res.push_back(std::vector<long long>());
    for(int i = 1; i <= STEP; i++) {
        for(int j = 0; j < CYCLES; j++) {
            // init
            graph = GraphGenerator::Generate(0.25, N * i, r_matrix);
            int v_end, v_start;
            v_start = rand() % graph->getRepresentation()->v_count;
            do {
                v_end = rand() % graph->getRepresentation()->v_count;
            } while(v_end == v_start);
            algorithm algo(MST_Prim, v_start, v_end);
            galgo = std::unique_ptr<GAlgorithm>(new GAlgorithm( (Graph**) &graph, algo));

            // algorithm
            start = read_QPC();
            galgo->SP_Dijkstra_execute();
            elapsed = read_QPC() - start; 

            std::cout << "Time [us] = " << (1000000.0 * elapsed) / frequency << std::endl; 
            sum += (double) (1000000.0 * elapsed) / frequency;
        }
        avg = sum / CYCLES;
        std::cout << "avgTime [us] = " << avg << std::endl;
        sum = 0;
        //res[res_count].push_back(avg);
    }
    //for(long long e : res[res_count])
      //  std::cout << "avg: " << e << std::endl;

    // test 50%
    // test 75%
    // test 99%


}

#endif