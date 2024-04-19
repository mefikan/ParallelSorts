#include "batcher_sort.h"

batcher_sort::batcher_sort()
{
	base_buf = new int[num_count];
	//random_numbers_at_file();
	//file_read(base_buf);
    array_generator(base_buf, num_count);
	batcher_sort_func();
	show_array(base_buf, num_count);
}
std::pair <int*, int*> batcher_sort::merge_arrays_and_return_pointers_to_small_and_big_part(int* src_first, int* src_second, int arr_size)
{
	int* buffer_small_big = new int[arr_size * 2];
	int ind_first = 0;
	int ind_second = 0;
	int ind_buf = 0;
	for (int i = 0; ind_first < arr_size && ind_second < arr_size; i++)
	{
		if (src_first[ind_first] < src_second[ind_second])
		{
			buffer_small_big[ind_buf++] = src_first[ind_first++];
		}
		else
		{
			buffer_small_big[ind_buf++] = src_second[ind_second++];
		}
	}
	while (ind_first < arr_size)
	{
		buffer_small_big[ind_buf++] = src_first[ind_first++];
	}
	while (ind_second < arr_size)
	{
		buffer_small_big[ind_buf++] = src_second[ind_second++];
	}
	int* pbuffer_small = new int[arr_size];
	int* pbuffer_big = new int[arr_size];
	for (int i = 0; i < arr_size; i++)
	{
		pbuffer_small[i] = buffer_small_big[i];
		pbuffer_big[i] = buffer_small_big[i + arr_size];
	}
	return std::make_pair(pbuffer_small, pbuffer_big);
}
void batcher_sort::batcher_sort_func()
{
	int count_per_array = ceil(num_count / 6.0);
	int count_last_array = num_count - count_per_array * 5;
	int** array_matrix = new int* [stream_count];
	int base_buf_ind = 0;
	for (int i = 0; i < stream_count; i++)
	{
		if (i == 5)
		{
			array_matrix[i] = new int[count_per_array];
			int start_ind = 0;
			for (int j = 0; (count_per_array != count_last_array) && (j < count_per_array - count_last_array); j++)
			{
				array_matrix[i][j] = 0;
				start_ind++;
			}
			for (int j = start_ind; j < count_per_array; j++)
			{
				array_matrix[i][j] = base_buf[base_buf_ind++];
			}
		}
		else
		{
			array_matrix[i] = new int[count_per_array];
			for (int j = 0; j < count_per_array; j++)
			{
				array_matrix[i][j] = base_buf[base_buf_ind++];
			}
		}
	}

	//showMatrix(arrayMatrix, streamCount, count_per_array);

	timer* t = new timer();
	std::thread* th1 = new std::thread(heap_sort, array_matrix[0], count_per_array);
	std::thread* th2 = new std::thread(heap_sort, array_matrix[1], count_per_array);
	std::thread* th3 = new std::thread(heap_sort, array_matrix[2], count_per_array);
	std::thread* th4 = new std::thread(heap_sort, array_matrix[3], count_per_array);
	std::thread* th5 = new std::thread(heap_sort, array_matrix[4], count_per_array);
	std::thread* th6 = new std::thread(heap_sort, array_matrix[5], count_per_array);

	th1->join();
	th2->join();
	th3->join();
	th4->join();
	th5->join();
	th6->join();

	//получение отсортированных подмассивов вычислением на 6 потоках, а далее слияние:

	//showMatrix(arrayMatrix, streamCount, count_per_array);

	// Тут сделана обработка данных сетью за 5 шагов, это как гонки в быках и коровах, чем меньше шагов, тем лучше
	// step 1 
	th1 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 0;
		int ind_second = 1;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th2 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 2;
		int ind_second = 3;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th3 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 4;
		int ind_second = 5;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th1->join();
	th2->join();
	th3->join();

	// step 2
	th1 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 0;
		int ind_second = 2;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th2 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 3;
		int ind_second = 5;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th3 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 1;
		int ind_second = 4;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th1->join();
	th2->join();
	th3->join();

	//step 3 
	th1 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 0;
		int ind_second = 1;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th2 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 2;
		int ind_second = 3;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th3 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 4;
		int ind_second = 5;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th1->join();
	th2->join();
	th3->join();

	// step 4
	th1 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 1;
		int ind_second = 2;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th2 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 3;
		int ind_second = 4;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th1->join();
	th2->join();

	// step 5
	th1 = new std::thread([&array_matrix](int count_per_array) {
		std::pair <int*, int*> buff_pair;
		int ind_first = 2;
		int ind_second = 3;
		buff_pair = merge_arrays_and_return_pointers_to_small_and_big_part(array_matrix[ind_first], array_matrix[ind_second], count_per_array);
		array_matrix[ind_first] = buff_pair.first;
		array_matrix[ind_second] = buff_pair.second;
		}, count_per_array);
	th1->join();
	delete t;
	//showMatrix(arrayMatrix, streamCount, count_per_array);
	int ind = 0;
	for (int i = 0; i < stream_count; i++)
	{
		for (int j = 0; j < count_per_array; j++)
		{
			base_buf[ind++] = array_matrix[i][j];
		}
	}
	if (is_array_sorted(base_buf, num_count))
	{
		std::cout << "SORT OK!\n";
	}
	else
	{
		std::cout << "NOT SORTED!\n";
	}
	//showArray(baseBuf, numCount);

}
