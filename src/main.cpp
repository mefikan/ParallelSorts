#include <iostream>
#include <vector>
#include "batcher_sort.h"

int main()
{
    batcher_sort sort;
    sort.show_array_batcher();
    sort.sort_6_processors();
    sort.show_array_batcher();

	return 0;
}
