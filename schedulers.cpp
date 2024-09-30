#include "schedulers.h"

//Round Robin scheduler implementation. In general, this function maintains a double ended queue
//of processes that are candidates for scheduling (the ready variable) and always schedules
//the first process on that list, if available (i.e., if the list has members)
int RoundRobin(const int& curTime, const vector<Process>& procList, const int& timeQuantum)
{
    static int timeToNextSched = timeQuantum;  //keeps track of when we should actually schedule a new process
    static deque<int> ready;  //keeps track of the processes that are ready to be scheduled

    int idx = -1;

    // first look through the process list and find any processes that are newly ready and
    // add them to the back of the ready queue
    for(int i = 0, i_end = procList.size(); i < i_end; ++i)
    {
        if(procList[i].startTime == curTime)
        {
            ready.push_back(i);
        }
    }

    // now take a look the head of the ready queue, and update if needed
    // (i.e., if we are supposed to schedule now or the process is done)
    if(timeToNextSched == 0 || procList[ready[0]].isDone)
    {
        // the process at the start of the ready queue is being taken off of the
        // processor

        // if the process isn't done, add it to the back of the ready queue
        if(!procList[ready[0]].isDone)
        {
            ready.push_back(ready[0]);
        }

        // remove the process from the front of the ready queue and reset the time until
        // the next scheduling
        ready.pop_front();
        timeToNextSched = timeQuantum;
    }

    // if the ready queue has any processes on it
    if(ready.size() > 0)
    {
        // grab the front process and decrement the time to next scheduling
        idx = ready[0];
        --timeToNextSched;
    }
    // if the ready queue has no processes on it
    else
    {
        // send back an invalid process index and set the time to next scheduling
        // value so that we try again next time step
        idx = -1;
        timeToNextSched = 0;
    }

    // return back the index of the process to schedule next
    return idx;
}

//SPN 
//used this format for the other functions too (they were pretty similar)
int shortestProcessNext(const int& curTime, const vector<Process>& procList)
{
    int index = -1;
    //compare to a large number that will be greater than all of them 
    int minTime = 99999;
    //iterate through procList and find a process that is ready to start and has the shortest time needed to run and is not done
    for(int i = 0; i < procList.size(); i++){
        //i was stuck on this for a while couldnt figure out why it would change process mid running
        //I didnt have a case to check if there was a process running previously
        //this if statement checks to see if the process has ran before but isnt finished
        //therefore it must be running right now and also needs to finish
        if(procList[i].timeScheduled > 0 && procList[i].isDone == false){
            index = i;
            break;
        }
        if(procList[i].startTime <= curTime && procList[i].totalTimeNeeded < minTime && procList[i].isDone == false){
            index = i;
            //set new shortest process
            minTime = procList[i].totalTimeNeeded;
        }
    }
    return index;
}
//SRP
int shortestRemainingTime(const int& curTime, const vector<Process>& procList)
{
    int index = 0;
    //very similar to previous function
    int minTime = 99999;
    for(int i = 0; i < procList.size(); i++){
        //check to see if the time left for the process to finish is the shortest compared to the rest
        if(procList[i].startTime <= curTime && procList[i].totalTimeNeeded - procList[i].timeScheduled < minTime && procList[i].isDone == false){
            index = i;
            //set new shortest remaining time
            minTime = procList[i].totalTimeNeeded - procList[i].timeScheduled;
        }
    }
    return index;
}
//HRRN
int highestResponseRatio(const int& curTime, const vector<Process>& procList)
{
    int index = 0;
    float maxRatio = 0;
    for(int i = 0; i < procList.size(); i++){
        //check to find the highest response ratio in the list that is ready and not done
        if(procList[i].startTime <= curTime  && procList[i].isDone == false){
            //formula is wait time - time needed / time needed (casted to float to get exact value)
            float ratio = static_cast<float>((curTime - procList[i].startTime) + procList[i].totalTimeNeeded) / (procList[i].totalTimeNeeded);
            if(maxRatio < ratio){
                index = i;
                //set new largest response ratio to compare to
                maxRatio = ratio;
            }
        }
    }
    return index;
}