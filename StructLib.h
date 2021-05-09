#ifndef STRUCTLIB
#define STRUCTLIB

#include <iostream>
#include <vector>

enum algo_type { MST_Kruskal, MST_Prim, SP_Dijkstra, SP_Bellman_Ford };
enum represent_type { r_list, r_matrix };

struct edge {
    int beg;
    int end;
    int weight;
    void display() { std::cout << "beg (" << beg << ") end (" << end << ") weight(" << weight << ")" << std::endl; }
};
typedef edge edge;

struct algorithm {
    algo_type a_type;
    int v_start;
    int v_end;
};
typedef algorithm algorithm;

// poprawna struktura edges_cnt 0 -
// vertices_cnt 0 -
//
//
// wszystkie wierzchołki z zakresu 0 - veritces_cnt

struct GraphBuffer{
    int edges_cnt;
    int vertices_cnt;
    int start_v;
    int end_v;
    std::vector<edge> edges;
    void display() {
        std::cout << "edges count: " << edges_cnt << std::endl;
        std::cout << "vertices count: " << vertices_cnt << std::endl;
        std::cout << "start vertex: " << start_v << std::endl;
        std::cout << "end vertex" << end_v << std::endl;
        std::cout << "edges: " << std::endl;
        for(edge e : edges) {
            e.display();
        }
    }
};
typedef GraphBuffer GraphBuffer;


#endif