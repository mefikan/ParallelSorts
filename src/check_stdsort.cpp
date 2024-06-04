#include "check_stdsort.h"

check_stdsort::check_stdsort() {

}

QString check_stdsort::sort(int size)
{
    QString result= "Array size is " + QString::number(size) + "\n";;

    std::vector <int> arr(size, 1);

    file_read(arr,"in.txt", size);

    timer_common *timer = new timer_common;

    std::sort(arr.begin(), arr.end());
    result += QString::number(timer->timer_stop()*1e-9) + " sec\n";
    delete timer;
    if (is_array_sorted(arr, size))
    {
        result+= "CHECK: Array is sorted";
    }
    else
    {
        result+= "CHECK: Array is NOT sorted";
    }

    file_write(arr, "out.txt", size);
    return result;
}
