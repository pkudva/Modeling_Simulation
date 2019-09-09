//
//  2_3.cpp
//  CIS545Proj1
//
//  Created by Priya Kudva on 1/21/18.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <random>


int main(int argc, const char * argv[]) {
    
    std::default_random_engine generator;
    
    std::uniform_int_distribution<> arrival(1, 100);
    
    int p1_occurrence = 0;
    int p2_occurrence = 0;
    int p3_occurrence = 0;
    int p4_occurrence = 0;
    
    int time_array[10000] = {};
    
    int sum = 0;
    float mean = 0.0;
    
    for(int i = 0; i < 10000; i++){
        int arrival_probability = arrival(generator); // random integer between 1 and 100
        if(arrival_probability >= 1 && arrival_probability <= 25){ //inter-arrival time of 1 minute
            p1_occurrence++;
            time_array[i] = 1;
            std::cout << 1 << "\n";
        }
        else if (arrival_probability >= 26 && arrival_probability <= 50){ //inter-arrival time of 2 minutes
            p2_occurrence++;
            time_array[i] = 2;
            std::cout << 2 << "\n";
        }
        else if (arrival_probability >= 51 && arrival_probability <= 75){ //inter-arrival time of 3 minutes
            p3_occurrence++;
            time_array[i] = 3;
            std::cout << 3 << "\n";
        }
        else{ //inter-arrival time of 4 minutes
            p4_occurrence++;
            time_array[i] = 4;
            std::cout << 4 << "\n";
        }
    }
    
    for(int j = 0; j < 10000; ++j){
        sum += time_array[j];
    }
    mean = ((float)sum) / 10000;
    
    std::cout << "1: " << p1_occurrence << ", 2: " << p2_occurrence << ", 3: " << p3_occurrence << ", 4: " << p4_occurrence << ", mean: " << mean << "\n";
    return 0;
}

