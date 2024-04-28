#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include "timer_common.h"
#include "block_sort.h"
#include "batcher_true_bitonic_merge.h"
#include "batcher_recursive.h"
#include "SampleSort.h"

void check_std_sort_time()
{
    int *arr = new int[NUM_COUNT];
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100000);
    for (int i = 0;i < NUM_COUNT; i++)
    {
        arr[i] = (dist(mt));
    }

    timer_common *timer = new timer_common;

    std::sort(&arr[0], &arr[NUM_COUNT-1]);

    delete timer;
    delete [] arr;
}


int main()
{
    block_sort bs;
    bs.sort_16();

    SampleSort ss;
    ss.sort();

    check_std_sort_time();

    return 0;
}
