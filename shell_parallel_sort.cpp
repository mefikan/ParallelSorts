#include "shell_parallel_sort.h"


shell_parallel_sort::shell_parallel_sort()
{
	/*random_numbers_at_file();
	file_read(base_buf);*/
	base_buf = new int[num_count];
	array_generator(base_buf);
	parallel_shell_sort();
}
void shell_parallel_sort::parallel_shell_sort()
{
	thread_pool tp(8);
	//show_array(base_buf, num_count);
	timer* t = new timer();
	for (int step = num_count / 2; step > 0; step /= 2)
	{
		for (int j = 0; j < step; j++)
		{
			tp.add_task(one_time_passes, base_buf, num_count, step, j);
		}
		tp.wait_all();
	}
	delete t;
	if (is_array_sorted(base_buf, num_count))
	{
		std::cout << "SORT OK!\n";
	}
	else
	{
		std::cout << "NOT SORTED!\n";
	}
	//show_array(base_buf, num_count);

}
void shell_parallel_sort::one_time_passes(int* arr, int n, int step, int shift)
{
	for (int i = shift; i < n; i += step)
	{
		
		for (int j = i; j - step >= 0 && arr[j] < arr[j - step]; j-=step)
		{
			std::swap(arr[j], arr[j - step]);
		}
	}
}