#ifndef MENU
#define MENU

#include <iostream>
#include <string>
#include "Tester.h"
#include "FileHandler.h"

class Menu {
private:
    Tester tester;
    FileHandler fhandl;
public:
    void menu_correctness();
    void menu_core();
};

void Menu::menu_core() {
    int control;
    std::cout << "CORE MENU" << std::endl;
    std::cout << "1) Test functionality" << std::endl;
    std::cout << "2) Test efficiency" << std::endl;
    std::cout << "3) Exit" << std::endl;
    std::cin >> control;
    while(control != 3) {
        switch(control) {
            case 1:
                menu_correctness();
                break;
            case 2:
                // tester.test_efficiency();
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
    int control;
    std::string path;
    std::cout << "CORRECTNESS MENU" << std::endl;
    std::cout << "1) execute MST PRIM algorithm" << std::endl;
    std::cout << "2) execute MST Kruskal algorithm" << std::endl;
    std::cout << "3) execute Shortest Path Djikstra algorithm" << std::endl;
    std::cout << "4) execute Shortest Path Bellman-Ford algorithm" << std::endl;
    std::cout << "5) Load File with graph" << std::endl;
    std::cout << "6) Exit" << std::endl;
    std::cin >> control;
    while(control != 4) {
        switch(control) {
            case 1:
                tester.test_correctness_MST_Prim();
                break;
            case 2:
                tester.test_correctness_MST_Kruskal();
                break;
            case 3:
                tester.test_correctness_SP_Djikstra();
                break;
            case 4:
                tester.test_correctness_SP_Bellman_Ford();
                break;
            case 5:
                std::cout << "Enter data file name:" << std::endl;
                std::cin >> path; 
                fhandl.read(path);
                if(fhandl.getIsFileLoaded()) {
                    std::cout << "Graph in file:" << std::endl;
                    fhandl.getBuffer().display();
                } else {
                    std::cout << "Problem in reading file occured - check entered file path" << std::endl;
                }
                break;
            default:
                std::cout << "OPTION OUT OF MENU" << std::endl;
                break;
        }
    }
} 

#endif