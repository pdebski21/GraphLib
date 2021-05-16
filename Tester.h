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

    void test_correctness_MST_Prim();
    void test_correctness_MST_Kruskal();
    void test_correctness_SP_Djikstra();
    void test_correctness_SP_Bellman_Ford();

    void test_efficiency();
// getters
    Graph* getGraph() { return graph; }
    GAlgorithm* getGalgo() { return galgo; }
    void setGraph(Graph* _graph) { graph = _graph; }
    void setGalgo(GAlgorithm* _galgo) { galgo = _galgo; }
};

void Tester::test_correctness_MST_Prim() {
    galgo->MST_Prim_execute();
}

void Tester::test_correctness_MST_Kruskal() {

}

void Tester::test_correctness_SP_Djikstra() {}
void Tester::test_correctness_SP_Bellman_Ford() {}
void Tester::test_efficiency() {}

#endif