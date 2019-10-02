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

    template<typename T>
    std::vector<int> linspace(T start_in, T end_in, int num_in) {

        std::vector<int> linspaced;

        double start = static_cast<double>(start_in);
        double end = static_cast<double>(end_in);
        double num = static_cast<double>(num_in);

        if (num == 0) { return linspaced; }
        if (num == 1) {
            linspaced.push_back(start);
            return linspaced;
        }

        double delta = (end - start) / (num - 1);

        for (int i = 0; i < num - 1; ++i) {
            linspaced.push_back(start + delta * i);
        }
        linspaced.push_back(end); // I want to ensure that start and end
        // are exactly the same as the input
        return linspaced;
    }

    std::vector<int> orderedList(int min, int max, int occurence) {

        return linspace(min, max, occurence);

    }


}
#endif //PROGFINE_GENERATOR_H
