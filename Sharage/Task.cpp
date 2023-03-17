#include "Task.h"


Task::Task() {}

Task::Task(int deliveryTime, int procesingTime, int coolingTime)
{
	_deliveryTime = deliveryTime;
	_procesingTime = procesingTime;
	_coolingTime = coolingTime;
}

bool Task::operator< (Task &task)
{
	if (this->_deliveryTime < task.GetDeliveryTime()) return true;
	if (this->_deliveryTime == task.GetCoolingTime() && this->_coolingTime >= task.GetCoolingTime()) return true;

	return false;
}

int Task::GetDeliveryTime()  { return _deliveryTime; }
int Task::GetProcesingTime() { return _procesingTime; }
int Task::GetCoolingTime()   { return _coolingTime; }