#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool canScheduleWorker(int day, Worker_T worker, const AvailabilityMatrix& avail, const std::vector<int>& shifts, size_t maxShifts);
bool scheduleHelper(int day, int slot, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, std::vector<int>& shifts);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    int numDays = avail.size(); 
    int numWorkers= avail[0].size();
    std::vector<int> shifts(numWorkers, 0);
    
    sched = DailySchedule(numDays, std::vector<Worker_T>(dailyNeed));
    
    return scheduleHelper(0, 0, avail, dailyNeed, maxShifts, sched, shifts);
    
}

bool canScheduleWorker(int day, Worker_T worker, const AvailabilityMatrix& avail, const std::vector<int>& shifts, size_t maxShifts) {
    return avail[day][worker] && shifts[worker] < maxShifts;
}

bool scheduleHelper(int day, int slot, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, std::vector<int>& shifts) {
    int numDays = avail.size(); 
    int numWorkers = avail[0].size(); 
    
    if (day == numDays) { 
        return true;
    }
    
    if (slot == dailyNeed) { 
        return scheduleHelper(day + 1, 0, avail, dailyNeed, maxShifts, sched, shifts);
    }
    
    for (Worker_T worker = 0; worker < numWorkers; ++worker) {
        if (canScheduleWorker(day, worker, avail, shifts, maxShifts)) {
            sched[day][slot] = worker;
            shifts[worker]++;
            
            if (scheduleHelper(day, slot + 1, avail, dailyNeed, maxShifts, sched, shifts)) {
                return true;
            }
            shifts[worker]--;
        }
    }
    
    return false;
}


