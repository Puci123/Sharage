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

        std::cout << current->GetIndex() << " ";

        tCost = std::max(tCost, current->GetDeliveryTime()) + current->GetProcesingTime();
        uCost = std::max(uCost, tCost + current->GetCoolingTime());
    }

    auto stop = std::chrono::high_resolution_clock::now();
    timerHandle = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
  
    delete compareByCoolingTime;
    delete compareByDeliveryTime;
    
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
        
        std::cout << curent.GetIndex() << " "; 

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
    
        Task current;


    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < dataSize; i++)
    {
        storedTask.Insert(dataTable[i]);
    }
    
    while (!storedTask.IsEmpty() || !readyTask.IsEmpty())
    {

        while (!storedTask.IsEmpty() && storedTask.Min()._deliveryTime <= tCost)
        {
            readyTask.Insert(storedTask.ExtractMin());
        }

        if (!readyTask.IsEmpty()) 
        {
            current = readyTask.ExtractMin();
        }
        else 


        {
            current = storedTask.ExtractMin();
        }

        std::cout << current.GetIndex() << " ";

        tCost = std::max(tCost, current.GetDeliveryTime()) + current.GetProcesingTime();
        uCost = std::max(uCost, tCost + current.GetCoolingTime());
    }
    auto stop = std::chrono::high_resolution_clock::now();
    timerHandle = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    delete compareByCoolingTime;
    delete compareByDeliveryTime;

    return uCost;

}

int main()
{
   
    int okValue;
    int timerOutput = 0;
   
   //--------------------------------------------------------------------------
    //std::string path = "heap_data2.csv";
    //std::ofstream file;

    //file.open(path,std::ios::ate);
    //file << "data size; Heap time [ns];" << std::endl;
    //file.close();

    //std::cout << "\ndata size  STL time Linqed list queue time" << std::endl;


    //for (int dataSize = 0; dataSize < 100000; dataSize += 10000)
    //{

    //    for (int i = 0; i < 1; i++)
    //    {
    //      
    //        std::cout << dataSize << "  ";
    //        Task* dataTable = CreateRadnomData(dataSize, 4000);
    //        ShrageHeap(dataTable, dataSize, timerOutput);
    //        std::cout << timerOutput << std::endl;


    //        file.open(path, std::ios::app);
    //        file << dataSize << ";" << timerOutput << std::endl;
    //        file.close();

    //        delete[] dataTable;
    //    }
    //}

    //-------------------------------------------------------------


    //----------------------------------
   
    int dataSize;
    std::string path = "sharageDataTest.txt";

    for (int i = 0; i < 8; i++)
    {
        Task* dataTable = LoadData(path, "00" + std::to_string(i), dataSize,okValue);   

        std::cout << path <<" 00" << std::to_string(i) << std::endl << std::endl;
        
        int costLinqedList = ShrageLinkedListQ(dataTable, dataSize, timerOutput);
        std::cout << std::endl << "Linked list prioryty queu cost: " << costLinqedList << std::endl << std::endl;
 

        int costStal = SharageSTL(dataTable, dataSize, timerOutput);
        std::cout << std::endl << "Stl prioryty queu cost: " << costStal << std::endl << std::endl;
        

        int costHeap = ShrageHeap(dataTable, dataSize, timerOutput);
        std::cout << std::endl << "Heap prioryty queu cost: " << costHeap << std::endl << std::endl;
        std::cout << std::endl;

        system("Pause");
        system("cls");

    }
    
    //---------------------------------
    return 0;
}

