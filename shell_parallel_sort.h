#pragma once
#include "includes.h"
#include "thread_pool.h"
#include "consts.h"
#include "file_processing_functions.h"
#include "timer.h"
#include "printing_elements_stdout_stream.h"

class shell_parallel_sort
{
	int* base_buf;
	void parallel_shell_sort();
	static void one_time_passes(int*arr, int n, int step, int shift);
public:
	shell_parallel_sort();
};