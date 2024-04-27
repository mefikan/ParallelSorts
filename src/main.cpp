#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include "new_batcher.h"
#include "batcher_sort.h"
#include "timer_common.h"
#include "final_batcher.h"

int main()
{
    batcher_sort bs;
    bs.sort_16_processors();
    final_batcher b;
    b.sort_16();

	return 0;
}
