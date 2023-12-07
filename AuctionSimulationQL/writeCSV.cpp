//
//  writeCSV.c
//  AuctionSimulationQL
//
//  Created by Yann Kerzreho on 07/12/2023.
//

#include <stdio.h>
#include "writeCSV.h"

std::vector<double> findCol(std::vector<std::vector<double>> data, const int j){
    std::vector<double> col;
    for (int i = 0; i < data.size(); i++) {
        col.push_back(data[i][j]);
    }
    return col;
}
