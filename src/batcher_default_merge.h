#ifndef PARALLELSORTS_BATCHER_DEFAULT_MERGE_H
#define PARALLELSORTS_BATCHER_DEFAULT_MERGE_H

#include <iostream>
#include <thread>
#include <cmath>
#include <mutex>
#include <vector>
#include <random>

#include "timer_common.h"
#include "sequential_sorts.h"
#include "generator.h"
#include "check.h"

class batcher_default_merge {
public:
    void num_generate();
    int* arr;
    int arr_size;
    int stream_count;
    unsigned int count_per_piece;
    void sort_16();
    void print_array();
    batcher_default_merge(){ arr = new int[NUM_COUNT]; arr_size = NUM_COUNT;};
    void merge_2_arrays(const unsigned int &start1, const unsigned int &start2);
};


#endif //PARALLELSORTS_BATCHER_DEFAULT_MERGE_H