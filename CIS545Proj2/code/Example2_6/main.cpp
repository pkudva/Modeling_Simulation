//
//  main.cpp
//  Queueing Mode
//  Discrete-event simulation starter code by A. Hornof & Y. Zhang - 2018
//  Modified by Priya Kudva - 2/6/18
//

#include "DES.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    DES sim;
    const int num_trials = 1000;
    
    for (int i = 0; i < num_trials; i++) {
        sim.initialize();
        std::cout << i+1 << ", ";
        sim.run();
    }
    std::cout << "Overall average, " << sim.total_average_wait/1000 << ", " << sim.total_queue_wait/1000 << ", " << sim.total_idle_server/1000 << ", " << sim.total_average_able_service/1000 << ", " << sim.total_average_baker_service/1000 << ", " << sim.total_average_interarrival/1000 << ", " << sim.total_average_wait_for_waiters/1000 << ", " << sim.total_average_time_in_system/1000 << "\n";
    
    return 0;
}
