#include "generator.h"

void array_generator(int* arr, int n)
{
    srand(time(NULL));
    for (int i = 0; i < NUM_COUNT; i++)
    {
        arr[i] = rand() % MAX_NUM + 1;
    }
}
void random_numbers_at_file(std::string file_name)
{
    std::ofstream out(file_name);
    srand(time(NULL));
    if (!out.is_open())
    {
        std::cout << "Error with opening file!";
        return;
    }
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, MAX_NUM);
    for (int i = 0;i < NUM_COUNT; i++)
    {
         out << (dist(mt)) << " ";
    }
    out.close();
    std::cout << "File filled with numbers\n";
}
void file_write(int* arr, std::string file_name)
{
    std::ofstream out(file_name);
    if (!out.is_open())
    {
        std::cout << "Error with opening file!";
        return;
    }
    for (int i = 0; i < NUM_COUNT; i++)
    {
        out << *(arr + i) << " ";
    }
    out.close();
}
void file_read(int* arr, std::string file_name)
{
    std::ifstream in(file_name);
    if (!in.is_open())
    {
        std::cout << "Error with opening file!";
        return;
    }
    for (size_t i = 0; i < NUM_COUNT; i++)
    {
        in >> arr[i];
    }
    in.close();
    std::cout << "File is readed succesfully\n";
}