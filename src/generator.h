#ifndef PARALLELSORTS_GENERATOR_H
#define PARALLELSORTS_GENERATOR_H

#include <fstream>
#include <iostream>

#include "consts.h"

void array_generator(int* arr, int n);
void random_numbers_at_file();
void file_write(int* arr);
void file_read(int* arr);

#endif //PARALLELSORTS_GENERATOR_H