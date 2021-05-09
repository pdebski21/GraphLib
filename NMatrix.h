#ifndef NMATRIX
#define NMATRIX

#include "Representation.h"
#include "StructLib.h"

class NMatrix : public Representation {
private:
    int ** mat;
public:
    NMatrix(int _e_count, int _vcount, std::vector<edge>& edges);
    ~NMatrix();

    std::vector<int> getAdj(int v_index);
    int getWeight(int u, int v);

};



#endif