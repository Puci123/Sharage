#include "CompareByDeliveryTime.h"


CompareByDeliveryTime::CompareByDeliveryTime() {};

bool CompareByDeliveryTime::Compare(Task* a, Task* b) 
{
	return a->GetDeliveryTime() <= b->GetDeliveryTime();

}
