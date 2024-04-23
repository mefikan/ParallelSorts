#include "generator.h"

template <class T> void array_generator_(T *arr, int n)
{
    srand(time(NULL));
    for (auto c : arr)
    {
        //c = rand() % 99 + 1;
    }
}

void array_generator(int* arr, int n)
{
    srand(time(NULL));
    for (int i = 0; i < NUM_COUNT; i++)
    {
        arr[i] = rand() % 99 + 1;
    }
}
void random_numbers_at_file()
{
    std::ofstream out(FILE_NAME);
    srand(time(NULL));
    if (!out.is_open())
    {
        std::cout << "Error with opening file!";
        return;
    }
    for (size_t i = 0; i < NUM_COUNT; i++)
    {
        out << (rand() % 100 + 1) << " ";
    }
    out.close();
    std::cout << "File filled with numbers\n";
}
void file_write(int* arr)
{
    std::ofstream out(FILE_NAME);
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
void file_read(int* arr)
{
    std::ifstream in(FILE_NAME);
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