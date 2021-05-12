#ifndef REPRESENTATION
#define REPRESENTATION

#include <vector>
#include <iostream>

class Representation {
public:
    int e_count;
    int v_count;
    Representation() = default;
    Representation(int _e_count, int _v_count) : e_count(_e_count), v_count(_v_count) {};
    virtual ~Representation() {};
    
    virtual void display() = 0;
    virtual std::vector<int> getAdj(int v_index) = 0;
    virtual int getWeight(int u, int v) = 0;
    virtual void setValue(int u, int v, int value) = 0;
    void display_adj(int v_index);
};



#endif