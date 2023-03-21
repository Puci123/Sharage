#pragma once
#include "Task.h"

class PriorityQueue
{
	public:
		virtual void Insert(Task*) = 0;				//Wstaw elemnt
		virtual Task* Minimum() = 0;				//Zwr�� pierwszy z kolejki
		virtual Task* ExtractMinimum() = 0;			//Zwr�� i us� pierwszy z kolejki 
		virtual bool IsEmpty() = 0;
		
};