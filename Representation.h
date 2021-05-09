#ifndef REPRESENTATION
#define REPRESENTATION

#include<vector>

class Representation {
public:
    int e_count;
    int v_count;
    Representation() = default;
    Representation(int _e_count, int _v_count) : e_count(_e_count), v_count(_v_count) {};
    ~Representation() = default;
    
    virtual std::vector<int> getAdj(int v_index);
    virtual int getWeight(int u, int v);
};

#endif