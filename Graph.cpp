#include "Graph.h"

Graph::Graph(int _e_count, int _v_count, std::vector<edge> _edges, represent_type rep_t) {
    switch(rep_t) {
        case r_matrix:
            rep = new NMatrix(_e_count, _v_count, _edges);
            break;
        case r_list:
            rep = new NList (_e_count, _v_count, _edges);
            break;
        default:
            throw std::runtime_error("Contruction Error - wrong type of Graph representation");
    }   
}

Graph::~Graph() {
    if(rep != nullptr)
        rep->~Representation();
}