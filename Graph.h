#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <exception>
#include "Representation.h"
#include "NList.h"
#include "NMatrix.h"
#include "StructLib.h"



// abstract class for graph representation
class Graph {
    private:
        Representation* rep = nullptr;
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