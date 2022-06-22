#include "Counter.h"


// Constructor / Destructor
Counter::Counter()
{
}

Counter::~Counter()
{
}

// Functions
void Counter::increase()
{
	this->count++;
}

int Counter::getCount() const
{
	return this->count;
}

void Counter::reset()
{
	this->count = 0;
}