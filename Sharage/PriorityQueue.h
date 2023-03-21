#pragma once
#include "Task.h"

class PriorityQueue
{
	public:
		virtual void Insert(Task*) = 0;				//Wstaw elemnt
		virtual Task* Minimum() = 0;				//Zwróæ pierwszy z kolejki
		virtual Task* ExtractMinimum() = 0;			//Zwróæ i usñ pierwszy z kolejki 
		virtual bool IsEmpty() = 0;
		
};