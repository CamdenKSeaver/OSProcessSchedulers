#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include<vector>  //process vector
#include<deque>   //for ready double ended queue
#include<fstream>  // file i/o
#include<iostream> // cerr

using namespace std;

struct Process
{
    Process() : id("notSet"), startTime(-1), totalTimeNeeded(-1), isDone(false), timeScheduled(0), timeFinished(-1), turnaroundTime(0), normalizedTurnaroundTime(0) {}

    // Given data
    string id;            //The process id
    int startTime;        //The time at which the process becomes available for scheduling
    int totalTimeNeeded;  //The total amount of time needed by the process

    // Process details
    bool isDone;          //Indicates if the process is complete
    int timeScheduled;    //The amount of time the process has been scheduled so far
    int timeFinished;     //The time that the process completed

	// Stats
	float turnaroundTime;
	float normalizedTurnaroundTime;
};


inline void readInProcList(const string& fname, vector<Process>& procList)
{
    ifstream in(fname.c_str());
    int numProcs;

    if(in.fail())
    {
        cerr << "Unable to open file \"" << fname << "\", terminating" << endl;
        exit(-1);
    }

    in >> numProcs;
    procList.resize(numProcs);
    for(auto& p:procList)
    {
        in >> p.id >> p.startTime >> p.totalTimeNeeded;
    }
    in.close();
}


int RoundRobin(const int& curTime, const vector<Process>& procList, const int& timeQuantum);
int shortestProcessNext(const int& curTime, const vector<Process>& procList);
int shortestRemainingTime(const int& curTime, const vector<Process>& procList);
int highestResponseRatio(const int& curTime, const vector<Process>& procList);

#endif