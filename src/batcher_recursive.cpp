#include "batcher_recursive.h"
#include <mutex>

using namespace std;

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
        bitonicMerge(arr,low,k,dir);
        bitonicMerge(arr,low+k,k,dir);
    }
}

void bitonicSort(int *arr, int low, int count, bool dir) {
    if (count > 1) {
        int k = count / 2;

        // Создаем потоки для параллельной сортировки
        thread firstHalf(bitonicSort, ref(arr), low, k, true);
        thread secondHalf(bitonicSort, ref(arr), low + k, k, false);

        firstHalf.join();
        secondHalf.join();
    }
    bitonicMerge(arr, low, count, dir);
}

QString batcher_recursive_init(int size) {
    QString result= "";

    int *arr = new int[size];
    file_read(arr,"in.txt", size);
    int now_size = size;
    result += "Array size is " + QString::number(size) + "\n";

    // Проверяем, что размер массива является кратным 2
    int *buf;
    int count_added_zeroes = 0;
    if ((size & (size - 1)) != 0) {
        int start_num = 1;
        int next_num = start_num*2;
        while (!(size>start_num && size<next_num)){
            start_num*=2;
            next_num*=2;
        }
        count_added_zeroes = next_num-size;
        result += "Array size is not a power of 2\n"
                  "New array size "  + QString::number(next_num) + "\n"
                  "Zeroes added " + QString::number(count_added_zeroes) + "\n";

        buf = new int[next_num];
        for (int i=0;i<count_added_zeroes;i++)
        {
            buf[i] = 0;
        }
        for (int i=0; i<size;i++)
        {
            buf[count_added_zeroes+i] = arr[i];
        }
        delete []arr;
        arr = buf;
        now_size = next_num;
    }
    //Запуск основного алгоритма сортировки и таймера
    timer_common *timer = new timer_common;
    bitonicSort(arr, 0, now_size, true);
    result += QString::number(timer->timer_stop()*1e-9) + "sec\n";
    delete timer;

    //Проверка массива, отсортирован ли он
    if (is_array_sorted(arr, now_size))
    {
        result += "CHECK: Array is sorted";
    }
    else
    {
        result += "CHECK: Array is NOT sorted";
    }
    file_write(&arr[count_added_zeroes], "out.txt", size);
    return result;
}
