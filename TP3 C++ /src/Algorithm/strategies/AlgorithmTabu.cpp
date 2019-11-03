//
// Created by Alexis Gardin on 23/10/2019.
//

#include <random>
#include <unordered_map>
#include "AlgorithmTabu.h"

AlgorithmTabu::AlgorithmTabu(const std::string &file) : Algorithm(file) {}

#define ITERATION_NUMBER 10000


std::string keyGenerator(int value, int x, int y) {
    return std::to_string(value) + ":" + std::to_string(x) + "-" + std::to_string(y);
    //return std::to_string(x) + "-" + std::to_string(y);
}

long AlgorithmTabu::run() {
    computeTabu();
    return algo_1();
}

void AlgorithmTabu::computeTabu() {
    //this->tabuTime = 100;
    this->tabuTime = std::max(std::ceil(std::sqrt(g.edges.size())), std::ceil(std::sqrt(g.nodes.size())));

}

int AlgorithmTabu::algo_1() {
    int sameCounter = 0;
    std::unordered_map<std::string, int> tabu;
    long bestScore = 0;
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib{0, (int) std::ceil(std::sqrt(g.nodes.size()))};
    //std::cout << "TABU" << std::endl;
    //g.printGraph();

    std::for_each(g.nodes.begin(), g.nodes.end(), [&](std::shared_ptr<Node> &node) {
        node->x = distrib(re);
        node->y = distrib(re);
        std::string key = keyGenerator(node->value, node->x, node->y);
        tabu.insert({key, this->tabuTime});
    });
    bestScore = score();

    for (unsigned int i = 0; i < ITERATION_NUMBER; i++) {
        std::for_each(g.nodes.begin(), g.nodes.end(), [&](std::shared_ptr<Node> &node) {

            std::string key = keyGenerator(node->value, node->x, node->y);
            int tempx = node->x;
            int tempy = node->y;
            std::string key2;
            int count = 0;
            do {
                node->x = distrib(re);
                node->y = distrib(re);
                key2 = keyGenerator(node->value, node->x, node->y);
                count++;
            } while (tabu.find(key2) != tabu.end());
            tabu.insert({key2, this->tabuTime});
            long s = score();
            if (s > bestScore) {
                sameCounter++;
                if (sameCounter != ITERATION_NUMBER / std::max(std::ceil(std::sqrt(g.edges.size())),
                                                               std::ceil(std::sqrt(g.nodes.size())))) {
                    node->x = tempx;
                    node->y = tempy;
                } else {
                    sameCounter = 0;
                }
            } else {
                bestScore = s;
                sameCounter = 0;
            }
        });


        std::vector<std::string> toRemove;
        for (std::pair<std::string, int> pair : tabu) {
            if (pair.second == 0) {
                toRemove.push_back(pair.first);
            } else {
                tabu[pair.first]--;
            }
        }
        for (std::string &toRemove: toRemove) {
            tabu.erase(toRemove);
        }
    }
    //std::cout << "RESULTAT : " << score() << std::endl;
    //displayMatrice();
    //displayMatriceWithValue();
    return bestScore;
}

