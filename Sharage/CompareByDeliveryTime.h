#pragma once
#include "Comparator.h"

static class CompareByDeliveryTime : public Comparator
{
	public:
		CompareByDeliveryTime();
		bool Compare(Task* a, Task* b) override;

};
