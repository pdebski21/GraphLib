#ifndef GRAPHGENERATOR
#define GRAPHGENERATOR

#include "Graph.h"
#include "time.h"

#define MAXWEIGHT 15


class GraphGenerator {
    
private:
public:
    GraphGenerator() {
        srand(time(NULL));

    }

    static Graph* Random_Generate(int v_count, double density, represent_type r_type) {;
        return Generate(density, v_count, r_type);
    }

    static Graph* Generate(double density, int v_count, represent_type r_type) {
        std::vector<edge> edges;
        int e_count = v_count * (v_count - 1) * density / 2;
        int unique_edge = 0;
        for(int i = 0; unique_edge < e_count; i++) {
            edge tmp_e (rand()%v_count, rand()%v_count, rand()%MAXWEIGHT + 1);
            // niepowtarzające się krawędzie ? !!!!!!!!!!!!!
            unique_edge++;
            edges.push_back(tmp_e);
        }
        return new Graph(unique_edge, v_count, edges, r_type);
    }

};

#endif