#pragma once
#include "includes.h"
#include "consts.h"
#include "sequential_sorts.h"
#include "timer.h"
#include "file_processing_functions.h"
#include "printing_elements_stdout_stream.h"

class batcher_sort
{
	int* base_buf;
	static std::pair <int*, int*> merge_arrays_and_return_pointers_to_small_and_big_part(int* src_first, int* src_second, int arr_size);
	void batcher_sort_func();
public:
	batcher_sort();
};

