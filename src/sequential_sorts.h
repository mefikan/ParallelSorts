#ifndef PARALLELSORTS_SEQUENTIAL_SORTS_H
#define PARALLELSORTS_SEQUENTIAL_SORTS_H


#include <algorithm> //swap
#include <vector>

void build_max_heap(int arr[], int n);
void build_max_heap_(std::vector<int> &arr, int n);
void shell_sort(int a[], int n);
void heap_sort_asc(int* arr, int n);
void heap_sort_asc_(std::vector<int> &arr, int n);
void build_min_heap(int arr[], int n);
void heap_sort_desc(int* arr, int n);

#endif //PARALLELSORTS_SEQUENTIAL_SORTS_H
