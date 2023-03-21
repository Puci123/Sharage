#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "Task.h"
#include "PriorityQueue.h"
#include "LinkedListQueue.h"
#include "CompareByDeliveryTime.h"
#include "CompareByCoolingTime.h"

Task* LoadData(std::string dataFilePath, std::string dataLabel, int& dataSizeHandle, int& okValue)
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

            output[i] = Task(deliveryTime, procesingTime, coolingTime,i);
        }
        
        dataFile >> line;
        dataFile >> line;
        dataFile >> line;
        dataFile >> okValue;



        dataFile.close();
    }
    else
    {
        std::cout << "Invalid path" << std::endl;
    }

    return output;

}

template<typename T> int CalculateCost(Task* dataTable,int dataSize,int &timerHandle , Comparator* compareByDeliveryTime, Comparator* compareByCoolingTime)
{
    int uCost = 0;
    int tCost = 0;
    Task* current = nullptr;
    
    PriorityQueue* pQueue = new T(compareByDeliveryTime);
    PriorityQueue* redyTask = new T(compareByCoolingTime);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < dataSize; i++)
    {
        pQueue->Insert(&dataTable[i]);
    }

    while (!pQueue->IsEmpty() || !redyTask->IsEmpty())
    {
        
        while(!pQueue->IsEmpty() && pQueue->Minimum()->GetDeliveryTime() <= tCost)
        {
            redyTask->Insert(pQueue->ExtractMinimum());
        }

        if (!redyTask->IsEmpty())
            current = redyTask->ExtractMinimum();
        else
            current = pQueue->ExtractMinimum();


        tCost = std::max(tCost, current->GetDeliveryTime()) + current->GetProcesingTime();
        uCost = std::max(uCost, tCost + current->GetCoolingTime());

    }

    auto stop = std::chrono::high_resolution_clock::now();
    timerHandle = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
  
    delete redyTask;
    return uCost;
}

int main()
{
   
    int dataSize;
    int okValue;
    int timerOutput;

    Comparator* compareByDeliveryTime = new CompareByDeliveryTime();
    Comparator* compareByCoolingTime  = new CompareByCoolingTime();

    PriorityQueue* pQueue = new LinkedListQueue(compareByDeliveryTime);
    
    std::cout << "\n\n";

    //----------------------------------
    for (int i = 1; i < 8; i++)
    {
        Task* dataTable = LoadData("sharageDataTest.txt", "00" + std::to_string(i), dataSize,okValue);
        int cost = CalculateCost<LinkedListQueue>(dataTable, dataSize,timerOutput, compareByDeliveryTime, compareByCoolingTime);

        std::cout << "Linked list queue " << i <<") " << cost << " / " << okValue;

        if (cost == okValue) std::cout << " \033[0;32mOK!\033[0m" << "  time consumed: " << timerOutput << " ns";
        std::cout << std::endl;
    }
    
    //---------------------------------

    return 0;
}

