#ifndef PARALLELSORTS_BLOCK_SORT_H
#define PARALLELSORTS_BLOCK_SORT_H


#include <iostream>
#include <thread>
#include <random>

#include "timer_common.h"
#include "sequential_sorts.h"
#include "generator.h"
#include "check.h"
#include "thread_pool.h"
#include "timer_pool.h"

//Программа писалась по следующей логике:
//Сортируем куски и далее в соответствии с сетью выполняем слияния элементов,
//что один кусок будет наименьшим, и так далее
//на самом деле работает довольно эффективно, если сравнивать с другими реализациями

class block_sort {
public:
    void num_generate();
    int* arr;
    int arr_size;
    int stream_count;
    unsigned int count_per_piece;
    void sort_16();
    void print_array();
    block_sort(){ arr = new int[NUM_COUNT]; arr_size = NUM_COUNT;};
    void merge_2_arrays(const unsigned int &start1, const unsigned int &start2);
};

#endif //PARALLELSORTS_BLOCK_SORT_H
