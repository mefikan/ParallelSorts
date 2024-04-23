#include "new_batcher.h"

new_batcher::new_batcher()
{
    arr.resize(NUM_COUNT);
}
new_batcher::new_batcher(int num_count)
{
    arr.resize(num_count);
}
void new_batcher::sort_6_processors()
{
    num_generate();
    count_per_piece = ceil(arr.size()/6.0);
    int count_added_zeroes = abs(arr.size() - count_per_piece*6);
    for (int i=0;i<count_added_zeroes;i++)
    {
        arr.emplace_back(0);
    }
    std::cout << "1) now size is " << arr.size() << "\n2) count_per_piece "<< count_per_piece << "\n3) count_added_zeroes is "<< count_added_zeroes << std::endl;
    print_array();


    heap_sort_(this->arr, 0*this->get_count_per_piece(), this->get_count_per_piece());
    heap_sort_(this->arr, 1*this->get_count_per_piece(), this->get_count_per_piece());
    heap_sort_(this->arr, 2*this->get_count_per_piece(), this->get_count_per_piece());
    heap_sort_(this->arr, 3*this->get_count_per_piece(), this->get_count_per_piece());
    heap_sort_(this->arr, 4*this->get_count_per_piece(), this->get_count_per_piece());
    heap_sort_(this->arr, 5*this->get_count_per_piece(), this->get_count_per_piece());

    print_array();

    merge_2_arrays(0*count_per_piece, 1*count_per_piece);
}
void new_batcher::num_generate()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    for (int i = 0;i < arr.size(); i++)
    {
        arr[i].setKey(dist(mt));
    }
    std::cout << "Numbers generated!\n";
    /*for (int i=0;i<size;i++)
    {
        std::cout << arr[i].getKey() << " ";
    }
    */
}
void new_batcher::merge_2_arrays(const unsigned int &start1, const unsigned int &start2)
{
    //end index included
    //first will have the biggest elements part
    std::vector <Element> buffer(count_per_piece*2);
    int ind1, ind2, i = 0;
    for ( ind1 = start1, ind2 = start2 ;ind1 < count_per_piece + start1 && ind2 < count_per_piece + start2; )
    {
        if (arr[ind1].getKey() < arr[ind2].getKey())
        {
            buffer[i++] = arr[ind1++].getKey();
        }
        else
        {
            buffer[i++] = arr[ind2++].getKey();
        }
    }
    while (ind1 < count_per_piece + start1)
    {
        buffer[i++] = arr[ind1++].getKey();
    }
    while (ind2 < count_per_piece + start2)
    {
        buffer[i++] = arr[ind2++].getKey();
    }
    for (int j = 0; j < count_per_piece; j++)
    {
        arr[j+start1] = buffer[j];
        arr[j+start2] = buffer[j+count_per_piece];
    }
    for (int g=0;g<buffer.size();g++)
    {
        if (g==buffer.size()/2)
        {
            std::cout << "\n";
        }

        std::cout << buffer[g].getKey() << " ";
    }
}
void new_batcher::print_array()
{
    for (int i=0;i<arr.size();i++)
    {
        std::cout << (i!=0 && i%count_per_piece==0 ?  "\n" :  "");
        std::cout << std::setw(3) <<arr[i].getKey() << " ";
    }
    std::cout << "\n\n";
}
