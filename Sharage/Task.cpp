#include "Task.h"


Task::Task() {}

Task::Task(int deliveryTime, int procesingTime, int coolingTime)
{
	_deliveryTime = deliveryTime;
	_procesingTime = procesingTime;
	_coolingTime = coolingTime;
}

int Task::GetDeliveryTime()  { return _deliveryTime; }
int Task::GetProcesingTime() { return _procesingTime; }
int Task::GetCoolingTime()   { return _coolingTime; }