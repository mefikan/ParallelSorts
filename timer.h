#pragma once
#include "includes.h"
class timer
{
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::high_resolution_clock clock;
public:
	timer();
	~timer();
};