#ifndef GALGORITHM
#define GALGORITHM

#include "Graph.h"
#include "StructLib.h"
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
#include <iostream>

class GAlgorithm {
private:    
    Graph* graph;
    algorithm algo;
    std::vector<edge> edges;
    std::vector<int> p;     // poprzednik
    std::vector<int> key;   // klucz
    std::vector<int> d;     // dystans
public:
    GAlgorithm() {}
    GAlgorithm(Graph** _graph, algorithm _algo);
    GAlgorithm(GAlgorithm& galo) {
        this->graph = galo.graph; 
        this->algo.a_type = galo.algo.a_type; 
        this->algo.v_start = galo.algo.v_start;
        this->algo.v_end = galo.algo.v_end;
    }
    ~GAlgorithm();
// algorithm execution
    std::vector<edge> MST_Kruskal_execute();
    std::vector<edge> MST_Prim_execute();
    std::vector<edge> SP_Dijkstra_execute();
    std::vector<edge> SP_Bellman_Ford_execute();
// I/O
    void display();
    void display_MST();
    void display_SP();
};

// potrzebne:
// p[u] tablica poprzedników
// key[u] - waga najmniejszej krawędzi dla wierzchołka
// adj[u] - lista sąsiadów wierzchołka


GAlgorithm::GAlgorithm(Graph** _graph, algorithm _algo) : graph(*_graph), algo(_algo) {
    key.resize(graph->getRepresentation()->v_count);
    p.resize(graph->getRepresentation()->v_count);
    d.resize(graph->getRepresentation()->v_count);
    // init krawędzie jeżeli algorytm Bellmana Forda
    if(algo.a_type == SP_Bellman_Ford || algo.a_type == MST_Kruskal) {
        for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
            std::vector<int> adj = graph->getRepresentation()->getAdj(i);
            for(int e : adj) {
                edges.push_back(edge(i, e, graph->getRepresentation()->getWeight(i, e)));
            }
        }
    }
    /*
    for(edge e : edges) {
        e.display();
    }
    */
}

GAlgorithm::~GAlgorithm() {}

std::vector<edge> GAlgorithm::MST_Prim_execute() {
    std::vector<bool> mstSet;
    mstSet.resize(graph->getRepresentation()->v_count);

    std::vector<std::pair<int, int*>> v_key;
    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        mstSet.push_back(false);
        key[i] = std::numeric_limits<int>::max();
        p[algo.v_start] = -1; // nie ma poprzednika dla wierzchołka startowego
    }
    key[algo.v_start] = 0;

    // wypełnij kolejkę
    for(int i = 0; i < graph->getRepresentation()->v_count; i++)
        v_key.push_back(std::pair<int, int*>(i, &key[i]));
    // przygotowanie kolejki / kopca dla wierzchołków grafu
    std::make_heap(v_key.begin(), v_key.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
    // wyświetl kolejkę <3

    // dopóki kolejka nie jest pusta wykonuj algorytm
    std::vector<int> out_of_pq;
    while(!v_key.empty()) {
        // pobierz z kolejki
        std::pop_heap(v_key.begin(), v_key.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
        std::pair<int, int*> u = v_key.back();
        v_key.pop_back();
        // zaznacz że należy do drzewa
        mstSet[u.first] = true;
        std::vector<int> v = graph->getRepresentation()->getAdj(u.first);   // list sąsiadów wierzchołka u

        for(int e : v) {
            std::cout << u.first << "-" << e << std::endl;
            //mstSet[e] == false
            if(mstSet[e] == false && graph->getRepresentation()->getWeight(u.first, e) < key[e] ) {
                key[e] = graph->getRepresentation()->getWeight(u.first, e);
                p[e] = u.first;
                //std::cout << e << "_key:" << key[e] << " p:" << p[e] << std::endl;
            }
            
            if(mstSet[e] == false && graph->getRepresentation()->getWeight(e, u.first) < key[e] ) {
                key[e] = graph->getRepresentation()->getWeight(e, u.first);
                p[e] = u.first;
                //std::cout << e << "_key:" << key[u.first] << " p:" << p[u.first] << std::endl;
            }
                  
        }
        // jeżeli naruszyliśmy strukture koprac - napraw
        if(!std::is_heap(v_key.begin(), v_key.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; }))
            std::make_heap(v_key.begin(), v_key.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
    }

    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        std::cout << i << "_key:" << key[i] << " p:" << p[i] << std::endl;
    }
}

// test
void edge_sort(std::vector<edge>& edges) {
    std::sort(edges.begin(), edges.end(), [](edge l, edge r){ return l.weight < r.weight; });
}


// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;
  
    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
  
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
  
            //every element is parent of itself
            parent[i] = i;
        }
    }

    ~DisjointSets() {
        //delete parent;
        //delete rnk;
    }
  
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
  
        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
  
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

