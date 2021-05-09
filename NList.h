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
    NList(int e_count, int v_count, std::vector<edge> edges);
    ~NList();
    
    std::vector<int> getAdj(int v_index) = 0;
    int getWeight(int u, int v) = 0;
};

#endif