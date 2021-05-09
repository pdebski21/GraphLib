#ifndef NMATRIX
#define NMATRIX

#include "Graph.h"
#include "Representation.h"

struct edge;

class NMatrix : public Representation {
private:
    int ** mat;
public:
    NMatrix(int _e_count, int _vcount, std::vector<edge>& edges);
    ~NMatrix();
};

#endif