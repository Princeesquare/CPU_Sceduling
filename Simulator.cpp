#include <iostream>
#include <fstream>
//#include <vector>


#define SIZE 5
#define LINE_MAX 1024

struct Process {
    int Name;
    int Burst_Time;
    int Arrival_Time; 
    int Waiting_Time;
    int priority;     
};

void InsertQ(Process* queue, int& rear, const Process& element) {
    queue[rear] = element;
    rear++;
}

void DelQ(Process* queue, int& front, int& rear) {
    if (front < rear) {
        front++;
    }
}

Process InsertFront(const Process* queue, int front) {
    return queue[front];
}

bool isEmptyQ(int front, int rear) {
    return front == rear;
}

void bubbleSort(Process* processes, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (processes[j].Arrival_Time > processes[j + 1].Arrival_Time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void RoundRobin(Process* processes, int quantumTime) {
    Process processQueue[SIZE];
    int front = 0, rear = 0;
    int currentTime = 0;

    while (!isEmptyQ(front, rear) || currentTime < SIZE) {
        while (currentTime < SIZE && processes[currentTime].Arrival_Time <= currentTime) {
            InsertQ(processQueue, rear, processes[currentTime]);
            currentTime++;
        }

        if (!isEmptyQ(front, rear)) {
            Process currentProcess = InsertFront(processQueue, front);
            DelQ(processQueue, front, rear);

            int executionTime = (quantumTime < currentProcess.Burst_Time) ? quantumTime : currentProcess.Burst_Time;
            currentProcess.Burst_Time -= executionTime;

            for (int i = currentTime; i < currentTime + executionTime; i++) {
                processes[i].Waiting_Time += executionTime;
            }

            currentTime += executionTime;

            if (currentProcess.Burst_Time > 0) {
                InsertQ(processQueue, rear, currentProcess);
            }
        }
        else {
            currentTime++;
        }
    }

    int totalWaiting = 0;
    for (int i = 0; i < SIZE; i++) {
        totalWaiting += processes[i].Waiting_Time;
    }

    double averageWaiting = static_cast<double>(totalWaiting) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: Round Robin\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].Waiting_Time << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaiting << " ms\n";
    std::cout << "\nResult Saved to Output.txt file\n";
}


void FCFS(Process* processes, int size) {
    bubbleSort(processes, size);

    int totalWaiting = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].Waiting_Time = processes[i - 1].Burst_Time + processes[i - 1].Arrival_Time + processes[i - 1].Waiting_Time - processes[i].Arrival_Time;
        totalWaiting += processes[i].Waiting_Time;
    }

    double averageWaiting = static_cast<double>(totalWaiting) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: First Come First Serve\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].Waiting_Time << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaiting << " ms\n";
    std::cout << "\nResult Saved to Output.txt file\n";
}

void SJF(Process* processes, int size) {
    bubbleSort(processes, size);

    int totalWaiting = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].Waiting_Time = processes[i - 1].Burst_Time + processes[i - 1].Arrival_Time + processes[i - 1].Waiting_Time;
        totalWaiting += processes[i].Waiting_Time;
    }

    double averageWaiting = static_cast<double>(totalWaiting) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: Shortest Job First\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].Waiting_Time << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaiting << " ms\n";
    std::cout << "\nResult Saved to Output.txt file\n";
}

void priorityScheduling(Process* processes, int size) {
    bubbleSort(processes, size);

    int totalWaiting = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].Waiting_Time = processes[i - 1].Burst_Time + processes[i - 1].Arrival_Time + processes[i - 1].Waiting_Time;
        totalWaiting += processes[i].Waiting_Time;
    }

    double averageWaiting = static_cast<double>(totalWaiting) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: priority Scheduling\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].Waiting_Time << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaiting << " ms\n";
    std::cout << "\nResult Saved to Output.txt file\n";
}
int main(int argc, char** argv) {
    Process processes[SIZE];

    int i = 0;
    int mode = 0;
    int option = 0;
    int option2 = 0;
    int quantumTime = 0;

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    while (inputFile >> processes[i].Burst_Time >> processes[i].Arrival_Time >> processes[i].priority) {
        processes[i].Name = i + 1;
        i++; 
    }

    inputFile.close();

    std::ofstream outputFile("output.txt", std::ios::trunc);

    std::cout << " CPU Scheduling Simulator\n";

    std::ifstream resultFile; 

    do {
        if (mode == 0)
            std::cout << "\nPRIMITIVE MODE\n\n";
        else if (mode == 1)
            std::cout << "\nNON-PRIMITIVE MODE\n\n";

        std::cout << "1. Select Scheduling Method\n";
        std::cout << "2. Enter Primitive Mode\n";
        std::cout << "3. Use Non-Primitive Mode\n";
        std::cout << "4. Display Result\n";
        std::cout << "5. Quit\n";
        std::cout << "\nEnter Option Here --> ";
        std::cin >> option;

        switch (option) {
        case 1:
            if (mode == 0)
                std::cout << "\n\n\nPRIMITIVE MODE\n\n";
            else if (mode == 1)
                std::cout << "\nNON-PRIMITIVE MODE\n\n";

            std::cout << "1. First Come First Serve Method\n";
            std::cout << "2. Shortest Job First Method\n";
            std::cout << "3. priority Scheduling\n";
            std::cout << "4. Round-Robin Scheduling\n";
            std::cout << "5. Back\n";
            std::cout << "\nEnter Option Here --> ";
            std::cin >> option2;


            switch (option2) {
            case 1:
                FCFS(processes, SIZE);
                break;
            case 2:
                SJF(processes, SIZE);
                break;
            case 3:
                priorityScheduling(processes, SIZE);
                break;
            case 4:
                std::cout << "\nEnter Quantum Time: ";
                std::cin >> quantumTime;
                RoundRobin(processes, quantumTime);
                break;
            case 5:
                break;
            default:
                std::cout << "\nInvalid Option Selected! Please Choose From 1 - 5\n";
                break;
            }
            break;
        case 2:
            mode = 0;
            break;
        case 3:
            mode = 1;
            break;
        case 4:
            resultFile.open("output.txt");
            std::cout << resultFile.rdbuf();
            resultFile.close();
            break;
        case 5:
            break;
        default:
            std::cout << "\nInvalid Option Selected! Please Choose From 1 - 5 \n";
            break;
        }
    } while (option != 5);

    return 0;
}


