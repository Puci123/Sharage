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

const int Task::GetDeliveryTime()  { return _deliveryTime; }
const int Task::GetProcesingTime() { return _procesingTime; }
const int Task::GetCoolingTime()   { return _coolingTime; }
const int Task::GetIndex()		 { return  _index; }