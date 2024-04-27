#ifndef PARALLELSORTS_BATCHER_TRUE_MERGE_H
#define PARALLELSORTS_BATCHER_TRUE_MERGE_H


#include <iostream>
#include <thread>
#include <random>

#include "timer_common.h"
#include "sequential_sorts.h"
#include "generator.h"
#include "check.h"


//works only for 16 elements
class batcher_true_merge {
public:
    void num_generate();
    int* arr;
    int arr_size;
    int stream_count;
    unsigned int count_per_piece;
    void sort_16();
    void print_array();
    batcher_true_merge(){ arr = new int[NUM_COUNT]; arr_size = NUM_COUNT;};
    void merge(const unsigned int &start1, const unsigned int &start2);
};


#endif //PARALLELSORTS_BATCHER_TRUE_MERGE_H
