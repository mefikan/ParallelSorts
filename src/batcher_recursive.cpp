#include "batcher_recursive.h"

using namespace std;

// Функция для слияния двух подмассивов
void bitonicMerge(int *arr, int low, int count, bool dir) {
    if (count > 1) {
        int k = count / 2;
        for (int i = low; i < low + k; ++i) {
            if ((arr[i] > arr[i + k]) == dir) {
                // Если dir == true, то сравниваем в порядке возрастания,
                // иначе в порядке убывания
                swap(arr[i], arr[i + k]);
            }
        }
        bitonicMerge(arr, low, k, dir);
        bitonicMerge(arr, low + k, k, dir);
    }
}

// Функция для сортировки битонной последовательности
void bitonicSort(int *arr, int low, int count, bool dir) {
    if (count > 1) {
        if (count <= 1024) {
            // Если количество элементов небольшое, просто сортируем их
            sort(&arr[0] + low, &arr[0] + low + count);
            return;
        }

        int k = count / 2;

        // Создаем потоки для параллельной сортировки
        thread firstHalf(bitonicSort, ref(arr), low, k, true);
        thread secondHalf(bitonicSort, ref(arr), low + k, k, false);

        firstHalf.join();
        secondHalf.join();

        bitonicMerge(arr, low, count, dir);
    }
}

// Функция для вызова сортировки
void sort(int *arr) {
    int n = NUM_COUNT;
    bitonicSort(arr, 0, n, true);
}

int batcher_recursive_init() {
    int *arr = new int[NUM_COUNT];
    for (int i = 0; i < NUM_COUNT; ++i) {
        arr[i] = rand() % 100 + 1;
    }

    // Проверяем, что размер массива является кратным 2
    if ((NUM_COUNT & (NUM_COUNT - 1)) != 0) {
        cout << "Размер массива не является кратным 2." << endl;
        return 1;
    }

    timer_common *timer_ = new timer_common;
    sort(arr);
    delete timer_;

    if (is_array_sorted(arr, NUM_COUNT))
    {
        std::cout << "Sorted!\n";
    }
    else
    {
        std::cout << "Not sorted!\n";
    }

    return 0;
}
