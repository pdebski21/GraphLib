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
    Core(GraphBuffer gbuffer);
    ~Core();

    void init_file(std::string path);
    void init_algorithm(GraphBuffer gbuffer, algo_type a_type);
    void init_graph(GraphBuffer gbuffer, represent_type r_type);
};

Core::Core() {
    init_file("data.txt");
    init_graph(fh.getBuffer(), r_matrix);
    init_algorithm(fh.getBuffer(), SP_Bellman_Ford);
    
    Galgo->display();
    //graph->display();
    // graph->getRepresentation()->display_adj(2);
    
    //Galgo->MST_Prim_execute();
    //Galgo->display_MST();

    //Galgo->SP_Dijkstra_execute();
    Galgo->SP_Bellman_Ford_execute();
}

Core::Core(GraphBuffer gbuffer) {

}

Core::~Core() {
    if(graph != nullptr) delete graph;
    if(Galgo != nullptr) delete Galgo;
}

void Core::init_file(std::string path) { fh.read(path); }

void Core::init_algorithm(GraphBuffer gbuffer, algo_type a_type) {
    algorithm algo(a_type ,gbuffer.start_v, gbuffer.end_v);
    Galgo = new GAlgorithm(&graph, algo);
}

void Core::init_graph(GraphBuffer gbuffer, represent_type r_type) {
    graph = new Graph(gbuffer.edges_cnt, gbuffer.vertices_cnt, gbuffer.edges, r_type);
}

#endif