#pragma once
#include "Comparator.h"

class CompareByCoolingTime : public Comparator
{
	public:
		CompareByCoolingTime();
		bool Compare( Task* a, Task* b) override;
		bool Compare(Task a, Task b) override;
		bool  operator() (Task a, Task b);
};

