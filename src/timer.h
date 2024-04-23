#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>
#include <iomanip>

class timer
{
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::high_resolution_clock clock;
public:
	timer();
	~timer();
};
#endif //TIMER_H