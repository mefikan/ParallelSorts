#ifndef PARALLELSORTS_SAMPLESORT_H
#define PARALLELSORTS_SAMPLESORT_H


#include <iostream>
#include <thread>
#include <random>
#include <cstdio>

#include "timer_common.h"
#include "sequential_sorts.h"
#include "generator.h"
#include "check.h"
#include "thread_pool.h"
#include "timer_pool.h"

class SampleSort {
public:
    void num_generate();
    int* arr;
    int arr_size;
    unsigned int p_count;
    void sort();
    void print_array();
    SampleSort(){ arr = new int[NUM_COUNT]; arr_size = NUM_COUNT; p_count = std::thread::hardware_concurrency();};
};


#endif //PARALLELSORTS_SAMPLESORT_H
