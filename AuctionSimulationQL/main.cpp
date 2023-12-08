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

    std::vector<double> alpha = {0.05, 0.1};
    std::vector<double> beta = {0.001};
    std::vector<double> gamma = {0.99, 0.95};
    std::vector<double> epsilon = {0.25};
    std::vector<double> opt = {10};
    std::vector<int> num_iterations = {1000000};
    std::vector<double> pricer = {1};
    int num_it_param = 10;
    int numConv = 10000;
    
    std::vector<std::vector<double>> conv = simulConvergence(alpha, beta, gamma, epsilon, opt, num_iterations, possible_bet, pricer, num_it_param, numConv);
    
    
    std::vector<double> conv1 = findCol(conv, 0);
    std::vector<double> conv2 = findCol(conv, 1);
    std::vector<double> alphas  = findCol(conv, 2);
    std::vector<double> gammas  = findCol(conv, 4);
    
    writeCSV("/Users/yannkerzreho/Documents/AC/sim_convergence.csv", conv1, conv2, alphas, gammas);
    
    return 0;
}



