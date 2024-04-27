#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include "timer_common.h"
#include "batcher_default_merge.h"
#include "batcher_true_merge.h"

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
    //batcher_default_merge b;
    //b.sort_16();
    //check_std_sort_time();

    batcher_true_merge btm;
    btm.sort_16();
    //btm.print_array();

    check_std_sort_time();

    //int a[] = {3,6,11,33,22,91,1,44,2, 0};
    //heap_sort_desc(a,10);
    //for (auto c : a)
    //{
    //    std::cout << c << " ";
    //}


    return 0;
}
