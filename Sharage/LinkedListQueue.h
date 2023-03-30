#pragma once
#include <iostream>
#include "Comparator.h"

class LinkedListQueue
{
	public:
		LinkedListQueue(Comparator* comparator);

		void Insert(Task* task);
		 Task* Minimum();
		 Task* ExtractMinimum();
		 bool IsEmpty();

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

