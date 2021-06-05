#ifndef GALGORITHM
#define GALGORITHM

#include "Graph.h"
#include "StructLib.h"
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
#include <iostream>

class GAlgorithm {
private:    
    Graph* graph;
    algorithm algo;
    std::vector<edge> edges;
    std::vector<int> p;     // poprzednik
    std::vector<int> key;   // klucz
    std::vector<int> d;     // dystans
    std::vector<edge> mst;
    bool negativeWeights = false; 
    bool negativeCycles = false;
public:
    GAlgorithm() {}
    GAlgorithm(Graph** _graph, algorithm _algo);
    GAlgorithm(GAlgorithm& galo) {
        this->graph = galo.graph; 
        this->algo.a_type = galo.algo.a_type; 
        this->algo.v_start = galo.algo.v_start;
        this->algo.v_end = galo.algo.v_end;
    }
    ~GAlgorithm();
// algorithm execution
    void MST_Kruskal_execute();
    void MST_Prim_execute();
    void SP_Dijkstra_execute();
    void SP_Bellman_Ford_execute();
// I/O
    void display();
    void display_MST();
    void display_SP();
};



#endif