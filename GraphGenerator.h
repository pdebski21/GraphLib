#ifndef GRAPHGENERATOR
#define GRAPHGENERATOR

#include "Graph.h"
#include "time.h"

class GraphGenerator {
    
    GraphGenerator() {
        srand(time(NULL));

    }

    Graph Random_Generate(int v_max) {
        double density = (rand() % 1000000) / 100000000.0 ;
        int v_count = rand() % (v_max + 1);

        return Generate(density, v_count);
    }

    Graph Generate(double density, int v_count) {
        
    }

};

#endif