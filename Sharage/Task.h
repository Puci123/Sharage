#pragma once

class Task
{
	public:
		Task(int deliveryTime, int procesingTime, int coolingTime, int index);
		Task();
		~Task();


		bool operator < (Task &task);

		int GetDeliveryTime();
		int GetProcesingTime();
		int GetCoolingTime();
		int GetIndex();
	
private:
		int _deliveryTime;
		int _procesingTime;
		int _coolingTime;
		int _index;
};
