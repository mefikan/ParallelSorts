#ifndef PARALLELSORTS_NEW_BATCHER_H
#define PARALLELSORTS_NEW_BATCHER_H


#include "element.h"
#include "consts.h"
#include "sequential_sorts.h"

#include <vector>
#include <random>
#include <iostream>
#include <iomanip>

class new_batcher {
    void num_generate();
    unsigned int count_per_piece;
    void merge_2_arrays(const unsigned int &start1, const unsigned int &start2);
public:
    std::vector <Element> arr;
    new_batcher();
    new_batcher(int num_count);
    void sort_6_processors();
    void sort_16_processors();
    void print_array();
    int get_size() {return arr.size();};
    unsigned int get_count_per_piece(){return count_per_piece;};

};


#endif //PARALLELSORTS_NEW_BATCHER_H
