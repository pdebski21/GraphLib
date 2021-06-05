#ifndef CORE
#define CORE

#include "Graph.h"
#include "StructLib.h"
#include "GAlgorithm.h"
#include "FileHandler.h"
// #include "GraphGenerator.h"
#include <exception>
#include <string>

class Core {
private:
    Graph* graph = nullptr;
    GAlgorithm* Galgo = nullptr;
    FileHandler fh;
    // GraphGenerator Ggenerator;
public:
    Core();
    ~Core();

    void init_file(std::string path);
    void init_algorithm(GraphBuffer gbuffer, algo_type a_type);
    void init_graph(GraphBuffer gbuffer, represent_type r_type);
// setters && getters
    Graph* getGraph() { return graph; }
    GAlgorithm* getGalgo() { return Galgo; }
};




#endif