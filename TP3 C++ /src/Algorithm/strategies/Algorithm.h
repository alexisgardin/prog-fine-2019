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
    Graph g;
    std::vector<std::pair<int, int>> arcs;
    const std::string file;
public:
    Algorithm(std::string file);

    virtual void run() = 0;

};


#endif //GRAPH_ALGORITHM_H
