#pragma once
class Task
{
	public:
		Task(int deliveryTime, int procesingTime, int coolingTime);
		Task();
		int GetDeliveryTime();
		int GetProcesingTime();
		int GetCoolingTime();
	
private:
		int _deliveryTime;
		int _procesingTime;
		int _coolingTime;
};
