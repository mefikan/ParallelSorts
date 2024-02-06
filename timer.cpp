#include "timer.h"

timer::timer()
{
	start = clock.now();
}
timer::~timer()
{
	end = clock.now();
	double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	std::cout << "\n-----TIME-----\n" << std::setprecision(15) << time * 1e-9 << " s\n" << time << " ns\n\n";
}