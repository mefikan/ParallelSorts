#ifndef PARALLELSORTS_GENERATOR_H
#define PARALLELSORTS_GENERATOR_H


#include <fstream>
#include <iostream>

#include "consts.h"

void array_generator(int* arr, int n);
void random_numbers_at_file(std::string file_name);
void file_write(int* arr, std::string file_name);
void file_read(int* arr, std::string file_name);

#endif //PARALLELSORTS_GENERATOR_H