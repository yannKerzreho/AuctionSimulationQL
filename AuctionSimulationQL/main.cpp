//
//  main.cpp
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 04/12/2023.
//

#include <iostream>
#include "writeCSV.h"
#include "Function.h"


int main() {
    
    std::vector<double> possible_bet;
    double step = 0.05;
    for (double value = 0.05; value < 1.0; value += step) {
        possible_bet.push_back(value);
    }

    double alpha = 0.05;
    double beta = 0;
    double gamma = 0.99;
    double epsilon = 0.025;
    int num_iterations = 1000000;
    double pricer = 1;
    double opt = 10;
    
    std::vector<std::vector<double>> combinations = generateCombinations( alpha, beta, gamma, epsilon, opt, num_iterations, pricer);

        // Print the generated combinations
        for (const auto& combination : combinations) {
            for (const auto& value : combination) {
                std::cout << value << " ";
            }
            std::cout << "\n";
        }

        return 0;
}

