#include "Tester.h"



long long int read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
} 

void Tester::write_res() {
    FileHandler fh;
    fh.write("Results.csv", res);
}

void Tester::test_efficiency(double density,  represent_type r_type) {
    long long int frequency, start, elapsed, sum, avg; 
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
 
// PRMIN

    res.push_back(std::vector<long long>());
    for(int i = 1; i <= STEP; i++) {
        sum = 0;
        for(int j = 0; j < CYCLES; j++) {
            
            // init
            graph = GraphGenerator::Generate(density, N * i, r_type);
            int v_end, v_start;
            v_start = rand() % graph->getRepresentation()->v_count;
            do {
                v_end = rand() % graph->getRepresentation()->v_count;
            } while(v_end == v_start);
            algorithm algo(MST_Prim, v_start, v_end);
            galgo = std::unique_ptr<GAlgorithm>(new GAlgorithm( (Graph**) &graph, algo));

            // algorithm
            start = read_QPC();
            galgo->MST_Prim_execute();
            elapsed = read_QPC() - start; 

            //std::cout << "Time [us] = " << (1000000.0 * elapsed) / frequency << std::endl; 
            sum += (double) (1000000.0 * elapsed) / frequency;
        }
        avg = sum / CYCLES;
        std::cout << "avgTime [us] = " << avg << std::endl;
        res.at(res_count).push_back(avg);
    }
    for(long long e : res.at(res_count))
      std::cout << "avg: " << e << std::endl;
    res_count++;

// KRUSKAL

    res.push_back(std::vector<long long>());
    for(int i = 1; i <= STEP; i++) {
        sum = 0;
        for(int j = 0; j < CYCLES; j++) {
            
            // init
            graph = GraphGenerator::Generate(density, N * i, r_type);
            int v_end, v_start;
            v_start = rand() % graph->getRepresentation()->v_count;
            do {
                v_end = rand() % graph->getRepresentation()->v_count;
            } while(v_end == v_start);
            algorithm algo(MST_Kruskal, v_start, v_end);
            galgo = std::unique_ptr<GAlgorithm>(new GAlgorithm( (Graph**) &graph, algo));

            // algorithm
            start = read_QPC();
            galgo->MST_Kruskal_execute();
            elapsed = read_QPC() - start; 

            //std::cout << "Time [us] = " << (1000000.0 * elapsed) / frequency << std::endl; 
            sum += (double) (1000000.0 * elapsed) / frequency;
        }
        avg = sum / CYCLES;
        std::cout << "avgTime [us] = " << avg << std::endl;
        res.at(res_count).push_back(avg);
    }
    for(long long e : res.at(res_count))
      std::cout << "avg: " << e << std::endl;
    res_count++;



// BELLMAN-FORD
    res.push_back(std::vector<long long>());
    for(int i = 1; i <= STEP; i++) {
        sum = 0;
        for(int j = 0; j < CYCLES; j++) {
            
            // init
            graph = GraphGenerator::Generate(density, N * i, r_type);
            int v_end, v_start;
            v_start = rand() % graph->getRepresentation()->v_count;
            do {
                v_end = rand() % graph->getRepresentation()->v_count;
            } while(v_end == v_start);
            algorithm algo(SP_Bellman_Ford, v_start, v_end);
            galgo = std::unique_ptr<GAlgorithm>(new GAlgorithm( (Graph**) &graph, algo));

            // algorithm
            start = read_QPC();
            galgo->SP_Bellman_Ford_execute();
            elapsed = read_QPC() - start; 

            //std::cout << "Time [us] = " << (1000000.0 * elapsed) / frequency << std::endl; 
            sum += (double) (1000000.0 * elapsed) / frequency;
        }
        avg = sum / CYCLES;
        std::cout << "avgTime [us] = " << avg << std::endl;
        res.at(res_count).push_back(avg);
    }
    for(long long e : res.at(res_count))
      std::cout << "avg: " << e << std::endl;
    res_count++;
    
// DJIKSTRA
    res.push_back(std::vector<long long>());
    for(int i = 1; i <= STEP; i++) {
        sum = 0;
        for(int j = 0; j < CYCLES; j++) {
            
            // init
            graph = GraphGenerator::Generate(density, N * i, r_type);
            int v_end, v_start;
            v_start = rand() % graph->getRepresentation()->v_count;
            do {
                v_end = rand() % graph->getRepresentation()->v_count;
            } while(v_end == v_start);
            algorithm algo(SP_Dijkstra, v_start, v_end);
            galgo = std::unique_ptr<GAlgorithm>(new GAlgorithm( (Graph**) &graph, algo));

            // algorithm
            start = read_QPC();
            galgo->SP_Dijkstra_execute();
            elapsed = read_QPC() - start; 

            //std::cout << "Time [us] = " << (1000000.0 * elapsed) / frequency << std::endl; 
            sum += (double) (1000000.0 * elapsed) / frequency;
        }
        avg = sum / CYCLES;
        std::cout << "avgTime [us] = " << avg << std::endl;
        res.at(res_count).push_back(avg);
    }
    for(long long e : res.at(res_count))
      std::cout << "avg: " << e << std::endl;
    res_count++;

}