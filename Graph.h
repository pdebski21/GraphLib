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
        Graph(int _e_count, int _v_count, std::vector<edge> _edges, represent_type rep_t) {
            NMatrix matrix(_e_count, _v_count, _edges);
            NList list(_e_count, _v_count, _edges);
            switch(rep_t) {
                case r_matrix:
                    rep = &matrix;
                    break;
                case r_list:
                    rep = &list;
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
// settery i gettery
    Representation* getRepresentation() { return rep; }

// dane pośrednie get wypełnienie / gęstość
};

#endif