//
//  2_4.cpp
//  CIS545Proj1
//
//  Created by Priya Kudva on 1/22/18.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <random>

int main(int argc, const char * argv[]) {
    std::default_random_engine generator;
    std::uniform_int_distribution<> coin(1,2);
    
    int zero_to_ten = 0;
    int fortyfive_to_fiftyfive = 0;
    int ninety_to_hundred = 0;
    
    for(int trial = 1; trial <= 1000; trial++){
        
        int harry_money = 0;
        int tom_money = 0;
        int harry_win = 0;
        
        for(int i = 0; i < 100; i++){
            int coin_toss = coin(generator);
            if(coin_toss == 1){ // 1 for heads, Harry should gain $1 and Tom should lose $1
                harry_money++;
                tom_money--;
            }
            if(coin_toss == 2){ // 2 for tails, Harry should lose $1 and Tom should gain $1
                harry_money--;
                tom_money++;
            }
            if(harry_money > tom_money){
                harry_win++;
            }
        }
        if(harry_win >=0 && harry_win <=10){
            zero_to_ten++;
        }
        else if(harry_win >= 45 && harry_win <= 55){
            fortyfive_to_fiftyfive++;
        }
        else if(harry_win >=90 && harry_win <= 100){
            ninety_to_hundred++;
        }
        std::cout << "Trial #" << trial;
        std::cout << " Harry had more money than Tom " << harry_win << " times.\n";
    }
    std::cout << "0-10: " << zero_to_ten << " 45-55: " << fortyfive_to_fiftyfive << " 90-100: " << ninety_to_hundred << "\n";
}
