#pragma once
#include "PriorityQueue.h"
#include <iostream>
#include "Comparator.h"

class LinkedListQueue : public PriorityQueue
{
	public:
		LinkedListQueue(Comparator* comparator);

		 void Insert(Task *task)		override;			
		 Task* Minimum()				override;
		 Task* ExtractMinimum()			override;
		 bool IsEmpty()					override;

	private:
		
		struct Node
		{
			Task* data;
			Node* nextNode;
		};

		Node* CreateNode(Task *task);


		Node* _head;
		Comparator* _comparator;

};

