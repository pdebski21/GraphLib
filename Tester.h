#ifndef TESTER
#define TESTER

#include "GraphGenerator.h"
#include "Graph.h"
#include "GAlgorithm.h"

class Tester {
private:
    Graph* graph = nullptr;
    GAlgorithm* galgo = nullptr;

public: 
    Tester() {}
    Tester(Graph* _graph, GAlgorithm* _galgo) : graph(_graph), galgo(_galgo) {}

    void test_efficiency();
// getters
    Graph* getGraph() { return graph; }
    GAlgorithm* getGalgo() { return galgo; }
    void setGraph(Graph* _graph) { graph = _graph; }
    void setGalgo(GAlgorithm* _galgo) { galgo = _galgo; }
};

void Tester::test_efficiency() {
    std::cout << "eff test" << std::endl;
    Graph g(*(GraphGenerator::Generate(5,0.2, r_matrix)));
    g.display();

}

#endif