#include "GAlgorithm.h"

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
    // reprezentacja grafu nieskierowanego dla MST
    if(algo.a_type == MST_Prim) {
        graph->getRepresentation()->display();
        for(int i = 0; i < graph->getRepresentation()->v_count; i++)
            for(int j = 0; j < graph->getRepresentation()->v_count; j++) {
                if(graph->getRepresentation()->getWeight(i, j) != 0)
                    graph->getRepresentation()->setValue(j , i, graph->getRepresentation()->getWeight(i, j));
            }
        graph->getRepresentation()->display();
    }
}

GAlgorithm::~GAlgorithm() {}    

void GAlgorithm::MST_Prim_execute() {
    using vectorp = std::vector<std::pair<int, int*>>;
    using pairi = std::pair<int, int*>;

    std::vector<bool> mstSet;
    mstSet.resize(graph->getRepresentation()->v_count);
    vectorp v_key;
    v_key.resize(graph->getRepresentation()->v_count);

    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        key[i] = std::numeric_limits<int>::max();
        p[i] = -1;
        mstSet[i] = false;
        v_key[i] = std::pair<int, int*>(i, &key[i]);
    }
    // set start of MST
    key[algo.v_start] = 0;

// --------------------------------------------------------------------------------------------------- AS
    for(int i = 0; i < graph->getRepresentation()->v_count; i++)
    {
	for(int j = i + 1 ; j < graph->getRepresentation()->v_count; j++)
	    graph->getRepresentation()->setValue(j, i, graph->getRepresentation()->getWeight(i, j));
    }	
// --------------------------------------------------------------------------------------------------- AS

    std::make_heap(v_key.begin(), v_key.end(), [](pairi l, pairi r) { return *l.second > *r.second; });

    while (!v_key.empty()) {

        std::pop_heap(v_key.begin(), v_key.end(), [](pairi l, pairi r) { return *l.second > *r.second; });
        pairi u = v_key.back();
        v_key.pop_back();

        mstSet[u.first] = true;

        std::vector<int> adj = graph->getRepresentation()->getAdj(u.first);
        for (int v : adj) {
            // relaksacja krawędzi
            if (graph->getRepresentation()->getWeight(u.first, v) && mstSet[v] == false && graph->getRepresentation()->getWeight(u.first, v) < key[v]) {
                p[v] = u.first;
                key[v] = graph->getRepresentation()->getWeight(u.first, v); 
            }
            // reorganize heap if needed
            if (!std::is_heap(v_key.begin(), v_key.end(), [](pairi l, pairi r) { return *l.second > *r.second; }))
                std::make_heap(v_key.begin(), v_key.end(), [](pairi l, pairi r) { return *l.second > *r.second; });

        }
	    std::cout << std::endl;
    }

    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        if(p[i] >= 0) {
            edge(p[i], i, graph->getRepresentation()->getWeight(p[i], i)).display();
            mst.push_back( edge(p[i], i, graph->getRepresentation()->getWeight(p[i], i)) );
        }
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

void GAlgorithm::MST_Kruskal_execute() {
    
    int mst_edges = 0;
    // sort edges
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
  
        if (set_u != set_v)
        {   
            // push edeges into mst
            mst.push_back(e);
  
            // Merge two sets
            ds.merge(set_u, set_v);

            // Optymalizacja przy MST mającym V - 1 krawędzi zakończ algorytm
            mst_edges++;
            if(mst_edges == graph->getRepresentation()->v_count - 1)
                break;
        }
    }
}

void GAlgorithm::SP_Dijkstra_execute() {
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
                if(graph->getRepresentation()->getWeight(u.first, e) < 0)
                    negativeWeights = true;
            }
        }
        if(!std::is_heap(v_d.begin(), v_d.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; }))
            std::make_heap(v_d.begin(), v_d.end(), [](std::pair<int, int*> l, std::pair<int, int*> r){ return *l.second > *r.second; });
    }  
}

void GAlgorithm::SP_Bellman_Ford_execute() {

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
            negativeCycles = true;
            break;
        }
    }
}

void GAlgorithm::display_MST() {
    int mst_sum = 0;
    std::cout<<"Edge \tWeight\n"; 
    for (edge e : mst) {
        if(e.end != algo.v_start) {
            std::cout << e.beg << " - " << e.end << " \t" << graph->getRepresentation()->getWeight(e.beg, e.end) << std::endl;
            mst_sum += e.weight;
        }
    }
    std::cout << "MST = " << mst_sum << std::endl;
}

void GAlgorithm::display_SP() {
    std::cout << "End\t" << "Dist\t" << "Path" << std::endl;
    for(int i = 0; i < graph->getRepresentation()->v_count; i++) {
        std::vector<int> path;
        int prev = i;

	if(i != algo.v_start)
          path.push_back(i);    // AS dodatkowo wierzcholek koncowy sciezki
  
        while(p[prev] != algo.v_start && p[prev] != -1) {   
            if(p[prev] != algo.v_start)	
                path.push_back(p[prev]);
            prev = p[prev];
        }
        path.push_back(algo.v_start);
        std::cout << i << "\t|" << d[i] << "\t|";

        for(auto it = path.end() - 1; it >= path.begin() || it == path.begin() ; it--) {	// AS
            std::cout << " " << *it << ",";
	    if(it == path.begin())
	      break;
	}

        std::cout << std::endl;
    }

    // jeżeli są wagi ujemne wyniki mogą być złe
    if(negativeWeights) {
        std::cout << "WAGI UJEMNE - Wyniki moga byc niepoprawne" << std::endl;
        negativeWeights = false;
    }
    // jeżeli pojawiają się cykle ujemne wadliwy jest algorytm Bellamna-Forda
    if(negativeCycles) {
        std::cout << "CYKLE UJEMNE - Algorytm Bellmana-Forda nie nadaje sie do grafow z cyklami ujemnymi" << std::endl;
        negativeCycles = false;
    }
    algo.display();
}

void GAlgorithm::display() {
    algo.display();
}