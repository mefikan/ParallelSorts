#include "SampleSort.h"

std::array<std::mutex, 8> arr_mutex;

void SampleSort::sort() {
    //num_generate();
    random_numbers_at_file("in1.txt");
    file_read(arr, "in1.txt");

    if (NUM_COUNT<p_count*10)
    {
        //отсортировать обычной сортировкой
        heap_sort_asc(arr,NUM_COUNT);
        return;
    }

    auto *timer = new timer_common;

    //1
    srand(time(NULL));
    numbers_ind = std::rand()%(arr_size-p_count*10-1);

    //2,3
    p_keys = new int[p_count];
    /*for (int i=0;i<p_count*10;i++)
    {
        if (i%10==0) {
            p_keys[i/10] = arr[i + numbers_ind];
        }
    }*/
    int max_num = MAX_NUM+1000;
    int min_num = 0;
    for (int i=0;i<p_count;i++)
    {
        p_keys[i] = max_num*(i+1)/p_count;
        //std::cout << p_keys[i] << " ";
    }
    std::cout << "\n";

    //Распределение, делаю параллельным с использованием мьютекса
    std::vector <std::thread> vec(p_count);
    int count_per_block = arr_size/p_count;
    for (int i=0;i<p_count;i++)
    {

        if (i != p_count-1)
        {
            //separate(i * count_per_block, count_per_block);
            vec[i] = std::thread([this](const int start, const int count){this->separate(start, count);}, i*count_per_block, count_per_block);
        }
        else
        {
            //separate(i * count_per_block, arr_size - i * count_per_block);
            vec[i] = std::thread([this](const int start, const int count){this->separate(start, count);}, i*count_per_block, arr_size-i*count_per_block);
        }
    }
    {
        for (int i=0;i<p_count;i++)
        {
            vec[i].join();
        }
    }
    delete []arr;

    //Тут отсортирую
    /*std::cout << "before sort\n";
    for (auto c : blocks)
    {
        for (auto d : c)
        {
            std::cout << d << " ";
        }
        std::cout << "\n";
    }*/
    /*for (auto c : blocks)
    {
        std::cout << c.size() << "\n";
    }*/

    for (int i=0;i<p_count;i++)
    {
        vec[i] = std::thread(heap_sort_asc_, std::ref(blocks[i]), blocks[i].size());
    }
    for (int i=0;i<p_count;i++)
    {
        vec[i].join();
    }

    //Тут клею
    arr = new int[NUM_COUNT];
    int ind_arr=0;
    for (int i=0; i<p_count;i++)
    {
        for (int j=0;j<blocks[i].size();j++)
        {
            arr[ind_arr++] = blocks[i][j];
        }
    }
    delete timer;

    if (is_array_sorted(arr,arr_size))
    {
        std::cout << "Sorted!\n";
    }
    else
    {
        std::cout << "Not sorted!\n";
    }
    file_write(arr, "out.txt");
    //print_array();
    delete [] arr;
}
void SampleSort::num_generate() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100000);
    for (int i = 0;i < arr_size; i++)
    {
        arr[i] = (dist(mt));
    }
    std::cout << "Numbers generated!\n";
}
void SampleSort::print_array() {
    for (int i=0;i<arr_size;i++)
    {
        //std::cout << (i!=0 && i%count_per_piece==0 ?  "\n" :  "");
        std::cout << std::setw(3) << arr[i] << " ";
    }
    std::cout << "\n\n";
}
int SampleSort::binary_search(const int start, const int end, const int num) {
    int l = start;
    int r = end;
    while (l<r)
    {
        int m = l + (r-l)/2;

        if (p_keys[m] == num)
            return m;
        else if (m+1 <= r &&  num > p_keys[m] && num < p_keys[m+1])
            return m+1;
        else if (m-1 >=0 && num < p_keys[m] && num > p_keys[m-1])
            return m;
        else if (num > p_keys[m])
        {
            l = m+1;
        }
        else
        {
            r = m-1;
        }
    }
    if (l==r && l==start)
    {
        return start;
    }
    else if (l==r && r==end)
    {
        return end;
    }
    return -1;
}
void SampleSort::separate(const int start, const int count) {

    for (int i=0;i<count;i++)
    {
        int ind=-1;// = binary_search(start, p_count, arr[start+i]);
        for (int j=0; j<p_count; j++)
        {
            if (arr[start+i]<p_keys[j])
            {
                ind = j;
                break;
            }
        }
        //std::cout << "index " << ind << "\n";
        if (ind!=-1)
        {
            arr_mutex[ind].lock();
            blocks[ind].push_back(arr[start + i]);
            arr_mutex[ind].unlock();
        }
        else
        {
            std::cout << "Error with binary search. value to find: " << arr[start + i] <<"\n";
            for (int i=0;i<p_count;i++)
            {
                std::cout << p_keys[i] << " ";
            }
            std::cout << "\n";
            return;
        }
    }
}
