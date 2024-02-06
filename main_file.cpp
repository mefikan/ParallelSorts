#include "includes.h"
#include "thread_pool.h"
#include "file_processing_functions.h"
#include "consts.h"
#include "batcher_sort.h"

int main()
{
	batcher_sort();

	thread_pool tp1(6);
	
	return 0;
}
