#include "HeapQueue.h"


void swap(Task* x, Task* y)
{
	Task temp = *x;
	*x = *y;
	*y = temp;
}

HeapQueue::HeapQueue(int cap, Comparator* c)
{
	heap_size = 0;
	capacity = cap;
	harr = new Task[cap];
	comp = c;
}

void HeapQueue::insertKey(Task k)
{

	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	while (i != 0 && !comp->Compare(harr[parent(i)],harr[i]))
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}


Task HeapQueue::extractMin()
{
	if (heap_size <= 0)
		return Task();

	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	Task root = harr[0];
	harr[0] = harr[heap_size - 1];
	heap_size--;
	MinHeapify(0);

	return root;
}

HeapQueue::~HeapQueue()
{
	delete[] harr;
}

void HeapQueue::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && comp->Compare(harr[l], harr[i]))
		smallest = l;
	if (r < heap_size && comp->Compare(harr[r], harr[smallest]))
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}

bool HeapQueue::isEmpty() 
{
	return heap_size == 0;
}


