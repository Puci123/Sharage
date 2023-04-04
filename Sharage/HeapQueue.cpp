#include "HeapQueue.h"


void swap(Task* x, Task* y)
{
	Task temp = *x;
	*x = *y;
	*y = temp;
}

HeapQueue::HeapQueue(int cap, Comparator* c)
{
	_heap_size = 0;
	_capacity = cap;
	_heap = new Task[cap];
	_comp = c;
}

void HeapQueue::Insert(Task k)
{

	_heap_size++;
	int i = _heap_size - 1;
	_heap[i] = k;

	while (i != 0 && !_comp->Compare(_heap[parent(i)],_heap[i]))
	{
		swap(&_heap[i], &_heap[parent(i)]);
		i = parent(i);
	}
}


Task HeapQueue::ExtractMin()
{
	
	if (_heap_size == 1)
	{
		_heap_size--;
		return _heap[0];
	}

	Task root = _heap[0];
	_heap[0] = _heap[_heap_size - 1];
	_heap_size--;
	MinHeapify(0);

	return root;
}

HeapQueue::~HeapQueue()
{
	delete[] _heap;
}

void HeapQueue::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < _heap_size && _comp->Compare(_heap[l], _heap[i]))
		smallest = l;
	if (r < _heap_size && _comp->Compare(_heap[r], _heap[smallest]))
		smallest = r;
	if (smallest != i)
	{
		swap(&_heap[i], &_heap[smallest]);
		MinHeapify(smallest);
	}
}

bool HeapQueue::IsEmpty() 
{
	return _heap_size == 0;
}


