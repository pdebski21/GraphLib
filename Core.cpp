#include "Core.h"

Core::Core() {}

Core::~Core() {
    if(graph != nullptr) delete graph;
    if(Galgo != nullptr) delete Galgo;
}

void Core::init_file(std::string path) { fh.read(path); }

void Core::init_algorithm(GraphBuffer gbuffer, algo_type a_type) {
    algorithm algo(a_type ,gbuffer.start_v, gbuffer.end_v);
    if(Galgo != nullptr) { delete Galgo; }
    Galgo = new GAlgorithm(&graph, algo);
}

void Core::init_graph(GraphBuffer gbuffer, represent_type r_type) {
    if(graph != nullptr) { delete graph; }
    graph = new Graph(gbuffer.edges_cnt, gbuffer.vertices_cnt, gbuffer.edges, r_type);
}