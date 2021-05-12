#include "Representation.h"

void Representation::display_adj(int v_index) { 
    std::cout << "Adj[" << v_index << "] { ";
    for(int e : getAdj(v_index))
        std::cout << e << ", ";
    std::cout << "}" << std::endl;;         
}