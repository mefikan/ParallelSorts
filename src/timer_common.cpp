#include "timer_common.h"

timer_common::timer_common()
{
    start = std::chrono::steady_clock::now();
}
timer_common::~timer_common()
{
    //std::cout << "\n-----TIME-----\n" << std::setprecision(15) << time * 1e-9 << " s\n" << time << " ns\n\n";
}
double timer_common::timer_stop()
{
    end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return time;
}
