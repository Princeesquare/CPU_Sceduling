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
} alg = { 0, 0, 0 };