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
	void batcher_sort_func();
public:
	batcher_sort();
};

#endif //BATCHER_SORT_H