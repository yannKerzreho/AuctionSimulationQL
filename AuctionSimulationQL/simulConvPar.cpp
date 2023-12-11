//
//  simulConvPar.c
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 11/12/2023.
//

#include "simulConvPar.h"

std::vector<std::vector<double>> processChunk(const std::vector<std::vector<double>>& combinations, const std::vector<double>& possible_bet, const int& num_it_param, const int& numConv, int start, int end) {
        
    std::vector<std::vector<double>> chunkResults;

    for (int i = start; i < end; ++i) {
        for (int it = 0; it < num_it_param; ++it) {
            
            std::vector<std::vector<int>> sim = simulation(combinations[i][0], combinations[i][1], combinations[i][2], combinations[i][3], combinations[i][4], combinations[i][5], possible_bet, combinations[i][6]);
            
            std::vector<int> conv = findConvergence(sim, numConv);
            
            std::vector<double> res = {static_cast<double>(conv[0]), static_cast<double>(conv[1]), combinations[i][0], combinations[i][1], combinations[i][2], combinations[i][3], combinations[i][4], combinations[i][5], combinations[i][6]};

            chunkResults.push_back(res);
        }
    }
    return chunkResults;
}

std::vector<std::vector<double>> simulConvPar(const std::vector<double>& alpha, const std::vector<double>& beta, const std::vector<double>& gamma, const std::vector<double>& epsilon, const std::vector<double>& opt, const std::vector<double>& num_iterations, const std::vector<double>& possible_bet, const std::vector<double>& pricer, const int& num_it_param, const int& numConv){
    
    std::vector<std::vector<double>> results;
    
    std::mutex resultsMutex;  // Mutex to protect access to the shared 'results' vector
 
    std::vector<std::vector<double>> combinations = generateCombinations(alpha, beta, gamma, epsilon, opt, num_iterations, pricer);

    // const int numChunks = 6; // Set the number of thread
    // const int chunkSize = combinations.size();
    
    const int numChunks = combinations.size(); // creat one thread for each combinaison
    const int chunkSize = 1;
    
    // Vector to hold thread objects
    std::vector<std::thread> threads;

    // Launch threads for each chunk
    for (int i = 0; i < numChunks; ++i) {
        int start = i * chunkSize;
        int end = (i == numChunks - 1) ? combinations.size() : (i + 1) * chunkSize;

        auto threadFunc = [&resultsMutex, &results](const std::vector<std::vector<double>>& combinations, const std::vector<double>& possible_bet, const int& num_it_param, const int& numConv, int start, int end){
            std::vector<std::vector<double>> chunkResults = processChunk(combinations, possible_bet, num_it_param, numConv, start, end);
            // Lock the mutex before modifying the shared 'results' vector
            resultsMutex.lock();
            results.insert(results.end(), chunkResults.begin(), chunkResults.end());
            resultsMutex.unlock();
        };
        
        // Start a thread for the current chunk
        std::thread myThread(threadFunc, std::ref(combinations), std::ref(possible_bet), std::ref(num_it_param), std::ref(numConv), start, end);
        threads.push_back(std::move(myThread));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return results;
}
