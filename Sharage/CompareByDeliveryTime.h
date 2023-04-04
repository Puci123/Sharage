#pragma once
#include "Comparator.h"

class CompareByDeliveryTime : public Comparator
{
	public:
		CompareByDeliveryTime();
		bool Compare(Task* a, Task* b) override;
		bool Compare(Task a, Task b) override;
		bool  operator() ( Task a, Task b);
};

