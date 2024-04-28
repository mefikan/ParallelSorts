#include "SampleSort.h"

void SampleSort::sort() {
    //num_generate();
    random_numbers_at_file("in.txt");
    file_read(arr, "in.txt");

    auto *timer = new timer_common;

    int numbers_ind = std::rand()%(arr_size-p_count);
    std::cout << "now number id is " << numbers_ind << "\n";


    delete timer;
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
