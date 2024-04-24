#include "check.h"

bool is_array_sorted(int* array, int n)
{
    int prev = array[0];
    for (int i = 1; i < n; i++)
    {
        if (array[i] < prev || array[i]<0)
            return 0;
        prev = array[i];
    }
    return 1;
}