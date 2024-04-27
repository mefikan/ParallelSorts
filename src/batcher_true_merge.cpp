#include "batcher_true_merge.h"

void batcher_true_merge::merge(const unsigned int &start1, const unsigned int &start2) {
    //end index included
    //merge 2 bitonic sequences into 2 bitonic sequences
    for (int i=0;i<count_per_piece;i++)
    {
        if (arr[start1 + i] > arr[start2 + i])
        {
            std::swap(arr[start1 + i], arr[start2 + i]);
        }
    }
}

void batcher_true_merge::sort_16() {
    count_per_piece = ceil(arr_size/16.0);
    //num_generate(); //can be chosen to generate array here, not in the file
    random_numbers_at_file("in.txt");
    file_read(arr, "in.txt");
    stream_count=16;
    timer_common *timer = new timer_common;

    //add zeroes to make piece sizes equal
    unsigned int count_added_zeroes = abs(arr_size - count_per_piece*16);
    int *buf = new int[NUM_COUNT + count_added_zeroes];
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
    arr_size = NUM_COUNT + count_added_zeroes;
    //std::cout << "1) now size is " << arr_size << "\n2) count_per_piece "<< count_per_piece << "\n3) count_added_zeroes is "<< count_added_zeroes << std::endl;

    //main sort
    std::vector<std::thread> vec(stream_count);
    /*for (int i=0;i<stream_count;i++)
    {
        if (i%2==0) {
            vec[i] = std::thread(heap_sort_asc, &arr[i * count_per_piece], count_per_piece);
        }
        else
        {
            vec[i] = std::thread(heap_sort_desc, &arr[i*count_per_piece], count_per_piece);
        }

    }
    for (int i=0;i<stream_count;i++)
    {
        vec[i].join(); //join means that we wait here when processes will end their work.
    }
    vec.resize(stream_count/2); //delete extra threads*/
    //print_array(); //debug

    //merge matrix scheme
    std::vector <std::vector <std::pair<int, int>>> indexes =
            {
                    {{0,1}, {3,2}, {4,5}, {7,6}, {8,9},{11,10}, {12,13}, {15,14}},  //1
                    {{0,2}, {1,3}, {6,4}, {7,5},{8,10},{9,11},{14,12}, {15,13}},    //2
                    {{0,1}, {2,3}, {5,4}, {7,6},{8,9},{10,11},{13,12}, {15,14}},    //3
                    {{0,4}, {1,5}, {2,6}, {3,7},{12,8},{13,9},{14,10}, {15,11}},    //4
                    {{0,2}, {1,3}, {4,6}, {5,7},{10,8},{11,9},{14,12}, {15,13}},    //5
                    {{0,1}, {2,3}, {4,5}, {6,7},{9,8},{11,10},{13,12}, {15,14}},    //6
                    {{0,8}, {1,9}, {2,10}, {3,11},{4,12},{5,13},{6,14}, {7,15}},    //7
                    {{0,4}, {1,5}, {2,6}, {3,7},{8,12},{9,13},{10,14}, {11,15}},    //8
                    {{0,2}, {1,3}, {4,6}, {5,7},{8,10},{9,11},{12,14}, {13,15}},    //9
                    {{0,1}, {2,3}, {4,5}, {6,7},{8,9},{10,11},{12,13}, {14,15}}     //10
            };
    //network merge
    for (int g=0;g<10;g++) {
        for (int i = 0; i < stream_count/2; i++) {
            int first_pair_val  = indexes[g][i].first;
            int second_pair_val  = indexes[g][i].second;
            vec[i] = std::thread([this](int first_pair_val, int second_pair_val){
                this->merge(first_pair_val * this->count_per_piece, second_pair_val * this->count_per_piece);}, first_pair_val, second_pair_val);
        }
        for (int j=0;j<stream_count/2;j++) {
            vec[j].join();
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
    print_array();
    delete [] arr;
}

void batcher_true_merge::print_array() {
    for (int i=0;i<arr_size;i++)
    {
        std::cout << (i!=0 && i%count_per_piece==0 ?  "\n" :  "");
        std::cout << std::setw(3) << arr[i] << " ";
    }
    std::cout << "\n\n";
}
