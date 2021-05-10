#ifndef CORE
#define CORE

#include "Graph.h"
#include "GAlgorithm.h"
#include "FileHandler.h"
#include "StructLib.h"

class Core {
private:
    Graph graph;
    GAlgorithm Galgo;
    FileHandler fh;
public:
    Core(GraphBuffer gbuffer);

    void init_algorithm();
    void init_graph();
};
    
    void Core::init_algorithm() {

    }

    void Core::init_graph() {
        
    }

#endif