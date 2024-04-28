#ifndef PARALLELSORTS_BATCHER_TRUE_BITONIC_MERGE_H
#define PARALLELSORTS_BATCHER_TRUE_BITONIC_MERGE_H


#include <iostream>
#include <thread>
#include <random>
#include <cmath>

#include "timer_common.h"
#include "sequential_sorts.h"
#include "generator.h"
#include "check.h"
#include "thread_pool.h"
#include <mutex>


//works only with arrays, where condition arr.size()%16 == 0 is true
/*
 * Данная программа выделяется тем, что использует конкретную сеть для сортировки массива длиной
 * в данном случае 16 элементов
 */
class batcher_true_bitonic_merge {
public:
    void num_generate();
    std::vector <std::vector <std::pair<int, int>>> indexes;
    int* arr;
    int arr_size;
    int stream_count;
    unsigned int count_per_piece;
    void sort();
    void print_array();
    batcher_true_bitonic_merge();
    void merge(const unsigned int &start1, const unsigned int &start2);
};


#endif //PARALLELSORTS_BATCHER_TRUE_BITONIC_MERGE_H
