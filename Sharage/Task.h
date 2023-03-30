#pragma once

 class Task
{
	public:
		Task(int deliveryTime, int procesingTime, int coolingTime, int index);
		Task();
		~Task();


		const int GetDeliveryTime();
		const int GetProcesingTime();
		const int GetCoolingTime();
		const int GetIndex();
	

		int _deliveryTime;
		int _procesingTime;
		int _coolingTime;
		int _index;
};
