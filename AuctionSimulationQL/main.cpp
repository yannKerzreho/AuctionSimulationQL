//
//  main.cpp
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 04/12/2023.
//

#include <iostream>
#include "writeCSV.h"
#include "Function.h"
#include "simulConvPar.h"
#include <chrono>


int main() {
    
    std::vector<double> possible_bet;
    double step = 0.05;
    for (double value = 0.05; value < 1.0; value += step) {
        possible_bet.push_back(value);
    }

    std::vector<double> alpha = {0.05, 0.1};
    std::vector<double> beta = {0.01, 0.001};
    std::vector<double> gamma = {0.99, 0.95};
    std::vector<double> epsilon = {0.25};
    std::vector<double> opt = {10};
    std::vector<double> num_iterations = {200000};
    std::vector<double> pricer = {1, 2};
    int num_it_param = 10;
    int numConv = 10000;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::vector<double>> conv = simulConvPar(alpha, beta, gamma, epsilon, opt, num_iterations, possible_bet, pricer, num_it_param, numConv);
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Elapsed time 1: " << duration.count() << " milliseconds" << std::endl;
    
    std::vector<double> conv1 = findCol(conv, 0);
    std::vector<double> conv2 = findCol(conv, 1);
    std::vector<double> alphas  = findCol(conv, 2);
    std::vector<double> betas  = findCol(conv, 3);
    std::vector<double> gammas  = findCol(conv, 4);
    std::vector<double> pricers  = findCol(conv, 8);


    writeCSV("/Users/yannkerzreho/Documents/AC/sim_convergence.csv", conv1, conv2, alphas, betas, gammas, pricers);
    
    return 0;
}



