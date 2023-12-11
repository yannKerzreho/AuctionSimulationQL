//
//  Qalgo.c
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 04/12/2023.
//

#include "Qalgo.h"

#include <vector>
#include <random>
#include <cmath>
#include <iostream>

Qalgo::Qalgo(int num_states, int num_actions, double alpha, double beta, double gamma, double epsilon, double opt)
    : num_states(num_states), num_actions(num_actions), alpha(alpha), beta(beta), gamma(gamma), epsilon(epsilon) {
    Q = std::vector<std::vector<double>>(num_states, std::vector<double>(num_actions));
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution<double> distribution(opt, opt / 100.0);
    for (int state = 0; state < num_states; state++) {
        for (int action = 0; action < num_actions; action++) {
            Q[state][action] = distribution(generator);
        }
    }
}

void Qalgo::update_q(int state, int action, double reward, int next_state) {
    double current_q = Q[state][action];
    double max_future_q = 0.0;

    if (next_state >= 0 && next_state < num_states) {
        max_future_q = *std::max_element(Q[next_state].begin(), Q[next_state].end());
    }

    double new_q = (1.0 - alpha) * current_q + alpha * (reward + gamma * max_future_q);
    Q[state][action] = new_q;
}

bool Qalgo::is_greedy(int t) {
    double eps = epsilon * std::exp(-beta * t);
    return (static_cast<double>(rand()) / RAND_MAX > eps);
}

int Qalgo::choose_action(int state, bool isgreedy) {
    if (isgreedy) {
        return rand() % num_actions;
    } else {
        int best_action = 0;
        for (int action = 1; action < num_actions; action++) {
            if (Q[state][action] > Q[state][best_action]) {
                best_action = action;
            }
        }
        return best_action;
    }
}
