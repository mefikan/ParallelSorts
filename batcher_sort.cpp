#include "batcher_sort.h"

std::pair <int*, int*> merge_arrays_and_return_pointers_to_small_and_big_part(int* srcFirst, int* srcSecond, int arrSize)
{
	int* bufferSmallBig = new int[arrSize * 2];
	int indFirst = 0;
	int indSecond = 0;
	int indBuf = 0;
	for (int i = 0; indFirst < arrSize && indSecond < arrSize; i++)
	{
		if (srcFirst[indFirst] < srcSecond[indSecond])
		{
			bufferSmallBig[indBuf++] = srcFirst[indFirst++];
		}
		else
		{
			bufferSmallBig[indBuf++] = srcSecond[indSecond++];
		}
	}
	while (indFirst < arrSize)
	{
		bufferSmallBig[indBuf++] = srcFirst[indFirst++];
	}
	while (indSecond < arrSize)
	{
		bufferSmallBig[indBuf++] = srcSecond[indSecond++];
	}
	int* pbufferSmall = new int[arrSize];
	int* pbufferBig = new int[arrSize];
	for (int i = 0; i < arrSize; i++)
	{
		pbufferSmall[i] = bufferSmallBig[i];
		pbufferBig[i] = bufferSmallBig[i + arrSize];
	}
	return std::make_pair(pbufferSmall, pbufferBig);
}
void batcher_sort()
{
	random_numbers_at_file();
	int* baseBuf = new int[num_count];
	file_read(baseBuf);
	int countPerArray = std::ceil(num_count / 6.0);
	int countLastArray = num_count - countPerArray * 5;
	int** arrayMatrix = new int* [stream_count];
	int baseBufInd = 0;
	for (int i = 0; i < stream_count; i++)
	{
		if (i == 5)
		{
			arrayMatrix[i] = new int[countPerArray];
			int startInd = 0;
			for (int j = 0; (countPerArray != countLastArray) && (j < countPerArray - countLastArray); j++)
			{
				arrayMatrix[i][j] = 0;
				startInd++;
			}
			for (int j = startInd; j < countPerArray; j++)
			{
				arrayMatrix[i][j] = baseBuf[baseBufInd++];
			}
		}
		else
		{
			arrayMatrix[i] = new int[countPerArray];
			for (int j = 0; j < countPerArray; j++)
			{
				arrayMatrix[i][j] = baseBuf[baseBufInd++];
			}
		}
	}

	//showMatrix(arrayMatrix, streamCount, countPerArray);

	timer* t = new timer();
	std::thread* th1 = new std::thread(heap_sort, arrayMatrix[0], countPerArray);
	std::thread* th2 = new std::thread(heap_sort, arrayMatrix[1], countPerArray);
	std::thread* th3 = new std::thread(heap_sort, arrayMatrix[2], countPerArray);
	std::thread* th4 = new std::thread(heap_sort, arrayMatrix[3], countPerArray);
	std::thread* th5 = new std::thread(heap_sort, arrayMatrix[4], countPerArray);
	std::thread* th6 = new std::thread(heap_sort, arrayMatrix[5], countPerArray);

	th1->join();
	th2->join();
	th3->join();
	th4->join();
	th5->join();
	th6->join();

	//получение отсортированных подмассивов вычислением на 6 потоках, а далее слияние:

	//showMatrix(arrayMatrix, streamCount, countPerArray);

	// Тут сделана обработка данных сетью за 5 шагов, это как гонки в быках и коровах, чем меньше шагов, тем лучше
	// step 1 
	th1 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 0;
		int indSecond = 1;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th2 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 2;
		int indSecond = 3;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th3 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 4;
		int indSecond = 5;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th1->join();
	th2->join();
	th3->join();

	// step 2
	th1 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 0;
		int indSecond = 2;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th2 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 3;
		int indSecond = 5;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th3 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 1;
		int indSecond = 4;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th1->join();
	th2->join();
	th3->join();

	//step 3 
	th1 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 0;
		int indSecond = 1;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th2 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 2;
		int indSecond = 3;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th3 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 4;
		int indSecond = 5;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th1->join();
	th2->join();
	th3->join();

	// step 4
	th1 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 1;
		int indSecond = 2;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th2 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 3;
		int indSecond = 4;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th1->join();
	th2->join();

	// step 5
	th1 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 2;
		int indSecond = 3;
		buffpair = merge_arrays_and_return_pointers_to_small_and_big_part(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th1->join();
	delete t;
	//showMatrix(arrayMatrix, streamCount, countPerArray);
	int ind = 0;
	for (int i = 0; i < stream_count; i++)
	{
		for (int j = 0; j < countPerArray; j++)
		{
			baseBuf[ind++] = arrayMatrix[i][j];
		}
	}
	if (is_array_sorted(baseBuf, num_count))
	{
		std::cout << "SORT OK!\n";
	}
	else
	{
		std::cout << "NOT SORTED!\n";
	}
	//showArray(baseBuf, numCount);

}
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