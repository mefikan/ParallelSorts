#ifndef BATCHER_SORT_H
#define BATCHER_SORT_H

#include <iostream>
#include <thread>
#include <cmath>

#include "timer.h"
#include "sequential_sorts.h"
#include "generator.h"
#include "show.h"
#include "check.h"

class batcher_sort
{
	int* base_buf;
	static std::pair <int*, int*> merge_arrays_and_return_pointers_to_small_and_big_part(int* src_first, int* src_second, int arr_size);
	void batcher_sort_func_6_processors();
    int stream_count;
public:
	batcher_sort();
    void sort_6_processors();
    void sort_16_processors();
    void show_array_batcher();
};

template <class T>
class NewBatcher
{
    T *buffer;
public:
    NewBatcher();
    NewBatcher(T &buf);
};

#endif //BATCHER_SORT_H