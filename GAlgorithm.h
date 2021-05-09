#ifndef GALGORITHM
#define GALGORITHM

#include "Graph.h"
#include <vector>


class GAlgorithm {
private:    
    Graph& graph;
    std::vector<int> p;
    std::vector<int> key;


public:
    std::vector<edge> MST_Kruskal_execute();
    std::vector<edge> MST_Prim_execute();
    std::vector<edge> SP_Dijkstra_execute();
    std::vector<edge> SP_Bellman_Ford_execute();
};

// potrzebne:
// p[u] tablica poprzedników
// key[u] - waga najmniejszej krawędzi dla wierzchołka
// adj[u] - lista sąsiadów wierzchołka

std::vector<edge> GAlgorithm::MST_Prim_execute() {

}

std::vector<edge> GAlgorithm::MST_Kruskal_execute() {

}



#endif