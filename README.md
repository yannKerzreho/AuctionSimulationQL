# AuctionSimulationQL

This repository contains a C++ implementation of a simulation framework for auction scenarios using Q-learning. The simulation is designed to model interactions between two agents engaged in auctions over multiple iterations.

## Contents

- **simulation**: The main simulation function (`simulation`) that models the auction process, taking various parameters like alpha, beta, gamma, epsilon, opt, num_iterations, possible_bet, and pricer.

- **findConvergence**: A utility function (`findConvergence`) that analyzes the convergence of auction actions over a specified number of iterations.

- **simulationStoch** and **simulationStochE**: Extensions of the main simulation with stochastic elements, introducing randomness into the agent's decisions.

- **generateCombinations**: A function (`generateCombinations`) that generates combinations of parameters for simulations.

- **simulConvergence**: The core function (`simulConvergence`) orchestrating multiple simulations with varying parameter combinations and collecting convergence results.

- **main**: An example `main` function demonstrating how to use the simulation framework with predefined parameter sets.

## Usage

To use the simulation framework, include the necessary headers (`Function.h` and others) in your C++ project. Define your parameters, such as alpha, beta, gamma, epsilon, opt, num_iterations, possible_bet, pricer, num_it_param, and numConv. Then call the `simulConvergence` function to run simulations and collect convergence results.

### Example

```cpp
// Example parameters
std::vector<double> alpha = {0.05, 0.1};
std::vector<double> beta = {0.001};
std::vector<double> gamma = {0.99, 0.95};
std::vector<double> epsilon = {0.25};
std::vector<double> opt = {10};
std::vector<int> num_iterations = {100000};
std::vector<double> pricer = {1};
int num_it_param = 10;
int numConv = 10000;

// Run simulations
std::vector<std::vector<double>> conv = simulConvergence(alpha, beta, gamma, epsilon, opt, num_iterations, possible_bet, pricer, num_it_param, numConv);

// Extract and write results
std::vector<double> conv1 = findCol(conv, 0);
std::vector<double> conv2 = findCol(conv, 1);
std::vector<double> alphas = findCol(conv, 2);
std::vector<double> gammas = findCol(conv, 4);

writeCSV("/Users/yannkerzreho/Documents/AC/sim_convergence.csv", conv1, conv2, alphas, gammas);
