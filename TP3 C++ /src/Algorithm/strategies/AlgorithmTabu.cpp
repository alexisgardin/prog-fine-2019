//
// Created by Alexis Gardin on 23/10/2019.
//

#include "AlgorithmTabu.h"

AlgorithmTabu::AlgorithmTabu(const std::string &file) : Algorithm(file) {}

void AlgorithmTabu::run() {
    std::cout << "TABU" << std::endl;
    g.printGraph();
}
