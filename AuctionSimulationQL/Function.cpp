//
//  Function.c
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 04/12/2023.
//

#include "Function.h"
#include "Qalgo.h"

#include <random>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>

std::vector<std::vector<int>> simulation(double& alpha, double& beta, double& gamma, double& epsilon, double opt, int num_iterations, const std::vector<double>& possible_bet, double& pricer){
    
    int num_actions = possible_bet.size();

    Qalgo A(1, num_actions, alpha, beta, gamma, epsilon, opt);
    Qalgo B(1, num_actions, alpha, beta, gamma, epsilon, opt);

    int current_state_A = 0;
    int current_state_B = 0;
    
    std::vector<std::vector<int>> actions;

    for (int t = 0; t < num_iterations; t++) {
        bool A_greed = A.is_greedy(t);
        bool B_greed = B.is_greedy(t);

        int a_A = A.choose_action(current_state_A, A_greed);
        int a_B = B.choose_action(current_state_B, B_greed);

        std::vector<int> action_pair = {A.choose_action(current_state_A, false), B.choose_action(current_state_B, false)};
        actions.push_back(action_pair);

        std::vector<int> bets = {a_A, a_B};
        std::vector<double> rewards(2, 0.0);

        double price;

        if (a_A == a_B) {
            price = possible_bet[static_cast<int>(a_B)];
            rewards[0] = (1.0 - price) / 2;
            rewards[1] = (1.0 - price) / 2;
        }

        if (a_A > a_B) {
            price = (2.0 - pricer) * possible_bet[a_A] + (pricer - 1.0) * possible_bet[a_B];
            rewards[0] = (1.0 - price);
        }

        if (a_B > a_A) {
            price = (2.0 - pricer) * possible_bet[a_B] + (pricer - 1.0) * possible_bet[a_A];
            rewards[1] = (1.0 - price);
        }

        A.update_q(current_state_A, a_A, rewards[0], 0);
        B.update_q(current_state_B, a_B, rewards[1], 0);
    }
    return actions;
}

std::vector<int> findConvergence(const std::vector<std::vector<int>>& actions, const int& numIt){
    
    unsigned long numActions = actions.size(); // Nombre de colonnes d'actions
    
    bool isConstant = true;
    int constantValue0 = actions[numActions - 1][0]; // Valeur constante présumée
    int constantValue1 = actions[numActions - 1][1]; // Valeur constante présumée
    
    for (unsigned long i = numActions - 2; i >= numActions - numIt; i--) {
        if (actions[i][0] != constantValue0 || actions[i][1] != constantValue1) {
            isConstant = false;
            break; // La valeur n'est plus constante, inutile de continuer
        }
    }
    
    if (isConstant) {
        std::vector<int> result = {constantValue0, constantValue1};
        return result;
        }
        // Si aucune colonne n'a été trouvée avec des valeurs constantes
        return {std::vector<int> {-100, -100}};
}


std::vector<std::vector<double>> generateCombinations(const std::vector<double>& alpha, const std::vector<double>& beta, const std::vector<double>& gamma, const std::vector<double>& epsilon, const std::vector<double>& opt, const std::vector<int>& num_iterations, const std::vector<double>& pricer) {
    
    std::vector<std::vector<double>> combinations;

    for (const auto& a : alpha) {
        for (const auto& b : beta) {
            for (const auto& g : gamma) {
                for (const auto& e : epsilon) {
                    for (const auto& o : opt) {
                        for (const auto& n : num_iterations) {
                            for (const auto& p : pricer) {
                                combinations.push_back({a, b, g, e, o, static_cast<double>(n), p});
                            }
                        }
                    }
                }
            }
        }
    }

    return combinations;
}

std::vector<std::vector<double>> simulConvergence(const std::vector<double>& alpha, const std::vector<double>& beta, const std::vector<double>& gamma, const std::vector<double>& epsilon, const std::vector<double>& opt, const std::vector<int>& num_iterations, const std::vector<double>& possible_bet, const std::vector<double>& pricer, const int& num_it_param, const int& numConv){
    
    std::vector<std::vector<double>> results;
 
    std::vector<std::vector<double>> combinations = generateCombinations(alpha, beta, gamma, epsilon, opt, num_iterations, pricer);
    
    for (int i = 0; i < combinations.size(); i++) {
        
        std::cout << "alpha : " << combinations[i][0] << " | beta : " << combinations[i][1] << " | gamma : " << combinations[i][2] << " | epsilon : " << combinations[i][3] << " | opt : " << combinations[i][4] << " | num_iterations : " << combinations[i][5] << " | pricer : " << combinations[i][6] << std::endl;

        for (int it = 0; it < num_it_param; it++) {
           
            std::vector<std::vector<int>> sim = simulation(combinations[i][0], combinations[i][1], combinations[i][2], combinations[i][3], static_cast<int>(combinations[i][4]), combinations[i][5], possible_bet, combinations[i][6]);
                        
            std::vector<int> conv = findConvergence(sim, numConv);
            
            std::vector<double> res = {static_cast<double>(conv[0]), static_cast<double>(conv[1]), combinations[i][0], combinations[i][1], combinations[i][2], combinations[i][3], combinations[i][4], combinations[i][5], combinations[i][6]};
            
            results.push_back(res);
        }
    }
    return results;
}

// Additional variation

