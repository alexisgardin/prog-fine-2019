//
// Created by Alexis Gardin on 23/10/2019.
//

#include <random>
#include "AlgorithmQuadra.h"

AlgorithmQuadra::AlgorithmQuadra(const std::string &file) : Algorithm(file) {}

long AlgorithmQuadra::run() {

    for (std::shared_ptr<Node> &node : g.nodes) {
        node->x = 0;
        node->y = 0;
    }

    int bestScore = score();
    for (std::shared_ptr<Node> &node : g.nodes) {
        for (std::shared_ptr<Node> &node2 : g.nodes) {
            if (node->value != node2->value) {
                for (int x = -1; x < 2; ++x) {
                    for (int y = -1; y < 2; ++y) {
                        node2->x += x;
                        node2->y += y;
                        int temp = score();
                        if (temp > bestScore) {
                            node2->x -= x;
                            node2->y -= y;
                        } else {
                            bestScore = temp;
                        }
                    }
                }
            }
        }
    }
    return bestScore;
}
