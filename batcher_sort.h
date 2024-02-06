#pragma once
#include "includes.h"
#include "consts.h"
#include "sequential_sorts.h"
#include "timer.h"
#include "file_processing_functions.h"
#include "printing_elements_stdout_stream.h"

void batcher_sort();
bool is_array_sorted(int* array, int n);
std::pair <int*, int*> merge_arrays_and_return_pointers_to_small_and_big_part(int* srcFirst, int* srcSecond, int arrSize);

