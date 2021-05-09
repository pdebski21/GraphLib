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