std::vector<std::vector<int>> simulationStoch(double a, double p, double alpha, double beta, double gamma, double epsilon, double opt, int num_iterations, const std::vector<double>& possible_bet, double pricer) {
    
    int num_actions = possible_bet.size();

    Qalgo A(1, num_actions, alpha, beta, gamma, epsilon, opt);
    Qalgo B(1, num_actions, alpha, beta, gamma, epsilon, opt);

    int current_state_A = 0;
    int current_state_B = 0;
    
    std::vector<std::vector<int>> actions;
    
    for (int t = 0; t < num_iterations; t++) {
        bool A_greed = A.is_greedy(t);
        bool B_greed = B.is_greedy(t);

        int a_A = A.choose_action(current_state_A, A_greed);
        int a_B = B.choose_action(current_state_B, B_greed);

        std::vector<int> action_pair = {A.choose_action(current_state_A, false), B.choose_action(current_state_B, false)};
        actions.push_back(action_pair);

        std::vector<int> bets = {a_A, a_B};
        std::vector<double> rewards(2, 0.0);

        double price;
        double current_value = 1;
        
        if(rand() / RAND_MAX < p) {
            current_value = a;
        }
        
        if (a_A == a_B) {
            price = possible_bet[static_cast<int>(a_B)];
            rewards[0] = (current_value - price) / 2;
            rewards[1] = (current_value - price) / 2;
        }

        if (a_A > a_B) {
            price = (2.0 - pricer) * possible_bet[a_A] + (pricer - 1.0) * possible_bet[a_B];
            rewards[0] = (current_value - price);
        }

        if (a_B > a_A) {
            price = (2.0 - pricer) * possible_bet[a_B] + (pricer - 1.0) * possible_bet[a_A];
            rewards[1] = (current_value - price);
        }

        A.update_q(current_state_A, a_A, rewards[0], 0);
        B.update_q(current_state_B, a_B, rewards[1], 0);
    }
    return actions;
}

std::vector<std::vector<int>> simulationStochE(int numE, double a, double p, double alpha, double beta, double gamma, double epsilon, double opt, int num_iterations, const std::vector<double>& possible_bet, double pricer){
    
    int num_actions = possible_bet.size();
    
    Qalgo A(1, num_actions, alpha, beta, gamma, epsilon, opt); // Initialize A with appropriate constructor
    Qalgo B(1, num_actions, alpha, beta, gamma, epsilon, opt); // Initialize B with appropriate constructor
    
    if (numE == 1) {
        A = Qalgo(2, num_actions, alpha, beta, gamma, epsilon*2, opt); // Reinitialize A with the 2-state constructor
    }
    
    if (numE == 2) {
        A = Qalgo(2, num_actions, alpha, beta, gamma, epsilon*2, opt); // Reinitialize A with the 2-state constructor
        B = Qalgo(2, num_actions, alpha, beta, gamma, epsilon*2, opt); // Initialize B with the 2-state constructor
    }
    
    std::vector<std::vector<int>> actions;
    
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    
    for (int t = 0; t < num_iterations; t++) {
        bool A_greed = A.is_greedy(t);
        bool B_greed = B.is_greedy(t);
        
        int state = 0;
        if (distribution(generator) < p) {
            state = 1;
        }
        
        int a_A = 0;
        int a_B = 0;
        
        if (numE == 0) {
            a_A = A.choose_action(0, A_greed);
            a_B = B.choose_action(0, B_greed);
            std::vector<int> action_pair = {A.choose_action(0, false), B.choose_action(0, false), state};
            actions.push_back(action_pair);
        }

        if (numE == 1) {
            a_A = A.choose_action(state, A_greed);
            a_B = B.choose_action(0, B_greed);
            std::vector<int> action_pair = {A.choose_action(state, false), B.choose_action(0, false), state};
            actions.push_back(action_pair);
        }
        
        if (numE == 2) {
            a_A = A.choose_action(state, A_greed);
            a_B = B.choose_action(state, B_greed);
            std::vector<int> action_pair = {A.choose_action(state, false), B.choose_action(state, false), state};
            actions.push_back(action_pair);
        }

        std::vector<int> bets = {a_A, a_B};
        std::vector<double> rewards(2, 0.0);

        double price;
        double current_value = 1;
        if(state == 1) {
            current_value = a;
        }
        
        if (a_A == a_B) {
            price = possible_bet[static_cast<int>(a_B)];
            rewards[0] = (current_value - price) / 2;
            rewards[1] = (current_value - price) / 2;
        }

        if (a_A > a_B) {
            price = (2.0 - pricer) * possible_bet[a_A] + (pricer - 1.0) * possible_bet[a_B];
            rewards[0] = (current_value - price);
        }

        if (a_B > a_A) {
            price = (2.0 - pricer) * possible_bet[a_B] + (pricer - 1.0) * possible_bet[a_A];
            rewards[1] = (current_value - price);
        }
            // uptade Qmatrix with the assumtoin next state = current state
        if (numE == 0) {
            A.update_q(0, a_A, rewards[0], 0);
            B.update_q(0, a_B, rewards[1], 0);
        }

        if (numE == 1) {
            A.update_q(state, a_A, rewards[0], state);
            B.update_q(0, a_B, rewards[1], 0);
        }
        
        if (numE == 2) {
            A.update_q(state, a_A, rewards[0], state);
            B.update_q(state, a_B, rewards[1], state);
        }
        
    }
    return actions;
}
