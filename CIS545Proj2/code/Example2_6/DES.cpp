//
//  DES.cpp
//  Queueing Model
//  Discrete-event simulation starter code by A. Hornof & Y. Zhang - 2018
//  Modified by Priya Kudva - 2/6/18
//

#include "DES.h"
#include <queue>
#include <random>
#include <iostream>

void DES::initialize() {
    current_time = 0;
    
    // __ Students: Initialize any variables you created.
    customers = 0;
    server1_busy = false;
    server2_busy = false;
    wait_time = 0;
    service_time = 0;
    inter_arrival_time = 0;
    
    total_wait_time = 0;
    total_waiting_customers = 0;
    total_idle_time = 0;
    total_Able_service_time = 0;
    total_Baker_service_time = 0;
    total_interarrival_time = 0;
    
    average_waiting_time = 0.0;
    queue_wait_probability = 0.0;
    idle_server_percent = 0.0;
    average_Able_service_time = 0.0;
    average_Baker_service_time = 0.0;
    average_interarrival = 0.0;
    average_wait_for_waiters = 0.0;
    average_time_in_system = 0.0;
    
    // Empty the queue to remove events unprocessed from the last simulation.
    while(!event_queue.empty()) {
        event_queue.pop();
    }
    while(!wait_queue.empty()) {
        wait_queue.pop();
    }
    
    // __ Students: Schedule the first arrival here.
    Event e;
    e.type = ARRIVAL;
    e.time = current_time;
    customers++;
    event_queue.push(e);
    
};

void DES::run() {
    // The event loop, run until all the events are processed
    while (!event_queue.empty() && customers < 100) {
        Event e = event_queue.top();
        event_queue.pop();
        
        if(e.type == ARRIVAL && server1_busy == true && server2_busy == true){
            total_waiting_customers++;
            wait_queue.push(e);
        }
        else if(e.type == ARRIVAL && server1_busy == false && server2_busy == false){
            total_idle_time += (e.time - current_time);
        }
        
        // set the current time to the event time
        current_time = e.time;
        
        switch (e.type) {
            case ARRIVAL:
                arrive();
                break;
            case ABLEDEPART:
                able_depart();
                break;
            case BAKERDEPART:
                baker_depart();
                break;
            default:
                break;
        }
    }
    average_waiting_time = ((double)total_wait_time) / 100;
    queue_wait_probability = ((double)total_waiting_customers) / 100;
    idle_server_percent = ((double)total_idle_time) / ((double)current_time);
    average_Able_service_time = ((double)total_Able_service_time) / 100;
    average_Baker_service_time = ((double)total_Baker_service_time) / 100;
    average_interarrival = ((double)total_interarrival_time) / 99;
    if(total_waiting_customers == 0){
        average_wait_for_waiters = 0;
    }
    else{
    average_wait_for_waiters = ((double)total_wait_time) / ((double)total_waiting_customers);
    }
    average_time_in_system = ((double)average_waiting_time + (double)average_Able_service_time +  (double)average_Baker_service_time);
    
    total_average_wait += average_waiting_time;
    total_queue_wait += queue_wait_probability;
    total_idle_server += idle_server_percent;
    total_average_able_service += average_Able_service_time;
    total_average_baker_service += average_Baker_service_time;
    total_average_interarrival += average_interarrival;
    total_average_wait_for_waiters += average_wait_for_waiters;
    total_average_time_in_system += average_time_in_system;
    
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);
    
    std::cout << average_waiting_time << ", " << queue_wait_probability << ", " << idle_server_percent << ", " << average_Able_service_time << ", " << average_Baker_service_time << ", " << average_interarrival << ", " << average_wait_for_waiters << ", " << average_time_in_system << "\n";
    
}

// To create an event and schedule the event for arrive() and depart(), do the following:
// Event e;
// e.type = THE EVENT TYPE YOU WANT;
// e.time = THE EVENT TIME YOU WANT;
// event_queue.push(e); //put the event in the priority queue, and it will be automatically sorted based on time.

void DES::arrive() {
    customers++;
    if (server1_busy == false && server2_busy == false){ //Able gets the customer
        server1_busy = true;
        Event e1;
        service_time = generate_Able_service_time();
        total_Able_service_time += service_time;
        e1.type = ABLEDEPART;
        e1.time = current_time + service_time;
        event_queue.push(e1);
    }
    else if(server1_busy == true){
        if(server2_busy == false){ //Baker gets the customer
            server2_busy = true;
            Event e1;
            service_time = generate_Baker_service_time();
            total_Baker_service_time += service_time;
            e1.type = BAKERDEPART;
            e1.time = current_time + service_time;
            event_queue.push(e1);
        }
    }
    
    Event e2;
    inter_arrival_time = generate_inter_arrival_time();
    total_interarrival_time += inter_arrival_time;
    e2.type = ARRIVAL;
    e2.time = current_time + inter_arrival_time;
    event_queue.push(e2);
    
}

void DES::able_depart(){
    server1_busy = false;
    if(!wait_queue.empty()){
        customers--;
        Event e = wait_queue.top();
        wait_queue.pop();
        wait_time = current_time - e.time;
        total_wait_time += wait_time;
        e.time = current_time;
        event_queue.push(e);
    }
}

void DES::baker_depart(){
    server2_busy = false;
    if(!wait_queue.empty()){
        customers--;
        Event e = wait_queue.top();
        wait_queue.pop();
        wait_time = current_time - e.time;
        total_wait_time += wait_time;
        e.time = current_time;
        event_queue.push(e);
    }
}

int DES::generate_inter_arrival_time(){
    std::uniform_int_distribution<> inter_arrival_time(1, 100);
    int probability = inter_arrival_time(generator);
    if(probability <= 20){
        return 1;
    }
    else if(probability > 20 && probability <= 45){
        return 2;
    }
    else if(probability > 45 && probability <= 80){
        return 3;
    }
    else{
        return 4;
    }
}

int DES::generate_Able_service_time(){
    std::uniform_int_distribution<> service_time(1, 100);
    int temp_probability = service_time(generator);
    if(temp_probability <= 30){
        return 2;
    }
    else if(temp_probability > 30 && temp_probability <= 58){
        return 3;
    }
    else if(temp_probability > 58 && temp_probability <= 83){
        return 4;
    }
    else{
        return 5;
    }
}

int DES::generate_Baker_service_time(){
    std::uniform_int_distribution<> service_time(1, 100);
    int temp_probability = service_time(generator);
    if(temp_probability <= 35){
        return 3;
    }
    else if(temp_probability > 35 && temp_probability <= 60){
        return 4;
    }
    else if(temp_probability > 60 && temp_probability <= 80){
        return 5;
    }
    else{
        return 6;
    }
}
