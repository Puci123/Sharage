#pragma once
#include "Task.h"

static class Comparator
{
	public:
		virtual bool Compare(Task* a, Task* b) = 0;

};