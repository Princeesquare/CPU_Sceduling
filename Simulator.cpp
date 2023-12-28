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