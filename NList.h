#ifndef HLIST
#define HLIST

#include "StructLib.h"
#include "Representation.h"
#include <vector>
#include <utility>
#include <forward_list>

class NList : public Representation {
private:
    std::forward_list<std::pair<int, int>>* list = nullptr;
public:
    NList(int _e_count, int _v_count, std::vector<edge> edges);
    ~NList();
    
    void display();
    std::vector<int> getAdj(int v_index);
    int getWeight(int u, int v);
    void setValue(int u, int v,int value);
};

    

#endif