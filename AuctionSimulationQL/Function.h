//
//  Function.h
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 04/12/2023.
//

#ifndef Function_h
#define Function_h

#include <stdio.h>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <fstream>

std::vector<std::vector<int>> simulation(double alpha, double beta, double gamma, double epsilon, double opt, int num_iterations, const std::vector<double>& possible_bet, double pricer);

std::vector<std::vector<int>> simulationStoch(double a, double p, double alpha, double beta, double gamma, double epsilon, double opt, int num_iterations, const std::vector<double>& possible_bet, double pricer);

std::vector<std::vector<int>> simulationStochE(int numE, double a, double p, double alpha, double beta, double gamma, double epsilon, double opt, int num_iterations, const std::vector<double>& possible_bet, double pricer);

std::vector<int> findConvergence(const std::vector<std::vector<int>> actions, const int numIt);

void writeCSV(const std::string& filePath, const std::vector<std::vector<int>>& data)

#endif /* Function_h */
