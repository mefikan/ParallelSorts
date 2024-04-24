#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>
#include <iomanip>

class timer_common
{
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::high_resolution_clock clock;
public:
	timer_common();
	~timer_common();
};
#endif //TIMER_H