//
//  writeCSV.h
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 05/12/2023.
//

#ifndef writeCSV_h
#define writeCSV_h

#include <stdio.h>

#include "writeCSV.tpp"  // Include the template implementation

// Base case for recursion, writes the last element in the row
template <typename T>
void writeCSVRow(std::ofstream& outputFile, const T& element);

// Recursive case for variadic template, writes elements separated by commas
template <typename T, typename... Args>
void writeCSVRow(std::ofstream& outputFile, const T& first, const Args&... rest);

// Helper function to check if all vectors have the same size
template <typename T>
size_t checkVectorSizes(const T& first);

template <typename T, typename... Args>
size_t checkVectorSizes(const T& first, const Args&... rest);

// Variadic template function to write a list of vectors to a CSV file
template <typename... Args>
void writeCSV(const std::string& filePath, const Args&... vectors);

#endif /* writeCSV_h */
