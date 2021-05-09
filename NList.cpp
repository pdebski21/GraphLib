#include "NList.h"


NList::NList(int _e_count, int _v_count, std::vector<edge> edges) 
    : Representation(_e_count, _v_count) , list( new std::vector<std::pair<int, int>>[_v_count+1] )
{
    for(edge e : edges)
        list[e.beg].push_back(std::pair<int, int>(e.beg, e.weight));
}

NList::~NList() {
    if(list != nullptr)
        delete list;
}