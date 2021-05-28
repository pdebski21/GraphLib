#ifndef MENU
#define MENU

#include <iostream>
#include <string>
#include "Tester.h"
#include "FileHandler.h"
#include "Core.h"

class Menu {
private:
    Tester tester;
    FileHandler fhandl;
    Core* core = nullptr;
public:
    Menu() {};
    Menu(GAlgorithm* galgo) : tester(galgo) {}
    Menu(Core* _core) : core(_core), tester(Tester(_core->getGalgo())) {}
    void menu_correctness();
    void menu_core();
};

void Menu::menu_core() {
    int control;
    std::string path;
    std::cout << "CORE MENU" << std::endl;
    std::cout << "1) Test functionality" << std::endl;
    std::cout << "2) Test efficiency" << std::endl;
    std::cout << "3) Exit" << std::endl;
    while(control != 3) {
        std::cin >> control;    
        switch(control) {
            case 1:
                std::cout << "Load File with graph" << std::endl;
                std::cout << "Enter data file name:" << std::endl;
                std::cin >> path; 
                fhandl.read(path);
                if(fhandl.getIsFileLoaded()) {
                    std::cout << "Graph in file:" << std::endl;
                    fhandl.getBuffer().display();
                    menu_correctness();
                } else {
                    std::cout << "Problem in reading file occured - check entered file path" << std::endl;
                }
                break;
            case 2:
                std::cout << "EFFICIENCY TEST" << std::endl;
                tester.test_efficiency(0.25, r_list);
                //tester.test_efficiency(0.25, r_matrix);
                //tester.test_efficiency(0.50, r_list);
                //tester.test_efficiency(0.50, r_matrix);
                //tester.test_efficiency(0.75, r_list);
                //tester.test_efficiency(0.75, r_matrix);
                //tester.test_efficiency(0.99, r_list);
                //tester.test_efficiency(0.99, r_matrix);
                tester.write_res();
                break;
            case 3:
                break;
            default:
                std::cout << "OPTION OUT OF MENU" << std::endl;
                break;
        }
    }
    
} 

void Menu::menu_correctness() {
    represent_type r_type;
    int control = 0;
    int rep_control = 0;
    while(control != 5) {
        while(rep_control != 1 && rep_control != 2) {
            std::cout << "Choose representation type:" << std::endl;
            std::cout << "1) Neighborhood Matrix:" << std::endl;
            std::cout << "2) Neighborhood List:" << std::endl;
            std::cin >> rep_control;
            switch(rep_control) {
                case 1:
                    r_type = r_matrix;
                    break;
                case 2:
                    r_type = r_list;
                    break;
                default:
                    std::cout << "OPTION OUT OF MENU :" << std::endl;
            }
        }
        core->init_graph(fhandl.getBuffer(), r_type);

        std::cout << "CORRECTNESS MENU" << std::endl;
        std::cout << "1) execute MST PRIM algorithm" << std::endl;
        std::cout << "2) execute MST Kruskal algorithm" << std::endl;
        std::cout << "3) execute Shortest Path Djikstra algorithm" << std::endl;
        std::cout << "4) execute Shortest Path Bellman-Ford algorithm" << std::endl;
        std::cout << "5) Exit" << std::endl;
        std::cin >> control;

        switch(control) {
            case 1:
                core->init_algorithm(fhandl.getBuffer(), MST_Prim);
                core->getGalgo()->MST_Prim_execute();
                core->getGalgo()->display_MST();
                break;
            case 2:
                core->init_algorithm(fhandl.getBuffer(), MST_Kruskal);
                core->getGalgo()->MST_Kruskal_execute();
                core->getGalgo()->display_MST();
                break;
            case 3:
                core->init_algorithm(fhandl.getBuffer(), SP_Dijkstra);
                core->getGalgo()->SP_Dijkstra_execute();
                core->getGalgo()->display_SP();
                break;
            case 4:
                core->init_algorithm(fhandl.getBuffer(), SP_Bellman_Ford);
                core->getGalgo()->SP_Bellman_Ford_execute();
                core->getGalgo()->display_SP();
                break;
            case 5:
                break;
            default:
                std::cout << "OPTION OUT OF MENU" << std::endl;
                break;
        }
    }
}

#endif