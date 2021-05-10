#ifndef FILEHANDLER
#define FILEHANDLER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "StructLib.h"

class FileHandler {
    private:
        GraphBuffer g;
    public:
    // I/O
        GraphBuffer read(std::string inPath);
        void write(std::string outPath);
        void display_curr_data();
    // setters / getters
        GraphBuffer& getBuffer() { return g; }
        // std::string& getInPath() { return inPath; }
};

#endif