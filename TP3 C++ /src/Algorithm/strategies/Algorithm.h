//
// Created by Alexis Gardin on 16/10/2019.
//

#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H


#include <utility>
#include <vector>
#include <iostream>
#include "Algorithm/model/Graph.h"


class Algorithm {
protected:
    std::vector<std::pair<int, int>> arcs;
    std::string file;
public:
    Graph g;

    Algorithm(std::string file);

    virtual long run() = 0;

    long score();

    long scoreCoordinate();

    long scoreDistance();

    void displayMatrice();

    void displayMatriceWithValue();

    void output();

    void movedAllPointsToPositive();
};


#endif //GRAPH_ALGORITHM_H
