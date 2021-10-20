#ifndef EXECUTION_SPEED_H
#define EXECUTION_SPEED_H

#include <iostream>
#include <chrono>
using namespace std::chrono;


// Class For Calulating Execution
class ExecutionSpeed{

   high_resolution_clock::time_point start = high_resolution_clock::now();
   high_resolution_clock::time_point stop = high_resolution_clock::now();

    public:
    ExecutionSpeed(){
        start = stop = high_resolution_clock::now();
    }
    void start_now(){
        start = stop = high_resolution_clock::now();
    }
    void stop_now(){
        stop = high_resolution_clock::now();
    }
    long double get_difference(){
        auto duration = duration_cast<microseconds>(stop - start);
        return duration.count()/1000;
    }
}ExecutionCalculator;

#endif /* EXECUTION_SPEED_H */