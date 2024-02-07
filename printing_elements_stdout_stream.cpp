#include "printing_elements_stdout_stream.h"

bool is_array_sorted(int* array, int n)
{
	int prev = array[0];
	for (int i = 1; i < n; i++)
	{
		if (array[i] < prev)
			return 0;
		prev = array[i];
	}
	return 1;
}
void show_matrix(int** matrix, int row, int column)
{
	std::cout << '\n';
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			std::cout << std::setw(2) << matrix[i][j] << " ";
		}
		std::cout << '\n';
	}
}
void show_array(int* arr, int n)
{
	for (size_t i = 0; i < n; i++)
	{
		std::cout << std::setw(2) << arr[i] << " ";
	}
	std::cout << '\n';
}