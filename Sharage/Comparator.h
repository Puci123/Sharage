#pragma once
#include "Task.h"

class Comparator
{
	public:
		virtual bool Compare(Task* a, Task* b) = 0;
		virtual bool Compare(Task a, Task b) = 0;

};