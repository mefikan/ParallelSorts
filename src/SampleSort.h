#ifndef PARALLELSORTS_SAMPLESORT_H
#define PARALLELSORTS_SAMPLESORT_H


#include <iostream>
#include <thread>
#include <random>
#include <cstdio>
#include <array>
#include <unordered_map>
#include <map>

#include "timer_common.h"
#include "sequential_sorts.h"
#include "generator.h"
#include "check.h"
#include "thread_pool.h"
#include "timer_pool.h"

//получилось так, что работает как std::sort, возможно небольшое ускорение конечно, но и так вроде норм

class SampleSort {
public:
    void num_generate();
    int* arr;
    int *p_keys;
    int arr_size;
    const int p_count;
    int numbers_ind;
    void sort();
    void print_array();
    void separate(const int start, const int count);
    int binary_search(const int start, const int end, const int num);
    std::vector <std::vector <int>> blocks;
    SampleSort() : p_count(std::thread::hardware_concurrency())
    {   arr = new int[NUM_COUNT];
                    arr_size = NUM_COUNT;
                    blocks.resize(p_count);
    };
};


#endif //PARALLELSORTS_SAMPLESORT_H
