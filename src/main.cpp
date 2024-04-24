#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include "new_batcher.h"
#include "batcher_sort.h"
#include "timer_common.h"

int main()
{
    //new_batcher b;
    //b.sort_6_processors();

    batcher_sort b;
    b.sort_6_processors();
    //b.show_array_batcher();

    int *array = new int[NUM_COUNT];
    array_generator(array, NUM_COUNT);
    timer_common *t = new timer_common;
    //shell_sort(array, NUM_COUNT);
    std::sort(&array[0], &array[NUM_COUNT-1]);
    delete t;
    //show_array(array, NUM_COUNT);

	return 0;
}
