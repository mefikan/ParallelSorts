#include "block_sort.h"

QString block_sort::sort_16() {
    QString result = "";

    file_read(arr, "in.txt", arr_size);
    stream_count = 16;
    auto timer = new timer_common;

    // Добавление недостающих нулей
    count_per_piece = ceil(arr_size/16.0);
    int count_added_zeroes = (arr_size - count_per_piece*16);
    if (count_added_zeroes<0)
    {
        count_added_zeroes = -count_added_zeroes;
    }
    int *buf = new int[arr_size + count_added_zeroes];
    for (int i=0;i<arr_size;i++)
    {
        buf[i] = arr[i];
    }
    for (int i=0;i<count_added_zeroes;i++)
    {
        buf[arr_size+i] = 0;
    }
    delete []arr;
    arr = buf;
    arr_size += count_added_zeroes;
    result += "Array size is " + QString::number(arr_size-count_added_zeroes) + "\n";
    result += "Now array size is " + QString::number(arr_size) + "\n"
              + "Count per block is " + QString::number(count_per_piece) + "\n";

    // Основной алгоритм сортировки
    std::vector<std::thread> vec(stream_count);
    for (int i=0;i<stream_count;i++)
    {
        vec[i] = std::thread(heap_sort_asc, &arr[i * count_per_piece], count_per_piece);
    }
    for (int i=0;i<stream_count;i++)
    {
        vec[i].join();
    }
    vec.resize(stream_count/2); //удаление лишних потоков

    // Представление сортировочной сети в виде матрицы пар элементов
    std::vector <std::vector <std::pair<int, int>>> indexes =
            {
                    {{0,1}, {3,2}, {4,5}, {7,6}, {8,9}, {11,10}, {12,13}, {15,14}},  //1
                    {{0,2}, {1,3}, {6,4}, {7,5}, {8,10}, {9,11}, {14,12}, {15,13}},    //2
                    {{0,1}, {2,3}, {5,4}, {7,6}, {8,9}, {10,11}, {13,12}, {15,14}},    //3
                    {{0,4}, {1,5}, {2,6}, {3,7}, {12,8}, {13,9}, {14,10}, {15,11}},    //4
                    {{0,2}, {1,3}, {4,6}, {5,7}, {10,8}, {11,9}, {14,12}, {15,13}},    //5
                    {{0,1}, {2,3}, {4,5}, {6,7}, {9,8}, {11,10}, {13,12}, {15,14}},    //6
                    {{0,8}, {1,9}, {2,10}, {3,11}, {4,12}, {5,13}, {6,14}, {7,15}},    //7
                    {{0,4}, {1,5}, {2,6}, {3,7}, {8,12}, {9,13}, {10,14}, {11,15}},    //8
                    {{0,2}, {1,3}, {4,6}, {5,7}, {8,10}, {9,11}, {12,14}, {13,15}},    //9
                    {{0,1}, {2,3}, {4,5}, {6,7}, {8,9}, {10,11}, {12,13}, {14,15}}     //10
            };

    // Слияние через сеть используя потоки и стандартное слияние
    for (int g=0;g<10;g++) {
        for (int i = 0; i < stream_count/2; i++) {
            int first_pair_val = indexes[g][i].first;
            int second_pair_val = indexes[g][i].second;
            vec[i] = std::thread([this](int first_pair_val, int second_pair_val)
                                 {this->merge_2_arrays(
                                        first_pair_val*this->count_per_piece,
                                        second_pair_val*this->count_per_piece);
                                 },
                                 first_pair_val, second_pair_val);
        }
        for (int j=0;j<stream_count/2;j++) {
            vec[j].join();
        }
    }
    result += QString::number(timer->timer_stop()*1e-9) + " sec\n";
    delete timer;

    // Проверка получившегося массива
    if (is_array_sorted(arr,arr_size))
    {
        result+= "CHECK: Array is sorted";
    }
    else
    {
        result+= "CHECK: Array is NOT sorted";
    }
    file_write(&arr[count_added_zeroes], "out.txt", arr_size-count_added_zeroes);
    delete []arr;

    return result;
}
void block_sort::num_generate() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100000);
    for (int i = 0;i < arr_size; i++)
    {
        arr[i] = (dist(mt));
    }
    //std::cout << "Numbers generated!\n";
}
void block_sort::merge_2_arrays(const unsigned int &start1, const unsigned int &start2) {
    std::vector <int> buffer(count_per_piece*2);
    int ind1, ind2, i = 0;
    for ( ind1 = start1, ind2 = start2 ;ind1 < count_per_piece + start1
                                       && ind2 < count_per_piece + start2; )
    {
        if (arr[ind1] < arr[ind2])
        {
            buffer[i++] = arr[ind1++];
        }
        else
        {
            buffer[i++] = arr[ind2++];
        }
    }
    while (ind1 < count_per_piece + start1)
    {
        buffer[i++] = arr[ind1++];
    }
    while (ind2 < count_per_piece + start2)
    {
        buffer[i++] = arr[ind2++];
    }
    for (int j = 0; j < count_per_piece; j++)
    {
        arr[j+start1] = buffer[j];
        arr[j+start2] = buffer[j+count_per_piece];
    }
}
void block_sort::print_array() {
    for (int i=0;i<arr_size;i++)
    {
        //std::cout << (i!=0 && i%count_per_piece==0 ?  "\n" :  "");
        std::cout << std::setw(3) << arr[i] << " ";
    }
    std::cout << "\n\n";
}
