#include "FrameTimer.h"

using namespace std::chrono;

// Constructor / Destructor
FrameTimer::FrameTimer()
{
	this->last = steady_clock::now();
}

FrameTimer::~FrameTimer()
{
}

// Functions
float FrameTimer::mark()
{
	const auto old = this->last;
	this->last = steady_clock::now();
	const duration<float> frameTime = this->last - old;
	return frameTime.count();
}