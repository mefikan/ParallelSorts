#ifndef PARALLELSORTS_BLOCK_SORT_H
#define PARALLELSORTS_BLOCK_SORT_H


#include <iostream>
#include <thread>
#include <random>
#include <Qstring>
#include <QtMath>
#include <QDebug>

#include "timer_common.h"
#include "sequential_sorts.h"
#include "generator.h"
#include "check.h"

//Программа писалась по следующей логике:
//Сортируем куски и далее в соответствии с сетью выполняем слияния элементов,
//что один кусок будет наименьшим, и так далее
//на самом деле работает довольно эффективно, если сравнивать с другими реализациями

class block_sort {
    int* arr;
    int arr_size;
    int stream_count;
    unsigned int count_per_piece;
    void num_generate();
    void print_array();
    void merge_2_arrays(const unsigned int &start1, const unsigned int &start2);
public:
    QString sort_16();
    block_sort(int size){ arr = new int[size]; arr_size = size;};
    block_sort(){ arr = new int[NUM_COUNT]; arr_size = NUM_COUNT;};
};

#endif //PARALLELSORTS_BLOCK_SORT_H
