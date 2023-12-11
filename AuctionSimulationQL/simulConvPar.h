//
//  simulConvPar.h
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 11/12/2023.
//

#ifndef simulConvPar_h
#define simulConvPar_h

#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include "Function.h"


std::vector<std::vector<double>> processChunk(const std::vector<std::vector<double>>& combinations, const std::vector<double>& possible_bet, const int& num_it_param, const int& numConv, int start, int end);

std::vector<std::vector<double>> simulConvPar(const std::vector<double>& alpha, const std::vector<double>& beta, const std::vector<double>& gamma, const std::vector<double>& epsilon, const std::vector<double>& opt, const std::vector<double>& num_iterations, const std::vector<double>& possible_bet, const std::vector<double>& pricer, const int& num_it_param, const int& numConv);

#endif /* simulConvPar_h */
