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
    int pMode; // Preemptive mode
    int n;     // time quantum for Round-Robin Scheduling
} alg = { 0, 0, 0 };

Process* initialHeader = nullptr;

string methods[5] = { "None", "First Come, First Served Scheduling", "Shortest-Job-First Scheduling", "Priority Scheduling", "Round-Robin Scheduling" };
string pModes[2] = { "OFF", "ON" };
string outputFilename;

// App function declarations
void validateParams(int, char**);
void getInitialProcesses(const string& filename);
void loadMainMenu();
void handleSchedulingMethod();
void handlePMode();
void handleShowResult();
void handleEndProgram();

// Linked list function declarations
struct Process* createProcess(int, int, int, int);
struct Process* insertFront(Process*, int, int, int, int);
struct Process* insertBack(Process*, int, int, int, int);
void deleteProcesses(Process**);
void sortProcesses(Process**, string);

int main(int argc, char** argv)
{
    validateParams(argc, argv);

    outputFilename = argv[4];

    getInitialProcesses(argv[2]);
    loadMainMenu();

    return 0;
}

// App templates
string mainMenuTemplate()
{
    string str = "CPU SCHEDULER SIMULATOR\n"
        "1) Scheduling Method (" +
        methods[alg.method] + (alg.method == 4 ? (" – time_quantum=" + to_string(alg.n)) : "") + ")\n"
        "2) Preemptive Mode (" +
        pModes[alg.pMode] + ")\n"
        "3) Show Result\n"
        "4) End Program\n\n";

    return str;
}

string programResultTemplate(Process* header, Algorithm a = alg)
{
    float sum = 0;
    int size = 0;
    float avWaitingTime;
    string mode = "";

    // Sort processes to show up in order
    sortProcesses(&header, "pid");

    if (a.method == 4)
    {
        mode = " - time_quantum=" + to_string(a.n);
    }
    else if (a.method == 2 || a.method == 3)
    {
        mode = a.pMode ? " - Preemptive" : " - Non Preemptive";
    }

    string str = "Scheduling Method: " + methods[a.method] + mode + "\n"
        "Process waiting times:\n";

    while (header != nullptr)
    {
        str += "P" + to_string(header->pid) + ": " + to_string(header->wt) + " ms\n";
        sum += header->wt;
        size++;

        header = header->next;
    }

    avWaitingTime = sum / size;

    str += "Average Waiting Time: " + to_string(avWaitingTime) + " ms\n\n";

    return str;
}