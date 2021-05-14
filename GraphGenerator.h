#ifndef GRAPHGENERATOR
#define GRAPHGENERATOR

#include "Graph.h"
#include "time.h"

#define MAXWEIGHT 15


class GraphGenerator {
    
    GraphGenerator() {
        srand(time(NULL));

    }

    Graph* Random_Generate(int v_max, double density, represent_type r_type) {;
        int v_count = rand() % (v_max + 1);

        return Generate(density, v_count, r_type);
    }

    Graph* Generate(double density, int v_count, represent_type r_type) {
        std::vector<edge> edges;
        int e_count = v_count * (v_count - 1) * density / 2;
        for(int i = 0; i < e_count; i++) {
            edge tmp_e (rand()%v_count, rand()%v_count, rand()%MAXWEIGHT + 1);

            // niepowtarzające się krawędzie ?
            edges.push_back(tmp_e);
        }
        return new Graph();
    }

};

#endif