#include "CompareByCoolingTime.h"

CompareByCoolingTime::CompareByCoolingTime() {};

bool CompareByCoolingTime::Compare(Task* a, Task* b)
{
	return a->GetCoolingTime() > b->GetCoolingTime();

}

bool CompareByCoolingTime::operator()(const Task a,const Task b)
{
	return (a._coolingTime < b._coolingTime);
}