#ifndef HLIST
#define HLIST

#include <vector>
#include <utility>
#include "Graph.h"
#include "Representation.h"

struct edge;

class NList : public Representation {
private:
    std::vector<std::pair<int, int>>* list = nullptr;
public:
    NList(int e_count, int v_count, std::vector<edge> edges);
    ~NList();
    
};

#endif