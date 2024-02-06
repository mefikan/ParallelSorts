#include "file_processing_functions.h"

void random_numbers_at_file()
{
	std::ofstream out(file_name);
	srand(time(NULL));
	if (!out.is_open())
	{
		std::cout << "Error with opening file!";
		return;
	}
	for (size_t i = 0; i < num_count; i++)
	{
		out << (rand() % 100 + 1) << " ";
	}
	out.close();
}
void file_write(int* arr)
{
	std::ofstream out(file_name);
	if (!out.is_open())
	{
		std::cout << "Error with opening file!";
		return;
	}
	for (int i = 0; i < num_count; i++)
	{
		out << *(arr + i) << " ";
	}
	out.close();
}
void file_read(int* arr)
{
	std::ifstream in(file_name);
	if (!in.is_open())
	{
		std::cout << "Error with opening file!";
		return;
	}
	for (size_t i = 0; i < num_count; i++)
	{
		in >> arr[i];
	}
	in.close();
}