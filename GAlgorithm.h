#ifndef GALGORITHM
#define GALGORITHM

#include "Graph.h"
#include "StructLib.h"
#include <vector>

class GAlgorithm {
private:    
    Graph* graph;
    algorithm algo;
    std::vector<int> p;
    std::vector<int> key;
public:
    GAlgorithm();
    GAlgorithm(Graph* graph, algorithm algo);
    ~GAlgorithm();
    std::vector<edge> MST_Kruskal_execute();
    std::vector<edge> MST_Prim_execute();
    std::vector<edge> SP_Dijkstra_execute();
    std::vector<edge> SP_Bellman_Ford_execute();
    
    // I/O
    void display();

};

// potrzebne:
// p[u] tablica poprzedników
// key[u] - waga najmniejszej krawędzi dla wierzchołka
// adj[u] - lista sąsiadów wierzchołka


GAlgorithm::GAlgorithm() {

}

GAlgorithm::GAlgorithm(Graph* _graph, algorithm _algo) : graph(_graph), algo(_algo) { 
    
}

GAlgorithm::~GAlgorithm() {

}

std::vector<edge> GAlgorithm::MST_Prim_execute() {

}

std::vector<edge> GAlgorithm::MST_Kruskal_execute() {

}

void GAlgorithm::display() {
    algo.display();
}

#endif