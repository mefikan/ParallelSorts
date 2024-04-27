#ifndef PARALLELSORTS_SEQUENTIAL_SORTS_H
#define PARALLELSORTS_SEQUENTIAL_SORTS_H

#include <algorithm> //for swap
#include <vector>
#include "element.h"
#include "new_batcher.h"

void build_max_heap(int arr[], int n);
void shell_sort(int a[], int n);
int* heap_sort(int* arr, int n);
void heap_sort_(std::vector <Element> &arr_, int start, int n);
void build_max_heap_(std::vector <Element> &arr, int n);

#endif //PARALLELSORTS_SEQUENTIAL_SORTS_H
