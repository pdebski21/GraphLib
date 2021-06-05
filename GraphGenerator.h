#ifndef GRAPHGENERATOR
#define GRAPHGENERATOR

#include "Graph.h"
#include "time.h"
#include <memory>

#define MAXWEIGHT 15

class GraphGenerator {
public:
    GraphGenerator() {}
    static std::unique_ptr<Graph> Generate(double density, int v_count, represent_type r_type);

};

#endif