std::vector<edge> GAlgorithm::MST_Kruskal_execute() {
int mst_wt = 0; // Initialize result
  
    // Sort edges in increasing order on basis of cost
    for(edge e : edges) {
        e.display();
    }
    edge_sort(edges);
    
    // Create disjoint sets
    DisjointSets ds(graph->getRepresentation()->v_count);
  
    // Iterate through all sorted edges
    for (edge e : edges)
    {
        int u = e.beg;
        int v = e.end;
  
        int set_u = ds.find(u);
        int set_v = ds.find(v);
  
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            //std::cout << u << " - " << v << " | " << e.weight << std::endl;
  
            // Update MST weight
            mst_wt += e.weight;
  
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }

    //std::cout << "MST = " << mst_wt << std::endl;
}


std::vector<edge> GAlgorithm::SP_Dijkstra_execute() {
    // init
    // using vectorp = std::vector<std::pair<int, int*>>;
    std::vector<std::pair<int, int*>> v_d;   // first index wierzchołka, second dystans
    for(int i = graph->getRepresentation()->v_count - 1; i >= 0; i--) {
        d[i] = std::numeric_limits<int>::max();
        p[i] = -1;
        v_d.push_back(std::pair<int, int*>(i, &d[i]));
    }
    d[algo.v_start] = 0;   // dystans do 1 wierzchołka to 0

    std::make_heap(v_d.begin(), v_d.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
    
    while(!v_d.empty()) {
        // zdejmij min element
        std::pop_heap(v_d.begin(), v_d.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
        std::pair<int, int*> u = v_d.back();
        v_d.pop_back();
        // dla każdego sąsiada min elementu wykonaj petle
        std::vector<int> adj = graph->getRepresentation()->getAdj(u.first); // sąsiedzi u
        for(int e : adj) {
            if(d[e] > *u.second + graph->getRepresentation()->getWeight(u.first, e)) {
                d[e] = *u.second + graph->getRepresentation()->getWeight(u.first, e);
                p[e] = u.first;
            }
        }
        if(!std::is_heap(v_d.begin(), v_d.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; }))
            std::make_heap(v_d.begin(), v_d.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
    }  
}

std::vector<edge> GAlgorithm::SP_Bellman_Ford_execute() {
    // init
    std::vector<std::pair<int, int*>> v_d;   // first index wierzchołka, second dystans
    for(int i = graph->getRepresentation()->v_count - 1; i >= 0; i--) {
        d[i] = 10000;
        p[i] = -1;
    }
    d[algo.v_start] = 0;

    // relaksacja dla każdej krawędzi 
    for(int i = 0; i < graph->getRepresentation()->v_count - 1; i++) {
        bool relaxed = false;
        for(edge e : edges) {
            if( d[e.end] > d[e.beg] + graph->getRepresentation()->getWeight(e.beg, e.end)) {
                d[e.end] = d[e.beg] + graph->getRepresentation()->getWeight(e.beg, e.end);
                p[e.end] = e.beg;
                relaxed = true;
            }
        }
        if(relaxed == false) break; // jeżeli nie wykonano żandej relaksacji skracamy algorytm
    }
    // sprawdzenie czy są cykle ujemne
    for(edge e : edges) {
        if(d[e.end] > d[e.beg] + graph->getRepresentation()->getWeight(e.beg, e.end)) {
            std::cout << "CYKLE UJEMNE - DO SOMETHING" << std::endl;
            break;
        }
    }
}

void GAlgorithm::display_MST() {
    int mst_sum = 0;
    std::cout<<"Edge \tWeight\n"; 
    for (int i = 0; i < graph->getRepresentation()->v_count; i++) {
        if(p[i] != p[algo.v_start]) {
            std::cout << p[i] << " - " << i << " \t" << graph->getRepresentation()->getWeight(p[i], i) << std::endl;
            mst_sum += key[i];
        }
    }
    std::cout << "MST = " << mst_sum << std::endl;
}

void GAlgorithm::display_SP() {
    std::cout << "End\t" << "Dist\t" << "Path" << std::endl;
    
    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        std::vector<int> path;
        int prev = i;
        while(p[prev] != algo.v_start && prev != -1) {
            if(p[prev] != p[algo.v_start])
                path.push_back(p[prev]);
            prev = p[prev];
        }
        path.push_back(algo.v_start);
        std::cout << i << "\t|" << d[i] << "\t|";
        for(auto it = path.end() - 1; it >= path.begin() || it == path.begin() ; it--) {
            std::cout << " " << *it << ","; 
        }
        std::cout << std::endl;
    }
}

void GAlgorithm::display() {
    algo.display();
}

#endif