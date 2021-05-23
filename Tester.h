#ifndef TESTER
#define TESTER

#define N 100
#define STEP 2
#define CYCLES 100
#include <memory>
#include "GraphGenerator.h"
#include "Graph.h"
#include "GAlgorithm.h"


class Tester {
private:
    std::unique_ptr<Graph> graph = nullptr;
    GAlgorithm* galgo = nullptr;

public: 
    Tester() {}
    Tester(Graph* _graph, GAlgorithm* _galgo) : graph(_graph), galgo(_galgo) {}

    void test_efficiency();
};

void Tester::test_efficiency() {

    graph = GraphGenerator::Generate(0.50, 5, r_matrix);
    graph->display();

    // test 25%
    for(int i = 0; i < CYCLES; i++) {

    }

    // test 50%
    // test 75%
    // test 99%


}

#endif