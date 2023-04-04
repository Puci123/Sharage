#pragma once
#include"Task.h"
#include "Comparator.h"


class HeapQueue
{
	private:
		Task* harr;
		Comparator* comp;
		int capacity;
		int heap_size;
	public:
		HeapQueue(int capacity,Comparator* comparator);
		~HeapQueue();


		void MinHeapify(int);

		int parent(int i) { return (i - 1) / 2; }

		int left(int i) { return (2 * i + 1); }

		int right(int i) { return (2 * i + 2); }

		Task extractMin();

		Task getMin() { return harr[0]; }

		void insertKey(Task k);

		bool isEmpty();
};

