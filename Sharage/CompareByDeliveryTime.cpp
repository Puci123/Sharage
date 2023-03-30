#include "CompareByDeliveryTime.h"


CompareByDeliveryTime::CompareByDeliveryTime() {};

bool CompareByDeliveryTime::Compare(Task* a, Task* b) 
{
	return a->GetDeliveryTime() < b->GetDeliveryTime();

}

bool CompareByDeliveryTime::operator()(const Task a, const Task b) 
{
	return (a._deliveryTime > b._deliveryTime);
}
