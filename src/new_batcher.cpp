#include "new_batcher.h"

new_batcher::new_batcher()
{
    arr.resize(NUM_COUNT);
}
new_batcher::new_batcher(int num_count)
{
    arr.resize(num_count);
}
bool new_batcher::is_array_sorted_()
{
    int n = this->arr.size();
    int prev =this->arr[0].getKey();
    for (int i = 1; i < n; i++)
    {
        if (this->arr[i].getKey() < prev)
        {
            std::cout << "Error at! " <<this->arr[i].getKey() << " - " << prev << "\n";
            return 0;
        }
        prev = this->arr[i].getKey();
    }
    return 1;
}
void new_batcher::sort_6_processors()
{
    int task_index=0;
    num_generate();
    count_per_piece = ceil(arr.size()/6.0);
    int count_added_zeroes = abs(arr.size() - count_per_piece*6);
    for (int i=0;i<count_added_zeroes;i++)
    {
        arr.emplace_back(0);
    }
    std::cout << "1) now size is " << arr.size() << "\n2) count_per_piece "<< count_per_piece << "\n3) count_added_zeroes is "<< count_added_zeroes << std::endl;
    //print_array();

    timer_common *t = new timer_common();
    struct sort_piece : public MT::Task {
        int coef;
        new_batcher *batch;
        sort_piece(const std::string &id, new_batcher &b, int cof) : Task(id), batch(&b), coef(cof) {};
        void one_thread_method() override {
            heap_sort_(batch->arr, coef * batch->get_count_per_piece(), batch->get_count_per_piece());
        }
    };
    struct merge_pieces : public MT::Task {
        int coef_1;
        int coef_2;
        new_batcher *batch;
        merge_pieces(const std::string &id, new_batcher &b, int cof1, int cof2) : Task(id), batch(&b), coef_1(cof1), coef_2(cof2)  {};
        void one_thread_method() override {
            batch->merge_2_arrays(coef_1*batch->count_per_piece, coef_2*batch->count_per_piece);
        }
    };

    MT::ThreadPool pool(8);
    pool.set_logger_flag(false);
    pool.start();

    //sorting 6 pieces in parallel
    for (int i=0;i<6;i++)
    {
        pool.add_task(sort_piece("TestTask_" + std::to_string(task_index++), *this, i));
    }
    pool.wait();

    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,0, 1));
    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,2, 3));
    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,4, 5));
    pool.wait();

    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,0, 2));
    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,3, 5));
    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,1, 4));
    pool.wait();

    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,0, 1));
    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,2, 3));
    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,4, 5));
    pool.wait();

    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,1, 2));
    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,3, 4));
    pool.wait();
    pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++),*this,2, 3));
    pool.wait();

    delete t;

    if (this->is_array_sorted_())
    {
        std::cout << "Array is sorted!\n";
    }
    else
    {
        std::cout << "Not sorted!\n";
    }
}
void new_batcher::sort_16_processors() {
    int task_index=0;
    num_generate();
    count_per_piece = ceil(arr.size()/16.0);
    int count_added_zeroes = abs(arr.size() - count_per_piece*16);
    for (int i=0;i<count_added_zeroes;i++)
    {
        arr.emplace_back(0);
    }
    std::cout << "1) now size is " << arr.size() << "\n2) count_per_piece "<< count_per_piece << "\n3) count_added_zeroes is "<< count_added_zeroes << std::endl;


    //tasks to threadpool
    struct sort_piece : public MT::Task {
        int coef;
        new_batcher *batch;
        sort_piece(const std::string &id, new_batcher &b, int cof) : Task(id), batch(&b), coef(cof) {};
        void one_thread_method() override {
            heap_sort_(batch->arr, coef * batch->get_count_per_piece(), batch->get_count_per_piece());
            //std::sort(&batch->arr[coef * batch->get_count_per_piece()], &batch->arr[coef * batch->get_count_per_piece() + batch->get_count_per_piece()]);
        }
    };
    struct merge_pieces : public MT::Task {
        int coef_1;
        int coef_2;
        new_batcher *batch;
        merge_pieces(const std::string &id, new_batcher &b, int cof1, int cof2) : Task(id), batch(&b), coef_1(cof1), coef_2(cof2)  {};
        void one_thread_method() override {
            batch->merge_2_arrays(coef_1*batch->count_per_piece, coef_2*batch->count_per_piece);
        }
    };

    MT::ThreadPool pool(8);
    pool.set_logger_flag(false);
    pool.start();

    //print_array();
    timer_common *timer = new timer_common;
    //sorting 6 pieces in parallel
    for (int i=0;i<16;i++)
    {
        pool.add_task(sort_piece("TestTask_" + std::to_string(task_index++), *this, i));
    }
    pool.wait();

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
    //net merging
    for (int i=0;i<10;i++) {
        //std::cout << "i is " << i << std::endl;
        //print_array();
        for (auto [a_, b_]: indexes[i]) {
            pool.add_task(merge_pieces("TestTask_" + std::to_string(task_index++), *this, a_, b_));
        }
        pool.wait();
    }
    delete timer;
    if (this->is_array_sorted_())
    {
        std::cout << "Array is sorted!\n";
    }
    else
    {
        std::cout << "Not sorted!\n";
    }
    //print_array();
}
void new_batcher::num_generate()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 1000);
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
