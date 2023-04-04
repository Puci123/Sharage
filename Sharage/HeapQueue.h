#pragma once
#include"Task.h"
#include "Comparator.h"


class HeapQueue
{
	private:
		Task* _heap;
		Comparator* _comp;
		int _capacity;
		int _heap_size;
	public:
		HeapQueue(int capacity,Comparator* comparator);
		~HeapQueue();


		void MinHeapify(int);

		int parent(int i) { return (i - 1) / 2; }

		int left(int i) { return (2 * i + 1); }

		int right(int i) { return (2 * i + 2); }

		Task ExtractMin();

		Task Min() { return _heap[0]; }

		void Insert(Task k);

		bool IsEmpty();
};

