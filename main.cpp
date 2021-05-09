#include "FileHandler.h"

int main(int argc, char** argv) {
    FileHandler fh;
    fh.read("data.txt");
    fh.display_curr_data();
    return 0;
}