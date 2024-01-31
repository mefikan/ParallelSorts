// Parallel_sorts.cpp: определяет точку входа для приложения.
//

#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>

const std::string fileName = "file.txt";
const int numCount = 10'000'000;
const int streamCount = 6;
//попытка батчер сортировки

//sekelton of most sorts
class timer
{
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::high_resolution_clock clock;
public:
	timer()
	{
		start = clock.now();
	}
	~timer()
	{
		end = clock.now();
		double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		std::cout << "-----TIME-----\n" << std::setprecision(15) << time * 1e-9 << " s\n" << time << " ns\n";
	}
};

void fileNumGenerator();
void fileRead(int* arr);
void arrayShow(int* arr);
void buildMaxHeap(int arr[], int n);
void fileWrite(int* arr);
int* heapSort(int* arr, int n);
template <class T> void shellSort(T a[], int n);
void batcherSort();
void showMatrix(int** matrix, int row, int column);
std::pair <int*, int*> mergeArraysAndReturnPointersToSmallAndBigPart(int* srcFirst, int* srcSecond, int arrSize);

int main()
{
	//batcherSort();
	fileNumGenerator();
	int* baseBuf = new int[numCount];
	fileRead(baseBuf);
	timer* t = new timer();
	heapSort(baseBuf, numCount);
	delete t;
	return 0;
}

void batcherSort()
{
	fileNumGenerator();
	int* baseBuf = new int[numCount];
	fileRead(baseBuf);
	int countPerArray = std::ceil(numCount / 6.0);
	int countLastArray = numCount - countPerArray * 5;
	int** arrayMatrix = new int* [streamCount];
	int baseBufInd = 0;
	for (int i = 0; i < streamCount; i++)
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
	std::thread* th1 = new std::thread(heapSort, arrayMatrix[0], countPerArray);
	std::thread* th2 = new std::thread(heapSort, arrayMatrix[1], countPerArray);
	std::thread* th3 = new std::thread(heapSort, arrayMatrix[2], countPerArray);
	std::thread* th4 = new std::thread(heapSort, arrayMatrix[3], countPerArray);
	std::thread* th5 = new std::thread(heapSort, arrayMatrix[4], countPerArray);
	std::thread* th6 = new std::thread(heapSort, arrayMatrix[5], countPerArray);

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
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th2 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 2;
		int indSecond = 3;
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th3 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 4;
		int indSecond = 5;
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
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
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th2 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 3;
		int indSecond = 5;
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th3 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 1;
		int indSecond = 4;
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
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
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th2 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 2;
		int indSecond = 3;
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th3 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 4;
		int indSecond = 5;
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
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
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th2 = new std::thread([&arrayMatrix](int countPerArray) {
		std::pair <int*, int*> buffpair;
		int indFirst = 3;
		int indSecond = 4;
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
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
		buffpair = mergeArraysAndReturnPointersToSmallAndBigPart(arrayMatrix[indFirst], arrayMatrix[indSecond], countPerArray);
		arrayMatrix[indFirst] = buffpair.first;
		arrayMatrix[indSecond] = buffpair.second;
		}, countPerArray);
	th1->join();
	delete t;
	//showMatrix(arrayMatrix, streamCount, countPerArray);

}
void showMatrix(int** matrix, int row, int column)
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
std::pair <int*, int*> mergeArraysAndReturnPointersToSmallAndBigPart(int* srcFirst, int* srcSecond, int arrSize)
{
	int* bufferSmallBig = new int[arrSize *2];
	int indFirst = 0;
	int indSecond = 0;
	int indBuf = 0;
	for (int i = 0; indFirst< arrSize && indSecond< arrSize; i++)
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
void fileNumGenerator()
{
	std::ofstream out(fileName);
	srand(time(NULL));
	if (!out.is_open())
	{
		std::cout << "Error with opening file!";
		return;
	}
	for (size_t i = 0; i < numCount; i++)
	{
		out << (rand() % 98 + 1) << " ";
	}
	out.close();
}
void fileRead(int* arr)
{
	std::ifstream in(fileName);
	if (!in.is_open())
	{
		std::cout << "Error with opening file!";
		return;
	}
	for (size_t i = 0; i < numCount; i++)
	{
		in >> arr[i];
	}
	in.close();
}
void arrayShow(int* arr)
{
	for (size_t i = 0; i < numCount; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << '\n';
}
void buildMaxHeap(int arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		if (arr[i] > arr[(i - 1) / 2])
		{
			int j = i;
			while (arr[j] > arr[(j - 1) / 2])
			{
				std::swap(arr[j], arr[(j - 1) / 2]);
				j = (j - 1) / 2;
			}
		}
	}
}
template <class T>
void shellSort(T a[], int n)
{
	int step, temp;
	for (step = n / 2; step > 0; step /= 2)
	{
		for (int i = step; i < n; i++)
		{
			temp = a[i];
			int j;
			for (j = i; j >= step && a[j - step] > temp; j -= step)
			{
				a[j] = a[j - step];
			}
			a[j] = temp;

		}
	}
}
int* heapSort(int* arr, int n)
{
	buildMaxHeap(arr, n);

	for (int i = n - 1; i > 0; i--)
	{
		std::swap(arr[0], arr[i]);
		int j = 0, index;
		do
		{
			index = (2 * j + 1);

			if (index < (i - 1) && arr[index] < arr[index + 1])
				index++;

			if (index < i && arr[j] < arr[index])
				std::swap(arr[j], arr[index]);

			j = index;

		} while (index < i);
	}
	return arr;
}
void fileWrite(int* arr)
{
	std::ofstream out(fileName);
	if (!out.is_open())
	{
		std::cout << "Error with opening file!";
		return;
	}
	for (int i = 0; i < numCount; i++)
	{
		out << *(arr + i) << " ";
	}
	out.close();
}