#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <queue>
#include <vector>

#include "Task.h"
#include "LinkedListQueue.h"
#include "CompareByDeliveryTime.h"
#include "CompareByCoolingTime.h"
#include "HeapQueue.h"

Task* CreateRadnomData(int dataSize,int maxRange) 
{
    Task* data = new Task[dataSize];

    for (int i = 0; i < dataSize; i++)
    {
        data[i] = Task(rand() % maxRange, rand() % maxRange, rand() % maxRange, -1);
    }

    return data;
}

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

int ShrageLinkedListQ(Task* dataTable,int dataSize,int &timerHandle)
{
    int uCost = 0;
    int tCost = 0;
    Comparator* compareByDeliveryTime = new CompareByDeliveryTime();
    Comparator* compareByCoolingTime = new CompareByCoolingTime();



    LinkedListQueue storedTask(compareByDeliveryTime);
    LinkedListQueue redyTask(compareByCoolingTime);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < dataSize; i++)
    {
        storedTask.Insert(&dataTable[i]);
    }

    int k = 0;

    while (!storedTask.IsEmpty() || !redyTask.IsEmpty())
    {
        Task* current = nullptr;


        while(!storedTask.IsEmpty() && storedTask.Minimum()->GetDeliveryTime() <= tCost)
        {
            redyTask.Insert(storedTask.ExtractMinimum());
        }

        if (!redyTask.IsEmpty())
            current = redyTask.ExtractMinimum();
        else
            current = storedTask.ExtractMinimum();


        tCost = std::max(tCost, current->GetDeliveryTime()) + current->GetProcesingTime();
        uCost = std::max(uCost, tCost + current->GetCoolingTime());
    }

    auto stop = std::chrono::high_resolution_clock::now();
    timerHandle = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
  
    //delete redyTask;
    return uCost;
}

int SharageSTL(Task* data,int dataSize, int &timerHandle) 
{
    int uCost = 0;
    int tCost = 0;
    Task curent;

    std::priority_queue<Task, std::vector<Task>, CompareByDeliveryTime> storedTasks;
    std::priority_queue<Task, std::vector<Task>, CompareByCoolingTime>  readyTasks;

    auto start = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < dataSize; i++)
    {
        storedTasks.push(data[i]);
    }
    int klak = 0;
    while (!storedTasks.empty() || !readyTasks.empty())
    {
        
        
   
        while (!storedTasks.empty() && storedTasks.top()._deliveryTime <= tCost)
        {
            readyTasks.push(storedTasks.top());
            storedTasks.pop();
        }
        

        if (!readyTasks.empty()) 
        {
            curent = readyTasks.top();
            readyTasks.pop();

        }
        else
        {
            curent = storedTasks.top();
            storedTasks.pop();
        }

        tCost = std::max(tCost, curent.GetDeliveryTime()) + curent.GetProcesingTime();
        uCost = std::max(uCost, tCost + curent.GetCoolingTime());
        
    }
    
    auto stop = std::chrono::high_resolution_clock::now();
    timerHandle = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    return uCost;
}

int ShrageHeap(Task* dataTable, int dataSize, int& timerHandle) 
{
    int uCost = 0;
    int tCost = 0;

    Comparator* compareByDeliveryTime = new CompareByDeliveryTime();
    Comparator* compareByCoolingTime = new CompareByCoolingTime();

    HeapQueue storedTask(dataSize,compareByDeliveryTime);
    HeapQueue readyTask(dataSize, compareByCoolingTime);
    
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < dataSize; i++)
    {
        storedTask.insertKey(dataTable[i]);
    }
    
    while (!storedTask.isEmpty())
    {

        while (!storedTask.isEmpty() && storedTask.getMin()._deliveryTime <= tCost)
        {
            readyTask.insertKey(storedTask.extractMin());
        }

        Task current;
        if (!readyTask.isEmpty())
            current = readyTask.extractMin();
        else
            current = storedTask.extractMin();

        tCost = std::max(tCost, current.GetDeliveryTime()) + current.GetProcesingTime();
        uCost = std::max(uCost, tCost + current.GetCoolingTime());
    }
    auto stop = std::chrono::high_resolution_clock::now();
    timerHandle = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    return uCost;

}

int main()
{
   
    int okValue;
    int timerOutput = 0;
   

    std::string path = "heap_data2.csv";
    std::ofstream file;

    file.open(path,std::ios::ate);
    file << "data size; Heap time [ns];" << std::endl;
    file.close();

    std::cout << "\ndata size  STL time Linqed list queue time" << std::endl;


    for (int dataSize = 0; dataSize < 100000; dataSize += 10000)
    {

        for (int i = 0; i < 1; i++)
        {
          
            std::cout << dataSize << "  ";
            Task* dataTable = CreateRadnomData(dataSize, 4000);
            ShrageHeap(dataTable, dataSize, timerOutput);
            std::cout << timerOutput << std::endl;


            file.open(path, std::ios::app);
            file << dataSize << ";" << timerOutput << std::endl;
            file.close();

            delete[] dataTable;
        }
    }


    //----------------------------------

    //int timerOutput;
    //for (int i = 0; i < 8; i++)
    //{
    //    Task* dataTable = LoadData("sharageDataTest.txt", "00" + std::to_string(i), dataSize,okValue);    
    //    int cost = ShrageHeap(dataTable, dataSize, timerOutput);
    //    //int cost = ShrageLinkedListQ(dataTable, dataSize, timerOutput);


    //    std::cout << "Linked list queue " << i <<") " << cost << " / " << okValue;

    //    if (cost == okValue) std::cout << " \033[;32mOK!\033[0m" << "  time consumed: " << timerOutput << " ns";
    //    std::cout << std::endl;
    //}
    
    //---------------------------------

   /* Comparator* compareByDeliveryTime = new CompareByDeliveryTime();
    HeapQueue storedTask(compareByDeliveryTime);
    storedTask.Insert(Task(1, 1, 1, 1));*/


    return 0;
}

