#ifndef GALGORITHM
#define GALGORITHM

#include "Graph.h"

class GAlgorithm {
private:    
    Graph& graph;
public:
    void MST_Kruskal_execute();
    void MST_Prim_execute();
    void SP_Dijkstra_execute();
    void SP_Bellman_Ford_execute();
};

#endif