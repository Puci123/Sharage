#pragma once
#include <queue>
#include <vector>
#include <typeinfo>
#include<iostream>
#include "PriorityQueue.h"
#include "Comparator.h"
#include "CompareByDeliveryTime.h"
#include "CompareByCoolingTime.h"
#include "Task.h"



class LTLQueue : public PriorityQueue
{
	public:
		LTLQueue(int key);


		void Insert(Task* task)			override;
		Task* Minimum()					override;
		Task* ExtractMinimum()			override;
		bool IsEmpty()					override;
	
	private:

	


		struct CompareDeliveryTime;

		int _key;
		std::priority_queue<Task*,std::vector<Task*>,CompareByDeliveryTime>   _deliveryQueue;
		std::priority_queue<Task*, std::vector<Task*>, CompareByCoolingTime> _coolingQueue;


};

