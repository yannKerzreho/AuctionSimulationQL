//
//  Function.h
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 04/12/2023.
//

#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <fstream>

#ifndef Function_h
#define Function_h
#include <stdio.h>

std::vector<std::vector<int>> simulation(double alpha, double beta, double gamma, double epsilon, double opt, int num_iterations, const std::vector<double>& possible_bet, double pricer);

std::vector<int> findConvergence(const std::vector<std::vector<int>> actions, const int numIt);

std::vector<std::vector<double>> generateCombinations(const std::vector<double>& alpha, const std::vector<double>& beta, const std::vector<double>& gamma, const std::vector<double>& epsilon, const std::vector<double>& opt, const std::vector<int>& num_iterations, const std::vector<double>& pricer);

std::vector<std::vector<double>> simulConvergence(const std::vector<double> alpha, const std::vector<double> beta, const std::vector<double> gamma, const std::vector<double> epsilon, const std::vector<double> opt, const std::vector<int> num_iterations, const std::vector<double>& possible_bet, const std::vector<double> pricer, const int num_it_param, const int numConv);

std::vector<std::vector<int>> simulationStoch(double a, double p, double alpha, double beta, double gamma, double epsilon, double opt, int num_iterations, const std::vector<double>& possible_bet, double pricer);

std::vector<std::vector<int>> simulationStochE(int numE, double a, double p, double alpha, double beta, double gamma, double epsilon, double opt, int num_iterations, const std::vector<double>& possible_bet, double pricer);


#endif /* Function_h */
