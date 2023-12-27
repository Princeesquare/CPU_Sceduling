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
