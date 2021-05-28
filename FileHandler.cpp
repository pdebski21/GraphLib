#include "FileHandler.h"

    // format pliku
    // 1 linia edges_cnt, vertices_cnt, start_v, end_v
    // wierzchołki numerowane od 0
    // w każdej lini opis krawędzi w formie
    // start_v, end_v, waga/przepustowosc
    // dla MTS nieskierowane dla scieżki i przepływu traktowane jako skierowane

GraphBuffer& FileHandler::read(std::string inPath)
{
    edge tmpEdge;
    std::ifstream fs(inPath, std::ifstream::in);
    if (fs.is_open())
    {
        fs >> g.edges_cnt >> g.vertices_cnt >> g.start_v >> g.end_v;    // 1 linia
        for(int i = 0; i < g.edges_cnt; i++) {
            fs >> tmpEdge.beg >> tmpEdge.end >> tmpEdge.weight ;
            g.edges.push_back(tmpEdge);
        }
        this->isFileLoaded = true;
    }
    else
    {
        std::cout << "reading file failed - check file name" << std::endl;
    }
    return g;
}

void FileHandler::write(std::string outPath, std::vector<std::vector<long long>>& res) 
{
    std::ofstream fs(outPath, std::ofstream::out);
    if(fs.is_open()) {
        for( auto v : res ) {
            for( auto e : v ) {
                fs << e << ";";
            }
            fs << std::endl;
        }
    } else {
        std::cout << "error - opening file failed" << std::endl;
    }
    fs.close();
}

void FileHandler::display_curr_data()
{
    g.display();
}