

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool isValid(const AvailabilityMatrix& avail, Worker_T worker, const size_t maxShifts,
std::vector<std::vector<Worker_T> > dailySchedule,
unsigned int day, int shift_count[]
);

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    std::vector<std::vector<Worker_T> > dailySchedule, 
    unsigned int day, const size_t dailyNeed, int shift_count[],
    unsigned int spot, const size_t maxShifts);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail, //k
    const size_t dailyNeed, //d
    const size_t maxShifts, //m
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    std::vector<std::vector<Worker_T> > dailySchedule;

    //create schedule vector
    vector<Worker_T> empties;
    for(int i = 0; i< (int)avail.size(); ++i){
        dailySchedule.push_back(empties);
    }

    //create shift_count
    int size = avail[0].size();
    int shift_count[size];

    for(int i = 0; i<size; ++i){ //create shift_count vector
        shift_count[i] = 0;
    }
    //initialize vars 
    unsigned int day = 0;
    unsigned int spot = 0;
    
    //call helper function
    bool valid =  scheduleHelper(avail, dailySchedule,day++,
    dailyNeed, shift_count, spot, maxShifts);

    return valid;
}

bool isValid(const AvailabilityMatrix& avail, Worker_T worker, const size_t maxShifts,
std::vector<std::vector<Worker_T> > dailySchedule, 
unsigned int day, int shift_count[]
){
    if(avail[day][worker] != true && // check worker available
    shift_count[worker] > (int) maxShifts) //check if reach max shifts
    {
        return false;
    }
    //loop thru schedule
    for(int i = 0; i < (int) dailySchedule[day].size();i++) {
        if(dailySchedule[day][i] == worker){ 
            return false; 
        }
    }
    return true;
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    std::vector<std::vector<Worker_T> > dailySchedule, 
    unsigned int day, const size_t dailyNeed, int shift_count[],
    unsigned int spot, const size_t maxShifts
    ){

    if(day == avail.size()-1){ //if filled all spots, return
        return true;
    }

    for(int i = 0; i < (int) avail[0].size(); i++){ //loop thru workers

        if(isValid(avail,i,maxShifts, dailySchedule,day, shift_count)){ //if meet constraints 

            shift_count[i]++; //increase # of shifts 
            dailySchedule[day].push_back(i); //add worker 

            if(spot == dailyNeed){ //reach end of day 
                if(scheduleHelper(avail, dailySchedule,day++,
                dailyNeed, shift_count, spot, maxShifts)){ //recurse to next day
                    return true;
                }
                else{
                    //undo changes if not return true
                    day--;
                    shift_count[i]--;
                    dailySchedule[day].pop_back();
                }
            }
            else{
                if(scheduleHelper(avail, dailySchedule,day,
                dailyNeed, shift_count, spot++, maxShifts)){ //recurse next spot
                        return true;
                }
                  else{
                    //undo changes if not return true
                    shift_count[i]--;
                    dailySchedule[day].pop_back();
                }

            }
        }

    } //for loop
    return false;
}

