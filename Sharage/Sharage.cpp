#include <iostream>
#include<fstream>
#include<string>

#include "Task.h"


Task* LoadData(std::string dataFilePath, std::string dataLabel, int& dataSizeHandle)
{
    std::ifstream dataFile;
    std::string line;
    Task* output = nullptr;

    dataLabel = "data." + dataLabel + ":";
    dataFile.open(dataFilePath,std::ios::in);

    if (dataFile.is_open())
    {
        while (line != dataLabel)
        {
            dataFile >> line;
        }
        
        dataFile >> line;
        
        dataSizeHandle = std::stoi(line);
        int deliveryTime, procesingTime, coolingTime;
        output = new Task[dataSizeHandle];

        for (int i = 0; i < dataSizeHandle; i++)
        {
            dataFile >> deliveryTime;
            dataFile >> procesingTime;
            dataFile >> coolingTime;

            output[i] = Task(deliveryTime, procesingTime, coolingTime);
        }
     

        dataFile.close();
    }
    else
    {
        std::cout << "Invalid path" << std::endl;
    }

    return output;

}

int CalculateCost(Task* data, int orderLenght, int* order) 
{
    int uCost = 0;
    int tCost = 0;

    for (int i = 0; i < orderLenght; i++)
    {
        tCost = std::max(tCost, data[order[i] - 1].GetDeliveryTime()) + data[order[i] - 1].GetProcesingTime();
        uCost = std::max(uCost, tCost + data[order[i] - 1].GetCoolingTime());
      
    }

    return uCost;
}

int main()
{
    int taskOrder[50] = { 1, 45, 30, 28, 18, 25, 10, 21, 6, 48, 5, 13, 31, 7, 2, 4, 49, 11, 19, 33, 46, 32, 47, 23, 34,
    50, 42, 14, 22, 29, 43, 8, 9, 36, 40, 37, 17, 38, 20, 39, 16, 24, 3, 35, 12, 41, 27, 44, 15, 26 };

    int dataSize;
    Task* dataTable = LoadData("sharageDataTest.txt","001",dataSize);

  

    std::cout << std::endl << "Csot of " << CalculateCost(dataTable, dataSize, taskOrder) << std::endl;
    return 0;
}

