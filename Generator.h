//
// Created by Alexis Gardin on 2019-09-23.
//

#ifndef PROGFINE_GENERATOR_H
#define PROGFINE_GENERATOR_H

#include <vector>
#include <random>


namespace Generator {

    std::vector<int> randomList(int min, int max, int occurence) {

        std::random_device random_device;
        std::mt19937 random_engine(random_device());
        std::uniform_int_distribution<int> distrib(min, max);
        std::vector<int> rl;
        for (int i = 0; i < occurence; ++i) {

            auto const randomNumber = distrib(random_engine);
            rl.push_back(randomNumber);
        }
        return rl;

    }
}
#endif //PROGFINE_GENERATOR_H
