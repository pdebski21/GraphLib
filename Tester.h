#ifndef TESTER
#define TESTER

class Tester {
private:

public:
    void test_correctness_MST_Prim();
    void test_correctness_MST_Kruskal();
    void test_correctness_SP_Djikstra();
    void test_correctness_SP_Bellman_Ford();

    void test_efficiency();

};

#endif