//
//  writeCSV.c
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 05/12/2023.
//

#include "writeCSV.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Helper function to check if all vectors have the same size
template <typename T>
size_t checkVectorSizes(const T& first) {
    return first.size();
}

template <typename T, typename... Args>
size_t checkVectorSizes(const T& first, const Args&... rest) {
    if (first.size() != checkVectorSizes(rest...)) {
        std::cerr << "Error: Vectors must have the same size." << std::endl;
        std::exit(1);  // Exit the program
    }
    return first.size();
}

// Base case for recursion, writes the last element in the row
template<typename T>
void writeCSVRow(std::ofstream& outputFile, const T& element) {
    outputFile << element << "\n";
}

// Recursive case for variadic template, writes elements separated by commas
template<typename T, typename... Args>
void writeCSVRow(std::ofstream& outputFile, const T& first, const Args&... rest) {
    outputFile << first << ",";
    writeCSVRow(outputFile, rest...);
}

// Variadic template function to write a list of vectors to a CSV file
template<typename... Args>
void writeCSV(const std::string& filePath, const Args&... colums) {
    // Check if all vectors have the same size
    size_t numRows = checkVectorSizes(colums...);
    
    std::ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the file " << filePath << " for writing." << std::endl;
        return;
    }

    for (size_t row = 0; row < numRows; ++row) {
        // Write elements of each vector in the row
        writeCSVRow(outputFile, colums[row]...);
    }

    outputFile.close();
    std::cout << "CSV file written successfully to " << filePath << std::endl;
}
