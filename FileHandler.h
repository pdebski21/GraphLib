#ifndef FILEHANDLER
#define FILEHANDLER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Graph.h"

struct edge;

// poprawna struktura edges_cnt 0 -
// vertices_cnt 0 -
//
//
// wszystkie wierzchołki z zakresu 0 - veritces_cnt

struct GraphBuffer{
    int edges_cnt;
    int vertices_cnt;
    int start_v;
    int end_v;
    std::vector<edge> edges;
    void display() {
        std::cout << "edges count: " << edges_cnt << std::endl;
        std::cout << "vertices count: " << vertices_cnt << std::endl;
        std::cout << "start vertex: " << start_v << std::endl;
        std::cout << "end vertex" << end_v << std::endl;
        std::cout << "edges: " << std::endl;
        for(edge e : edges) {
            e.display();
        }
    }
};

typedef GraphBuffer GraphBuffer;

class FileHandler {
    private:
        GraphBuffer g;
        std::string inPath;
    public:
    // I/O
        GraphBuffer read(std::string inPath);
        void write(std::string outPath);
        void display_curr_data();
    // setters / getters
        GraphBuffer& getBuffer() { return g; }
        // std::string& getInPath() { return inPath; }
};

#endif