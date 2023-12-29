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
    std::cout << "\nResult Saved to Output.txt\n";
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
    outputFile << "\nScheduling Method: First Come First Served\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].wTime << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaiting << " ms\n";
    std::cout << "\nResult Saved to Output.txt\n";
}