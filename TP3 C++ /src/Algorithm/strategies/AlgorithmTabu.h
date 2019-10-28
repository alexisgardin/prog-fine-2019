//
// Created by Alexis Gardin on 23/10/2019.
//

#ifndef GRAPH_ALGORITHMTABU_H
#define GRAPH_ALGORITHMTABU_H


#include "Algorithm.h"

class AlgorithmTabu : public Algorithm {
public:
    AlgorithmTabu(const std::string &file);

    int tabuTime = 0;

    int run() override;

    void computeTabu();
};


#endif //GRAPH_ALGORITHMTABU_H
