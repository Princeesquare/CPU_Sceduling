#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define SIZE 5
#define LINE_MAX 1024

struct Process {
    int Name;
    int bTime; // Burst Time
    int aTime; // Arrival Time
    int wTime; // Waiting Time
    int p;     // Priority
    int sr;    // Show Result
};

void enqueue(std::vector<Process>& queue, const Process& element) {
    queue.push_back(element);
}

void dequeue(std::vector<Process>& queue) {
    if (!queue.empty()) {
        queue.erase(queue.begin());
    }
}

Process front(const std::vector<Process>& queue) {
    return queue.front();
}

bool isEmpty(const std::vector<Process>& queue) {
    return queue.empty();
}

void RoundRobin(std::vector<Process>& processes, int quantumTime) {
    std::vector<Process> processQueue;
    int currentTime = 0;

    while (!isEmpty(processQueue) || currentTime < SIZE) {
        while (currentTime < SIZE && processes[currentTime].aTime <= currentTime) {
            enqueue(processQueue, processes[currentTime]);
            currentTime++;
        }

        if (!isEmpty(processQueue)) {
            Process currentProcess = front(processQueue);
            dequeue(processQueue);

            int executionTime = std::min(quantumTime, currentProcess.bTime);
            currentProcess.bTime -= executionTime;

            for (int i = currentTime; i < currentTime + executionTime; i++) {
                processes[i].wTime += executionTime;
            }

            currentTime += executionTime;

            if (currentProcess.bTime > 0) {
                enqueue(processQueue, currentProcess);
            }
        }
        else {
            currentTime++;
        }
    }
    int totalWaiting = 0;
    for (int i = 0; i < SIZE; i++) {
        totalWaiting += processes[i].wTime;
    }

    double averageWaiting = static_cast<double>(totalWaiting) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: Round Robin\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].wTime << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaiting << " ms\n";
    std::cout << "\nResult Saved to Output.txt file\n";
}


void FCFS(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.aTime < b.aTime;
        });

    int totalWaiting = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].wTime = processes[i - 1].bTime + processes[i - 1].aTime + processes[i - 1].wTime - processes[i].aTime;
        totalWaiting += processes[i].wTime;
    }

    double averageWaiting = static_cast<double>(totalWaiting) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: First Come First Serve\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].wTime << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaiting << " ms\n";
    std::cout << "\nResult Saved to Output.txt file\n";
}

void SJF(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.bTime < b.bTime;
        });

    int totalWaiting = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].wTime = processes[i - 1].bTime + processes[i - 1].aTime + processes[i - 1].wTime;
        totalWaiting += processes[i].wTime;
    }

    double averageWaiting = static_cast<double>(totalWaiting) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: Shortest Job First\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].wTime << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaiting << " ms\n";
    std::cout << "\nResult Saved to Output.txt file\n";
}

void PriorityScheduling(std::vector<Process> & processes) {
    std::sort(processes.begin(), processes.end(), [](const Process & a, const Process & b) {
        return a.p < b.p;
        });

    int totalWaiting = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].wTime = processes[i - 1].bTime + processes[i - 1].aTime + processes[i - 1].wTime;
        totalWaiting += processes[i].wTime;
    }

    double averageWaiting = static_cast<double>(totalWaiting) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: Priority Scheduling\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].wTime << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaiting << " ms\n";
    std::cout << "\nResult Saved to Output.txt file\n";
}
int main(int argc, char** argv) {
    std::vector<Process> processes(SIZE);

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

    while (inputFile >> processes[i].bTime >> processes[i].aTime >> processes[i].p) {
        processes[i].Name = i + 1;
        i++;
    }

    inputFile.close();

    std::ofstream outputFile("output.txt", std::ios::trunc);

    std::cout << " CPU Scheduler Simulator\n";

    std::ifstream resultFile; // Declare here

    do {
        if (mode == 0)
            std::cout << "\nMODE : Preemptive\n\n";
        else if (mode == 1)
            std::cout << "\nMODE : Non-Preemptive\n";

        std::cout << "1) Scheduling Method (None)\n";
        std::cout << "2) Preemptive Mode\n";
        std::cout << "3) Non-Preemptive Mode\n";
        std::cout << "4) Show Result\n";
        std::cout << "5) End Program\n";
        std::cout << "Option> ";
        std::cin >> option;

        switch (option) {
        case 1:
            if (mode == 0)
                std::cout << "\n\n\n\n MODE : Preemptive\n";
            else if (mode == 1)
                std::cout << "\nMODE : Non-Preemptive\n";

            std::cout << "1) First Come, First Served Scheduling\n";
            std::cout << "2) Shortest-Job-First Scheduling\n";
            std::cout << "3) Priority Scheduling\n";
            std::cout << "4) Round-Robin Scheduling\n";
            std::cout << "5) Back\n";
            std::cout << "\n\n";
            std::cout << "Option> ";
            std::cin >> option2;


            switch (option2) {
            case 1:
                FCFS(processes);
                break;
            case 2:
                SJF(processes);
                break;
            case 3:
                PriorityScheduling(processes);
                break;
            case 4:
                std::cout << "Enter Quantum Time: ";
                std::cin >> quantumTime;
                RoundRobin(processes, quantumTime);
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid Option! Please Choose From 1 - 5\n";
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
            std::cout << "\nInvalid Option! Please Choose From 1 - 5 \n";
            break;
        }
    } while (option != 5);

    return 0;
}


