#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <exception>
#include "NList.h"
#include "NMatrix.h"

struct edge {
    int beg;
    int end;
    int weight;
    void display() { std::cout << "beg (" << beg << ") end (" << end << ") weight(" << weight << ")" << std::endl; }
};

enum algo_type { MST_Kruskal, MST_Prim, SP_Dijkstra, SP_Bellman_Ford };
enum represent_type { r_list, r_matrix };

struct algorithm {
    algo_type a_type;
    int v_start;
    int v_end;
};

typedef edge edge;
typedef algorithm algorithm;

// abstract class for graph representation
class Graph {
    private:
        Representation* rep = nullptr;
        algorithm algo;
    public:
        Graph(int _e_count, int _v_count, std::vector<edge> _edges, represent_type rep_t) {
            
            switch(rep_t) {
                case r_matrix:
                    rep = new NMatrix(_e_count, _v_count, _edges);
                    break;
                case r_list:
                    rep = new NList(_e_count, _v_count, _edges);
                    break;
                default:
                    throw std::runtime_error("Contruction Error - wrong type of Graph representation");
            }
        }

        ~Graph() {
            if(rep != nullptr) {
                delete rep;
            }
        }

        // 
        // dane pośrednie get wypełnienie / gęstość
};

#endif