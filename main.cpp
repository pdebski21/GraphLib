#include "FileHandler.h"
#include "Graph.h"
#include "Core.h"
#include "Menu.h"

int main(int argc, char** argv) {
    /*
    FileHandler fh;
    fh.read("data.txt");
    fh.display_curr_data();
    */
    Core c;
    Menu m(&c);
    m.menu_core();
    return 0;
}