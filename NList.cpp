#include "NList.h"

NList::NList(int _e_count, int _v_count, std::vector<edge> edges) 
    : Representation(_e_count, _v_count) , list( new std::forward_list<std::pair<int, int>>[_v_count+1] )
{
    for(edge e : edges)
        list[e.beg].push_front(std::pair<int, int>(e.beg, e.weight));
}

NList::~NList() {
    if(list != nullptr)
        delete list;
}

std::vector<int> NList::getAdj(int v_index) {
    std::vector<int> res;

    return res;
}

int NList::getWeight(int u, int v) {

}