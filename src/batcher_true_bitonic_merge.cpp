#include "batcher_true_bitonic_merge.h"

void batcher_true_bitonic_merge::merge(const unsigned int &start1, const unsigned int &start2) {
    //end index included
    //merge 2 bitonic sequences into 2 bitonic sequences

    if (arr[start1] > arr[start2])
    {
        std::swap(arr[start1], arr[start2]);
    }

}
batcher_true_bitonic_merge::batcher_true_bitonic_merge(){
    arr = new int[NUM_COUNT];
    arr_size = NUM_COUNT;
    //merge matrix scheme - идем по строкам - каждая строка - "ступень сети"
};
struct sort_asc_desc : public MT::Task {
    sort_asc_desc(const std::string &description, int *arr, const int arr_size, int start, bool is_asc)
            : Task(description)
    {
        if (is_asc)
        {
            heap_sort_asc(&arr[start], arr_size);
        }
        else
        {
            heap_sort_desc(&arr[start], arr_size);
        }
    };
    void one_thread_method() override
    {}
};
struct comparator_exchange : public MT::Task {
    comparator_exchange(const std::string &description, int *arr, const int arr_size,int start1, int start2)
            : Task(description)
    {
        for (int i=0;i<arr_size;i++)
        {
            exchange(arr[start1 + i], arr[start2 + i]);
        }
    };
    void one_thread_method() override
    {}
    void exchange(int &val1, int &val2)
    {
        if (val1>val2)
        {
            std::swap(val1, val2);
        }
    }
};
void batcher_true_bitonic_merge::sort() {
    //num_generate(); //can be chosen to generate array here, not in the file
    random_numbers_at_file("in.txt");
    file_read(arr, "in.txt");
    stream_count=8;
    timer_common *timer = new timer_common;

    unsigned int count_added_zeroes = pow(2,std::ceil(log2(arr_size))) - arr_size;
    std::cout << count_added_zeroes << "\n";

    //Добавление незначащих нулей
    if (count_added_zeroes!=0) {
        int *buf = new int[NUM_COUNT + count_added_zeroes];
        for (int i = 0; i < arr_size; i++) {
            buf[i] = arr[i];
        }
        for (int i = 0; i < count_added_zeroes; i++) {
            buf[arr_size + i] = 0;
        }
        delete[]arr;
        arr = buf;
        arr_size = NUM_COUNT + count_added_zeroes;
        std::cout << "now size is " << arr_size << "\n";
    }





    //основная часть алгоритма
    MT::ThreadPool pool(8);
    pool.set_logger_flag(false);
    pool.start();

    for (int mult = 2; mult<arr_size;mult*=2) {
        for (int i=0;i<mult;i++)
        {

        }




        for (int i = 0; i < mult; i++) {
            pool.add_task(comparator_exchange("thread", std::ref(arr), arr_size / mult, i * arr_size / mult,
                                              i * arr_size / (mult * 2)));
        }
        for (int j=0;j<arr_size;j++)
        {
            if (j == (arr_size/mult))
            {
                std::cout << std::setw(4) <<"\n" <<arr[j] << " ";
            }
            else
            {
                std::cout << std::setw(4) << arr[j] << " ";
            }
        }
        std::cout << "\n\n";
    }
    return;
    
    delete timer;
    if (is_array_sorted(arr,arr_size))
    {
        std::cout << "Sorted!\n";
    }
    else
    {
        std::cout << "Not sorted!\n";
    }
    //file_write(arr, "out.txt");
    print_array();
    delete [] arr;
}

void batcher_true_bitonic_merge::print_array() {
    for (int i=0;i<arr_size;i++)
    {
        std::cout << (i!=0 && i%16==0 ?  "\n" :  "");
        std::cout << std::setw(5) << arr[i] << " ";
    }
    std::cout << "\n\n";
}
