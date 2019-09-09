//
//  p4.cpp
//  CIS545Proj3
//
//  Created by Priya Kudva on 2/22/18.
//  Copyright © 2018 University of Oregon. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, const char * argv[]) {
    std::ifstream file;
    file.open("data.txt"); //open the file with the data values
    
    double x; //input from the file
    double sum = 0.0; //sum of all chi-values
    double expected = 5.0; //the expected frequency of a normal distribution
    double chi_square_critical_value = 66.3387; //test against calculated chi-squared value
    
    //create the bins to keep track of frequency
    double group1 = 0.0;
    double group2 = 0.0;
    double group3 = 0.0;
    double group4 = 0.0;
    double group5 = 0.0;
    double group6 = 0.0;
    double group7 = 0.0;
    double group8 = 0.0;
    double group9 = 0.0;
    double group10 = 0.0;

    
    while(file >> x){ //count the frequency of the data into the 10 bins
        if(x <= 77.07){ //bin 1 = all values <= 77.07
            group1++;
        }
        else if(x > 77.07 && x <= 82.14){ //bin 2 = all values between 77.07 and 82.14
            group2++;
        }
        else if(x > 82.14 && x <= 87.21){ //bin 3 = all values between 82.14 and 87.21
            group3++;
        }
        else if(x > 87.21 && x <= 92.28){ //bin 4 = all values between 87.21 and 92.28
            group4++;
        }
        else if(x > 92.28 && x <= 97.35){ //bin 5 = all values between 92.28 and 97.35
            group5++;
        }
        else if(x > 97.35 && x <= 102.42){ //bin 6 = all values between 97.35 and 102.42
            group6++;
        }
        else if(x > 102.42 && x <= 107.49){ //bin 7 = all values between 102.42 and 107.49
            group7++;
        }
        else if(x > 107.49 && x <= 112.56){ //bin 8 = all values between 107.49 and 112.56
            group8++;
        }
        else if(x > 112.56 && x <= 117.63){ //bin 9 = all values between 112.56 and 117.63
            group9++;
        }
        else { //bin 10 = all values >= 117.63
            group10++;
        }
    }
    
    //calculate the difference between the observed frequencies and the expected
    double diff1 = group1 - expected;
    double diff2 = group2 - expected;
    double diff3 = group3 - expected;
    double diff4 = group4 - expected;
    double diff5 = group5 - expected;
    double diff6 = group6 - expected;
    double diff7 = group7 - expected;
    double diff8 = group8 - expected;
    double diff9 = group9 - expected;
    double diff10 = group10 - expected;
    
    //square the differences and divide by the expected frequency
    double chi1 = ((diff1 * diff1)/expected);
    double chi2 = ((diff2 * diff2)/expected);
    double chi3 = ((diff3 * diff3)/expected);
    double chi4 = ((diff4 * diff4)/expected);
    double chi5 = ((diff5 * diff5)/expected);
    double chi6 = ((diff6 * diff6)/expected);
    double chi7 = ((diff7 * diff7)/expected);
    double chi8 = ((diff8 * diff8)/expected);
    double chi9 = ((diff9 * diff9)/expected);
    double chi10 = ((diff10 * diff10)/expected);
    
    //add the chi-squared values together
    sum = chi1 + chi2 + chi3 + chi4 + chi5 + chi6 + chi7 + chi8 + chi9 + chi10;

    //output chi-squared value
    std::cout << std::fixed;
    std::cout << "Chi-squared value: " << std::setprecision(3) << sum << std::endl;
    
    if(sum <= chi_square_critical_value){
        std::cout << "Hypothesis proved. This data follows a normal distribution." << std::endl;
    }
    else{
        std::cout << "Hypothesis disproved. This data does not follow a normal distribution." << std::endl;
    }
    
    return 0;
}

