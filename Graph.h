#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <exception>
#include "StructLib.h"
#include "Representation.h"
#include "NList.h"
#include "NMatrix.h"


// abstract class for graph representation
class Graph {
private:
    Representation* rep = nullptr;
public:
    Graph() {};
    Graph(Graph*& graph) { rep = graph->rep; }
    Graph(int _e_count, int _v_count, std::vector<edge> _edges, represent_type rep_t);
    ~Graph();
// settery i gettery
    Representation* getRepresentation() { return rep; }
    void display() { rep->display(); }
// dane pośrednie get wypełnienie / gęstość
};



#endif