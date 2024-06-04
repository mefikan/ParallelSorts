#ifndef PARALLELSORTS_GENERATOR_H
#define PARALLELSORTS_GENERATOR_H


#include <fstream>
#include <iostream>
#include <random>

#include "consts.h"

void array_generator(int* arr, int n);
void random_numbers_at_file(std::string file_name, int size, unsigned int max_num);
void file_write(int* arr, std::string file_name, int size = NUM_COUNT);
void file_read(int* arr, std::string file_name, int size = NUM_COUNT);

void array_generator(std::vector<int> &arr, int n);
void file_write(std::vector<int> &arr, std::string file_name, int size = NUM_COUNT);
void file_read(std::vector<int> &arr, std::string file_name, int size = NUM_COUNT);

#endif //PARALLELSORTS_GENERATOR_H
