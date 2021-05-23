#ifndef GRAPHGENERATOR
#define GRAPHGENERATOR

#include "Graph.h"
#include "time.h"
#include <memory>

#define MAXWEIGHT 15


class GraphGenerator {
    
private:
public:
    GraphGenerator() {

    }

    static std::unique_ptr<Graph> Generate(double density, int v_count, represent_type r_type) {
        srand(time(NULL));

        std::vector<edge> edges;
        //int e_count = v_count * (v_count - 1) * density / 2;  // undirected graphs
        int e_count = v_count * v_count * density;              // directed graphs
        std::unique_ptr<Graph> g(new Graph(e_count, v_count, edges, r_type));

        int unique_edge = 0;
        for(int i = 0; unique_edge < e_count; i++) {
            edge tmp_e (rand()%v_count, rand()%v_count, rand()%MAXWEIGHT + 1);
            // pomiń jeżeli krawędź się powtarza
            if(g->getRepresentation()->getWeight(tmp_e.beg, tmp_e.end) > 0)
                continue;
            unique_edge++;
            //tmp_e.display();
            g->getRepresentation()->setValue(tmp_e.beg, tmp_e.end, tmp_e.weight);
        }

        return g;
    }

};

#endif