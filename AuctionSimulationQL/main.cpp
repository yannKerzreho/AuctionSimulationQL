//
//  main.cpp
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 04/12/2023.
//

#include <iostream>

int main() {
    
    // Define possible_bet
    std::vector<double> possible_bet;
    double step = 0.05;
    for (double value = 0.05; value < 1.0; value += step) {
        possible_bet.push_back(value);
    }
    
    // Define parameters
    double alpha = 0.05;
    double beta = 0;
    double gamma = 0.99;
    double epsilon = 0.025;
    int num_it = 1000000;
    double auction_type = 1;  // 1=>FP & 2=>SP

    
    
    
}
