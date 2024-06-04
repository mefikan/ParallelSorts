#include "sequential_sorts.h"

void build_max_heap(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > arr[(i - 1) / 2])
        {
            int j = i;
            while (arr[j] > arr[(j - 1) / 2])
            {
                std::swap(arr[j], arr[(j - 1) / 2]);
                j = (j - 1) / 2;
            }
        }
    }
}
void heap_sort_asc(int* arr, int n)
{
    if (n<=1)
        return;
    build_max_heap(arr, n);

    for (int i = n - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        int j = 0, index;
        do
        {
            index = (2 * j + 1);

            if (index < (i - 1) && arr[index] < arr[index + 1])
                index++;

            if (index < i && arr[j] < arr[index])
                std::swap(arr[j], arr[index]);

            j = index;

        } while (index < i);
    }
    return;
}

void shell_sort(int a[], int n)
{
    int step, temp;
    for (step = n / 2; step > 0; step /= 2)
    {
        for (int i = step; i < n; i++)
        {
            temp = a[i];
            int j;
            for (j = i; j >= step && a[j - step] > temp; j -= step)
            {
                a[j] = a[j - step];
            }
            a[j] = temp;

        }
    }
}
void build_min_heap(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[(i - 1) / 2])
        {
            int j = i;
            while (arr[j] < arr[(j - 1) / 2])
            {
                std::swap(arr[j], arr[(j - 1) / 2]);
                j = (j - 1) / 2;
            }
        }
    }
}

void heap_sort_desc(int* arr, int n)
{
    if (n<=1)
        return;
    build_min_heap(arr, n);

    for (int i = n - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        int j = 0, index;
        do
        {
            index = (2 * j + 1);

            if (index < (i - 1) && arr[index] > arr[index + 1])
                index++;

            if (index < i && arr[j] > arr[index])
                std::swap(arr[j], arr[index]);

            j = index;

        } while (index < i);
    }
    return;
}

void heap_sort_asc_(std::vector<int> &arr, int n)
{
    if (n<=1)
        return;
    build_max_heap_(arr, n);

    for (int i = n - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        int j = 0, index;
        do
        {
            index = (2 * j + 1);

            if (index < (i - 1) && arr[index] < arr[index + 1])
                index++;

            if (index < i && arr[j] < arr[index])
                std::swap(arr[j], arr[index]);

            j = index;

        } while (index < i);
    }
    return;
}
void build_max_heap_(std::vector<int> &arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > arr[(i - 1) / 2])
        {
            int j = i;
            while (arr[j] > arr[(j - 1) / 2])
            {
                std::swap(arr[j], arr[(j - 1) / 2]);
                j = (j - 1) / 2;
            }
        }
    }
}
