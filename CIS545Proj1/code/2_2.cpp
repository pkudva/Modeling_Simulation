//
//  2_2.cpp
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
    
    std::uniform_int_distribution<> service(1, 100);
    
    int p1_occurrence = 0;
    int p2_occurrence = 0;
    int p3_occurrence = 0;
    
    int time_array[10000] = {};
    
    int sum = 0;
    float mean = 0.0;
    
    for(int i = 0; i < 10000; i++){
        int service_probability = service(generator);
        if(service_probability >= 1 && service_probability <= 30){ //service time of 3 minutes
            p1_occurrence++;
            time_array[i] = 3;
            std::cout << 3 << "\n";
        }
        else if (service_probability >= 31 && service_probability <= 75){ //service time of 6 minutes
            p2_occurrence++;
            time_array[i] = 6;
            std::cout << 6 << "\n";
        }
        else{ //service time of 10 minutes
            p3_occurrence++;
            time_array[i] = 10;
            std::cout << 10 << "\n";
        }
    }
    
    for(int j = 0; j < 10000; ++j){
        sum += time_array[j];
    }
    mean = ((float)sum) / 10000;
    
    std::cout << "3: " << p1_occurrence << ", 6: " << p2_occurrence << ", 10: " << p3_occurrence << ", mean: " << mean << "\n";
    return 0;
}
