#include "sample_sort.h"

std::array<std::mutex, 8> arr_mutex;

QString SampleSort::sort() {
    QString result= "Array size is " + QString::number(arr_size) + "\n";
    file_read(arr, "in.txt", arr_size);
    auto *timer = new timer_common;
    /*
     * если размер массива слишком маленький,
     * то используем обычную сортировку
    */
    if (arr_size<=p_count*10)
    {
        heap_sort_asc(arr, arr_size);
        file_write(arr, "out.txt",arr_size);
        result += QString::number(timer->timer_stop()*1e-9) + " sec\n";
        delete timer;
        result += "Массив отсортировки секвентально";
        return result;
    }
    // Выбор случайного места в массиве, откуда возьмем s
    srand(time(NULL));
    numbers_ind = std::rand()%(arr_size-p_count*10-1);
    /*
     * Заполнение массива s (buffer), а также
     * выбор массива ключей и его сортировка
    */
    int p_keys_size = p_count+1;
    p_keys = new int[p_keys_size];

    int *buffer = new int[p_keys_size*10];
    int start_s_index = rand()%(arr_size-p_keys_size*10-1);
    for (int i=0;i<p_keys_size*10;i++)
    {
        buffer[i] = arr[start_s_index+i];
    }
    for (int i=0, pi = 1;i<p_keys_size*10;i+=10, pi++)
    {
        p_keys[pi] = buffer[i];
    }
    p_keys[0] = INT32_MIN;
    p_keys[p_keys_size-1] = INT32_MAX;
    heap_sort_asc(p_keys, p_keys_size);

    // Добавление ключей блоков для их просмотра
    result+= "Bucket keys:\n";
    for (int i=0;i<p_keys_size;i++)
    {
        if (i==p_keys_size/2)
        {
            result+= QString::number(p_keys[i]) + "\n";
        }
        result+= QString::number(p_keys[i]) + " ";
    }
    /*
     * Распределение элементов происходит
     * параллельно с использованием массива
     * мьютексов
    */
    std::vector <std::thread> vec(p_count);
    int count_per_block = arr_size/p_count;
    for (int i=0;i<p_count;i++)
    {
        if (i != p_count-1)
        {
            vec[i] = std::thread([this](const int start, const int count){
                this->separate(start, count);}, i*count_per_block, count_per_block);
        }
        else
        {
            vec[i] = std::thread([this](const int start, const int count){
                this->separate(start, count);}, i*count_per_block, arr_size-i*count_per_block);
        }
    }
    {
        for (int i=0;i<p_count;i++)
        {
            vec[i].join();
        }
    }
    delete []arr;

    result += "\nBlocks sizes:\n";
    for (auto c : blocks)
    {
        result+= QString::number(c.size()) + " ";
    }
    // Сортировка каждого блока параллельно
    for (int i=0;i<p_count;i++)
    {
        vec[i] = std::thread(heap_sort_asc_,
                             std::ref(blocks[i]), blocks[i].size());
    }
    for (int i=0;i<p_count;i++)
    {
        vec[i].join();
    }
    // Соединение блоков в один массив
    arr = new int[arr_size];
    int ind_arr=0;
    for (int i=0; i<p_count;i++)
    {
        for (int j=0;j<blocks[i].size();j++)
        {
            arr[ind_arr++] = blocks[i][j];
        }
    }
    result += "\n" + QString::number(timer->timer_stop()*1e-9) + " sec\n";
    delete timer;

    // Проверка массива
    if (is_array_sorted(arr, arr_size))
    {
        result+= "CHECK: Array is sorted";
    }
    else
    {
        result+= "CHECK: Array is NOT sorted";
    }
    file_write(arr, "out.txt", arr_size);
    delete [] arr;
    return result;
}

void SampleSort::num_generate() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100000);
    for (int i = 0;i < arr_size; i++)
    {
        arr[i] = (dist(mt));
    }
}

void SampleSort::print_array() {
    for (int i=0;i<arr_size;i++)
    {
        std::cout << std::setw(3) << arr[i] << " ";
    }
    std::cout << "\n\n";
}

int SampleSort::binary_search(const int start, const int end, const int num) {
    int l = start;
    int r = end;

    while (l < r)
    {
        int m = l + (r-l)/2;

        if (p_keys[m] == num)
            return m;
        else if (num > p_keys[m] && (m+1 <= r) && num < p_keys[m+1])
        {
            return m+1;
        }
        else if (num < p_keys[m] && (m-1>=l) && num > p_keys[m-1])
        {
            return m;
        }
        else if (num < p_keys[m])
        {
            r = m;
        }
        else if (num > p_keys[m])
        {
            l = m;
        }
    }
    return 1;
}

void SampleSort::separate(const int start, const int count) {

    for (int i=0;i<count;i++)
    {
        int ind = binary_search(1, p_count, arr[start+i]);
        if (ind!=-1)
        {
            arr_mutex[ind-1].lock();
            blocks[ind-1].push_back(arr[start + i]);
            arr_mutex[ind-1].unlock();
        }
        else
        {
            std::cout << "Error with binary search. value to find: " << arr[start + i] <<"\n";
            for (int i=0;i<p_count+1;i++)
            {
                std::cout << p_keys[i] << " ";
            }
            std::cout << "\n";
            return;
        }
    }
}

SampleSort::SampleSort() : p_count(std::thread::hardware_concurrency())
{   arr = new int[NUM_COUNT];
    arr_size = NUM_COUNT;
    blocks.resize(p_count);
};

SampleSort::SampleSort(int size) : p_count(std::thread::hardware_concurrency())
{
    arr = new int[size];
    arr_size = size;
    blocks.resize(p_count);
};
