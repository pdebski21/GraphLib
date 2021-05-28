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
        bool isFileLoaded = false;
    public:
    // I/O
        GraphBuffer& read(std::string inPath);
        void write(std::string outPath, std::vector<std::vector<long long>>& res);
        void display_curr_data();
    // setters / getters
        GraphBuffer& getBuffer() { return g; }
        bool getIsFileLoaded() { return isFileLoaded; };
        // std::string& getInPath() { return inPath; }
};

#endif