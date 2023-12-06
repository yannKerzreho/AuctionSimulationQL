//
//  Qalgo.h
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 04/12/2023.
//

#include <random>
#include <cmath>
#include <iostream>
#include <vector>

#ifndef Qalgo_h
#define Qalgo_h
#include <stdio.h>

class Qalgo {
    private:
    
    int num_states;
    int num_actions;
    double alpha;
    double beta;
    double gamma;
    double epsilon;
    std::vector<std::vector<double>> Q;
    
    public:
    // Builder
    Qalgo(int num_states, int num_actions, double alpha, double beta, double gamma, double epsilon, double opt);

    // Methods
    void update_q(int state, int action, double reward, int next_state);
    bool is_greedy(int t);
    int choose_action(int state, bool isgreedy);
    
};

#endif /* Qalgo_h */
