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
public:
    GAlgorithm();
    GAlgorithm(Graph** _graph, algorithm _algo) :  graph(*_graph), algo(_algo) {}
    GAlgorithm(GAlgorithm& galo) {
        this->graph = galo.graph; 
        this->algo.a_type = galo.algo.a_type; 
        this->algo.v_start = galo.algo.v_start;
        this->algo.v_end = galo.algo.v_end;
    }
    GAlgorithm(Graph** graph, algorithm algo);
    ~GAlgorithm();
// algorithm execution
    std::vector<edge> MST_Kruskal_execute();
    std::vector<edge> MST_Prim_execute();
    std::vector<edge> SP_Dijkstra_execute();
    std::vector<edge> SP_Bellman_Ford_execute();
// I/O
    void display();
    void display_MST();
    void display_SP();
};

// potrzebne:
// p[u] tablica poprzedników
// key[u] - waga najmniejszej krawędzi dla wierzchołka
// adj[u] - lista sąsiadów wierzchołka

GAlgorithm::GAlgorithm() {}
GAlgorithm::GAlgorithm(Graph** _graph, algorithm _algo) : graph(*_graph), algo(_algo) {
    key.resize(graph->getRepresentation()->v_count);
    p.resize(graph->getRepresentation()->v_count);
    d.resize(graph->getRepresentation()->v_count);
    // init krawędzie jeżeli algorytm Bellmana Forda
    if(algo.a_type == SP_Bellman_Ford) {
        for(int i = 0; i < graph->getRepresentation()->v_count - 1; i++) {
            std::vector<int> adj = graph->getRepresentation()->getAdj(i);
            for(int e : adj) {
                edges.push_back(edge(i, e, graph->getRepresentation()->getWeight(i, e)));
            }
        }
    }
    /*
    for(edge e : edges) {
        e.display();
    }
    */
}

GAlgorithm::~GAlgorithm() {}

std::vector<edge> GAlgorithm::MST_Prim_execute() {
    std::vector<bool> mstSet;
    mstSet.resize(graph->getRepresentation()->v_count);
    std::vector<std::pair<int, int*>> v_key;
    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        mstSet.push_back(false);
        key[i] = std::numeric_limits<int>::max();
        p[algo.v_start] = -1; // nie ma poprzednika dla wierzchołka startowego
    }
    key[algo.v_start] = 0;

    // wypełnij kolejkę
    for(int i = 0; i < graph->getRepresentation()->v_count; i++)
        v_key.push_back(std::pair<int, int*>(i, &key[i]));
    // przygotowanie kolejki / kopca dla wierzchołków grafu
    std::make_heap(v_key.begin(), v_key.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
    // wyświetl kolejkę <3

    // dopóki kolejka nie jest pusta wykonuj algorytm
    std::vector<int> out_of_pq;
    while(!v_key.empty()) {
        // pobierz z kolejki
        std::pop_heap(v_key.begin(), v_key.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
        std::pair<int, int*> u = v_key.back();
        v_key.pop_back();
        // zaznacz że należy do drzewa
        mstSet[u.first] = true;
        std::vector<int> v = graph->getRepresentation()->getAdj(u.first);   // list sąsiadów wierzchołka u

        for(int e : v) {
            if(mstSet[e] == false && graph->getRepresentation()->getWeight(u.first, e) < key[e] ) {
                
                key[e] = graph->getRepresentation()->getWeight(u.first, e);
                p[e] = u.first;
            }
        }
    }

    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        std::cout << "key:" << key[i] << "p:" << p[i] << std::endl;
    }
}

// test
void edge_sort(std::vector<edge>& edges) {
    std::sort(edges.begin(), edges.end(), [](edge l, edge r){ return l.weight < r.weight; });
}
// tesgt
void makeSet(int* group, int v_count) {
    for(int i = 0; i < v_count; i++)
        group[i] = i;
}
// test
int FindSet(int* group, int x) {
    return group[x];
}
// test
void Union(int* group, int v_count, int x, int y) {
    for(int i = 0; i < v_count; i++)
        if(group[i] == group[y])
            group[y] = group[x];
}

std::vector<edge> GAlgorithm::MST_Kruskal_execute() {

}

