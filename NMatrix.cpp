#include "NMatrix.h"

NMatrix::NMatrix(int _e_count, int _v_count, std::vector<edge>& edges) : Representation(_e_count, _v_count) , mat(new int* [v_count]) {
    for(int i = 0; i < v_count; i++)
        mat[i] = new int;
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

}

std::vector<int> NMatrix::getAdj(int v_index) {
    std::vector<int> res;
    for(int i = 0; i < v_count; i++) 
        if(mat[v_index][i] > 0)
            res.push_back(mat[v_index][i]);
    return res;
}

int NMatrix::getWeight(int u, int v) {
    return mat[u][v];
}

void NMatrix::setValue(int u, int v,int value) {

}