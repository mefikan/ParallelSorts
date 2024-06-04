#ifndef PARALLELSORTS_SAMPLESORT_H
#define PARALLELSORTS_SAMPLESORT_H

#include <iostream>
#include <thread>
#include <random>
#include <cstdio>
#include <array>
#include <QString>
#include <mutex>
#include <cstdint>

#include "timer_common.h"
#include "sequential_sorts.h"
#include "generator.h"
#include "check.h"

class SampleSort {
    int* arr;
    int *p_keys;
    int arr_size;
    int numbers_ind;
    const int p_count;
    std::vector <std::vector <int>> blocks;

    void num_generate();
    void print_array();
    void separate(const int start, const int count);
    int binary_search(const int start, const int end, const int num);
public:
    QString sort();
    SampleSort();
    SampleSort(int size);
};

#endif //PARALLELSORTS_SAMPLESORT_H
