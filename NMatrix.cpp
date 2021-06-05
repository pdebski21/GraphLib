#include "NMatrix.h"

NMatrix::NMatrix(int _e_count, int _v_count, std::vector<edge>& edges) : Representation(_e_count, _v_count) {
    // allocate memory for matrix
    mat = new int*[_v_count];
    for(int i = 0; i < v_count; i++)
        mat[i] = new int[v_count];
    // fill with zeros
    for(int i = 0; i < v_count; i++)
        for(int j = 0; j < v_count; j++)
            mat[i][j] = 0;
    // fill with edges values
    for(edge e : edges)
        mat[e.beg][e.end] = e.weight;
}

NMatrix::~NMatrix() {
    if(mat != nullptr) {
        for(int i = 0; i < v_count; i++)
            if(mat[i] != nullptr)
                delete mat[i];
        delete mat;
    }
}

void NMatrix::display() {
    std::cout << "vertex count: " << v_count << std::endl;
    std::cout << "edges count: " << e_count << std::endl;
    for(int i = 0; i < v_count; i++) {
        std::cout << i  << ": { ";
        for(int j = 0; j < v_count; j++) {
            std::cout << mat[i][j] << ", ";
        }
        std::cout << "}" << std::endl;
    }
}

std::vector<int> NMatrix::getAdj(int v_index) {
    std::vector<int> res;
    if(v_index < v_count && v_index >=0) {
        for(int i = 0; i < v_count; i++) 
            if(mat[v_index][i] != 0)
                res.push_back(i);
    }
    return res;
}

int NMatrix::getWeight(int u, int v) {
    return mat[u][v];
}

void NMatrix::setValue(int u, int v,int value) {
    mat[u][v] = value;
}