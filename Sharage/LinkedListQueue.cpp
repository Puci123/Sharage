#include "LinkedListQueue.h"



LinkedListQueue::LinkedListQueue(Comparator* comparator) 
{
	_head = CreateNode(nullptr);
	_comparator = comparator;
}

LinkedListQueue::Node* LinkedListQueue::CreateNode(Task *task) 
{
	Node* node = new Node();
	node->nextNode = nullptr;
	node->data = task;

	return node;
}

void LinkedListQueue::Insert(Task *task) 
{
	Node* curentNode = _head;

	while (true)
	{
		if (curentNode->nextNode == nullptr) 
		{
			curentNode->nextNode = CreateNode(task);
			break;

		}
		else if (_comparator->Compare(task,curentNode->nextNode->data))
		{
			Node* temp = curentNode->nextNode;
			curentNode->nextNode = CreateNode(task);
			curentNode->nextNode->nextNode = temp;

			break;
		}
		
		curentNode = curentNode->nextNode;
	}


}

Task* LinkedListQueue::ExtractMinimum() 
{
	Task* firstTask = _head->nextNode->data;
	Node* temp = _head->nextNode;

	_head->nextNode = _head->nextNode->nextNode;
	delete temp;

	return firstTask;
}

Task* LinkedListQueue::Minimum()
{ 
	return _head->nextNode->data;
}

bool LinkedListQueue::IsEmpty() 
{
	return _head->nextNode == nullptr;
}
