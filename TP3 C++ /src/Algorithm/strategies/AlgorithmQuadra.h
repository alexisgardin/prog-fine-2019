//
// Created by Alexis Gardin on 23/10/2019.
//

#ifndef GRAPH_ALGORITHMQUADRA_H
#define GRAPH_ALGORITHMQUADRA_H


#include "Algorithm.h"

class AlgorithmQuadra : public Algorithm {
public:
    AlgorithmQuadra(const std::string &file);

    long run() override;

};


#endif //GRAPH_ALGORITHMQUADRA_H
