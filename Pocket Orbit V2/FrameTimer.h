#pragma once

#include <chrono>

class FrameTimer
{
private:
	std::chrono::steady_clock::time_point last;

public:
	// Constructor / Destructor
	FrameTimer();
	~FrameTimer();

	// Functions
	float mark();
};