std::vector<edge> GAlgorithm::SP_Dijkstra_execute() {
    // init
    std::vector<std::pair<int, int*>> v_d;   // first index wierzchołka, second dystans
    for(int i = graph->getRepresentation()->v_count - 1; i >= 0; i--) {
        d[i] = std::numeric_limits<int>::max();
        p[i] = -1;
        v_d.push_back(std::pair<int, int*>(i, &d[i]));
    }
    d[algo.v_start] = 0;   // dystans do 1 wierzchołka to 0

    std::make_heap(v_d.begin(), v_d.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
    
    while(!v_d.empty()) {
        // zdejmij min element
        std::pop_heap(v_d.begin(), v_d.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
        std::pair<int, int*> u = v_d.back();
        v_d.pop_back();
        // dla każdego sąsiada min elementu wykonaj petle
        std::vector<int> adj = graph->getRepresentation()->getAdj(u.first); // sąsiedzi u
        std::cout << "odwiedzone z " << u.first << std::endl;
        for(int e : adj) {
            if(d[e] > *u.second + graph->getRepresentation()->getWeight(u.first, e)) {
                d[e] = *u.second + graph->getRepresentation()->getWeight(u.first, e);
                p[e] = u.first;
                std::cout << e << ": d " << d[e] << " p " << p[e] << std::endl;
            }
        }
    }  
// displ
    std::cout << "finalne wartosci:" << std::endl;
    for(int i = 0; i < graph->getRepresentation()->v_count; i ++) {
        std::cout << i << ": d " << d[i] << " p " << p[i] << std::endl;
    }

}

std::vector<edge> GAlgorithm::SP_Bellman_Ford_execute() {
    // init
    std::vector<std::pair<int, int*>> v_d;   // first index wierzchołka, second dystans
    for(int i = graph->getRepresentation()->v_count - 1; i >= 0; i--) {
        d[i] = 10000;
        p[i] = -1;
    }
    d[algo.v_start] = 0;

    // relaksacja dla każdej krawędzi 
    for(int i = 0; i < graph->getRepresentation()->v_count - 1; i++) {
        bool relaxed = false;
        for(edge e : edges) {
            if( d[e.end] > d[e.beg] + graph->getRepresentation()->getWeight(e.beg, e.end)) {
                d[e.end] = d[e.beg] + graph->getRepresentation()->getWeight(e.beg, e.end);
                p[e.end] = e.beg;
                relaxed = true;
                //std::cout << e.end << ": d " << d[e.end] << " p " << p[e.end] << std::endl;
            }
        }
        std::cout << relaxed;
        if(relaxed == false) break; // jeżeli nie wykonano żandej relaksacji skracamy algorytm
    }
    // sprawdzenie czy są cykle ujemne
    for(edge e : edges) {
        if(d[e.end] > d[e.beg] + graph->getRepresentation()->getWeight(e.beg, e.end))
            std::cout << "CYKLE UJEMNE - DO SOMETHING" << std::endl;
    }

// displ
    std::cout << "finalne wartosci:" << std::endl;
    for(int i = 0; i < graph->getRepresentation()->v_count; i ++) {
        std::cout << i << ": d " << d[i] << " p " << p[i] << std::endl;
    }

}


void GAlgorithm::display_MST() {
    /*
    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        std::cout << "p:" << p[i] << ", ";
    }
    std::cout << std::endl;
    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        std::cout << "key:" << key[i] << ", ";
    }
    */
    int mst_sum = 0;
    std::cout << "Edge \t Weight" << std::endl;
    for (int i = 0; i < graph->getRepresentation()->v_count; i++) {
        std::cout << "(" << p[i]<< ", " << i << ") \t" << key[i] << std::endl;
        mst_sum += key[i];
    }
    std::cout << "MST = " << mst_sum << std::endl;
}

void GAlgorithm::display_SP() {
    std::cout << "End\t" << "Dist\t" << "Path";
    /*
    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        std::vector<int> path;
        int prev = i;
        while(p[prev] != algo.v_start) {
            path.push_back(p[prev]);
            prev = p[prev];
        }
        path.push_back(algo.v_start);
        std::cout << i << "|" << d[i] << "|";
        for(int i = path.size(); i > 0; i--)
            std::cout << " " << path[i];
        std::cout << std::endl;
    }
    */
}

void GAlgorithm::display() {
    algo.display();
}

#endif