#include "CompareByCoolingTime.h"

CompareByCoolingTime::CompareByCoolingTime() {};

bool CompareByCoolingTime::Compare(Task* a, Task* b)
{
	return a->GetCoolingTime() >= b->GetCoolingTime();

}