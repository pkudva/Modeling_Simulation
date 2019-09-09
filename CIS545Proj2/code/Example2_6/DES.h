//
//  DES.h
//  Queueing Model
//  Discrete-event simulation starter code by A. Hornof & Y. Zhang- 2018
//  Modified by Priya Kudva - 2/6/18
//

#ifndef __Queueing_Model__DES__
#define __Queueing_Model__DES__

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <random>

// Only two event types
enum EventType {ARRIVAL, ABLEDEPART, BAKERDEPART};

typedef unsigned int Time;

struct Event {
    Time time;
    EventType type;
    
    // Order the events by time starting with the smallest time.
    // (Priority queues put bigger things at the front.)
    bool operator< (const Event& y) const {
        // Reverse the order so that an event with an earlier (smaller) time is bigger.
        return y.time < time;
    }
};


class DES {
public:
    void initialize();
    void run();
    
    // __ Students: Add your statistic variables here.
    int customers;
    int inter_arrival_time;
    int service_time;
    int wait_time;
    bool server1_busy;
    bool server2_busy;
    
    int total_waiting_customers;
    int total_wait_time;
    int total_idle_time;
    int total_Able_service_time;
    int total_Baker_service_time;
    int total_interarrival_time;
    
    
    double average_waiting_time;
    double queue_wait_probability;
    double idle_server_percent;
    double average_Able_service_time;
    double average_Baker_service_time;
    double average_interarrival;
    double average_wait_for_waiters;
    double average_time_in_system;
    
    double total_average_wait;
    double total_queue_wait;
    double total_idle_server;
    double total_average_able_service;
    double total_average_baker_service;
    double total_average_interarrival;
    double total_average_wait_for_waiters;
    double total_average_time_in_system;
    
private:
    
    // __ Students: You  need to implement the following methods.
    void arrive();
    void able_depart();
    void baker_depart();
    
    // Use std::uniform_int_distribution<> to generate random numbers.
    int generate_inter_arrival_time();
    int generate_Able_service_time();
    int generate_Baker_service_time();
    
    Time current_time = 0;
    
    // Seed the random number generator as follows.
    std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> generator =
    std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647>(410510);
    
    // Create an event queue with C++'s priority_queue data structure.
    // priority_queue is an abstract interface to provide a standardization of the methods for all priority_queues.
    // The abstract interface insures that methods (in this case such as pop(), push(), and empty()) will be implemented.
    // Behind the scenes, priority_queue is implemented as a heap.
    // This particularly priority queue uses a vector as a container for the elements.
    std::priority_queue<Event, std::vector<Event>> event_queue;
    std::priority_queue<Event, std::vector<Event>> wait_queue;
    
};

#endif /* defined(__Queueing_Model__DES__) */

