//
//  main.cpp
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 04/12/2023.
//

#include <iostream>
#include "writeCSV.h"

int main() {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};
    std::vector<int> vec3 = {7, 8, 9};

    // Example usage
    writeCSV("/Users/yannkerzreho/Documents/AC/try.csv", vec1, vec2, vec3);

    return 0;
}

