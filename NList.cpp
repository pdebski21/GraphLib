#include "NList.h"

NList::NList(int _e_count, int _v_count, std::vector<edge> edges) 
    : Representation(_e_count, _v_count) , list( new std::forward_list<std::pair<int, int>>[_v_count+1] )
{    
    for(edge e : edges)
        list[e.beg].push_front(std::pair<int, int>(e.end, e.weight));
}

NList::~NList() {
    //if(list != nullptr) {	// AS
    //    delete list;
    //}
}

void NList::display() {
    std::cout << "vertex count: " << v_count << std::endl;
    std::cout << "edges count: " << e_count << std::endl;
    for(int i = 0; i < v_count; i++) {
        std::cout << "v(" << i << "): ";
        for(std::pair<int, int> e : list[i]) {
            std::cout << "[" << e.first << ", " << e.second << "], ";
        }
        std::cout << std::endl;
    }
}

std::vector<int> NList::getAdj(int v_index) {
    std::vector<int> res;
    if(v_index < v_count && v_index >=0) {
        for(std::pair<int, int> e : list[v_index]) {
            res.push_back(e.first);
        }
    }
    return res;
}

int NList::getWeight(int u, int v) {
    for(std::pair<int, int> e : list[u])
        if(e.first == v)
            return e.second;
    return 0;
}


void NList::setValue(int u, int v,int value) {
    for(std::pair<int, int> e : list[u])
        if(e.first == v  && e.second != 0) {
            e.second = value;
            return;
        }
    list[u].push_front(std::pair<int, int>(v, value));
    
}