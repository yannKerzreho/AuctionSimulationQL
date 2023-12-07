# AuctionSimulationQL

This repository contains a C++ implementation of a simulation framework for auction scenarios using Q-learning. The simulation is designed to model interactions between two agents engaged in auctions over multiple iterations as presented in Artificial Intelligence and Auction Design by M. Banchio and A. Skrzypacz 2022. 

## Main Contents

- **simulation**: The main simulation function (`simulation`) that models the auction process, taking various parameters like alpha, beta, gamma and epsilon (for the parametrization of QL algorithme). opt is used to initialize Q-matrix, num_iterations is the number of round play by the algorithme, possible_bet are the available actions (with a price set at 1), and pricer manage the auction design (1 for a first price and 2 for a second price, between 1 and 2 for any convex combinaison).

- **findConvergence**: The function (`findConvergence`) analyzes the convergence of Q-algo over combinaison of a specified parameters (used to run (`simulation`)). num_it_param set how many run for each set of parameter and numConv set the number of iteration used to assume convergence.

## Additional function

- **findCol**: To extract from a array a colum the function (`findCol`) take as argument a `std::vector<std::vector<double>>`and a `int` for the index of the colum.

- **writeCSV**: Creat a .csv at the path (first argument) with the set of vectors used as argument.

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
