#include "Task.h"


Task::Task() 
{
	_coolingTime = -1;
	_deliveryTime = -1;
	_procesingTime = -1;
	_index = -1;
}

Task::Task(int deliveryTime, int procesingTime, int coolingTime, int index)
{
	_deliveryTime = deliveryTime;
	_procesingTime = procesingTime;
	_coolingTime = coolingTime;
	_index = index;
}

Task::~Task() {}

bool Task::operator< (Task &task)
{
	if (this->_deliveryTime < task.GetDeliveryTime()) return true;
	if (this->_deliveryTime == task.GetCoolingTime() && this->_coolingTime >= task.GetCoolingTime()) return true;

	return false;
}

int Task::GetDeliveryTime()  { return _deliveryTime; }
int Task::GetProcesingTime() { return _procesingTime; }
int Task::GetCoolingTime()   { return _coolingTime; }
int Task::GetIndex()		 { return  _index; }