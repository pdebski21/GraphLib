#ifndef REPRESENTATION
#define REPRESENTATION

class Representation {
public:
    int e_count;
    int v_count;
    Representation();
    Representation(int _e_count, int _v_count) : e_count(_e_count), v_count(_v_count)  {};
    ~Representation() {};
    
};

#endif