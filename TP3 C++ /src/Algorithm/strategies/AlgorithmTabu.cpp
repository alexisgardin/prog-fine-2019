//
// Created by Alexis Gardin on 23/10/2019.
//

#include <random>
#include "AlgorithmTabu.h"

AlgorithmTabu::AlgorithmTabu(const std::string &file) : Algorithm(file) {}

#define ITERATION_NUMBER 1000
#define TABU_TIME 3


std::string keyGenerator(int value, int x, int y) {
    return std::to_string(value) + ":" + std::to_string(x) + "-" + std::to_string(y);
}

void AlgorithmTabu::run() {
    std::unordered_map<std::string, int> tabu;
    int bestScore = 0;
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib{0, (int) std::ceil(std::sqrt(g.nodes.size()))};
    std::cout << "TABU" << std::endl;
    g.printGraph();
    std::for_each(g.nodes.begin(), g.nodes.end(), [&](std::shared_ptr<Node> &node) {
        node->x = distrib(re);
        node->y = distrib(re);
        std::string key = keyGenerator(node->value, node->x, node->y);
        tabu.insert({key, TABU_TIME});
    });
    bestScore = score();

    for (unsigned int i = 0; i < ITERATION_NUMBER; i++) {
        std::for_each(g.nodes.begin(), g.nodes.end(), [&](std::shared_ptr<Node> &node) {

            std::string key = keyGenerator(node->value, node->x, node->y);
            int tempx = node->x;
            int tempy = node->y;
            std::string key2;

            do {
                node->x = distrib(re);
                node->y = distrib(re);
                key2 = keyGenerator(node->value, node->x, node->y);
            } while (tabu.find(key2) != tabu.end());
            tabu.insert({key2, ITERATION_NUMBER});
            int s = score();
            if (s < bestScore) {
                node->x = tempx;
                node->y = tempy;
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
    std::cout << "RESULTAT : " << score() << std::endl;
    displayMatrice();
}
