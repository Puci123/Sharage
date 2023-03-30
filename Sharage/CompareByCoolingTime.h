#pragma once
#include "Comparator.h"

static class CompareByCoolingTime : public Comparator
{
	public:
		CompareByCoolingTime();
		bool Compare( Task* a, Task* b) override;
		bool  operator() (Task a, Task b);
};

