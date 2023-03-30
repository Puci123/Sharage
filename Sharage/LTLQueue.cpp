#include "LTLQueue.h"



// 0 -> compare by delivery time, 1 -> compare by cooling time
LTLQueue::LTLQueue(int key)
{
	_key = key;
}


void LTLQueue::Insert(Task * task)
{
	if (_key == 0)
		_deliveryQueue.push(task);
	else
		_coolingQueue.push(task);
}

 Task* LTLQueue::ExtractMinimum()
{ 
	Task* temp = nullptr;

	if (_key == 0) 
	{
		temp = _deliveryQueue.top();
		_deliveryQueue.pop();
	}
	else 
	{
		std::cout << "OK!   ";
		temp = _coolingQueue.top();
		_coolingQueue.pop();
	}

	return temp;

}

Task* LTLQueue::Minimum()
{

	Task* temp = nullptr;

	if (_key == 0)
	{
		temp = _deliveryQueue.top();
	}
	else
	{
		temp = _coolingQueue.top();
	}

	return nullptr;
}

bool LTLQueue::IsEmpty() { return true; }

