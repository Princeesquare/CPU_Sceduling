#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib> 

using namespace std;

struct Process
{
    int pid;
    int burstTime;
    int arrivalTime;
    int priority;
    int wt;  // Process waiting time
    int rbt; // Process remaining time
    struct Process* next;
    struct Process* prev;
};

struct Algorithm
{
    int method;
    int pModes; // Preemptive mode
    int n;     // time quantum for Round-Robin Scheduling
} alg = { 4, 2, 2 };

// App function declarations


// Linked list function declarations
struct Process* createProcess(int, int, int, int);
struct Process* insertFront(Process*, int, int, int, int);
struct Process* insertBack(Process*, int, int, int, int);
void deleteProcesses(Process**);
void sortProcesses(Process**, string);