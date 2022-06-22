#pragma once

class Counter
{
private:
	int count = 0;

public:
	// Constructor / Destructor
	Counter();
	~Counter();

	// Functions
	void increase();
	int getCount() const;
	void reset();
};