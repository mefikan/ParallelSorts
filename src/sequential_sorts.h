#ifndef PARALLELSORTS_SEQUENTIAL_SORTS_H
#define PARALLELSORTS_SEQUENTIAL_SORTS_H

#include <algorithm> //swap

void build_max_heap(int arr[], int n);
void shell_sort(int a[], int n);
int* heap_sort_asc(int* arr, int n);
void build_min_heap(int arr[], int n);
int* heap_sort_desc(int* arr, int n);

#endif //PARALLELSORTS_SEQUENTIAL_SORTS_H
