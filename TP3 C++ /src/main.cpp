
#include <iostream>
#include <Algorithm/strategies/AlgorithmTabu.h>
#include <Algorithm/strategies/AlgorithmQuadra.h>
#include <Algorithm/strategies/AlgorithmGreedy.h>
#include <dirent.h>
#include <sys/types.h>
#include <fstream>

#define DEBUG false
using namespace std;

std::vector<std::string> list_dir(std::string path) {
    std::vector<std::string> files;
    struct dirent *entry;
    DIR *dir = opendir(path.c_str());

    if (dir == NULL) {
        return files;
    }
    while ((entry = readdir(dir)) != NULL) {
        std::size_t found = std::string(entry->d_name).find(".in");
        if (found != std::string::npos && std::string(entry->d_name).find("output") == std::string::npos)
            files.push_back(path + "/" + entry->d_name);
    }
    closedir(dir);
    return files;
}

int main() //Driver Function for Dijkstra SSSP
{
    std::vector<std::string> files = list_dir("../files");
    std::for_each(files.begin(), files.end(), [&](const std::string &file) {
        double millis = 0;
        std::cout << "FILE : " << file << std::endl;
        int it = 50;
        int count = 0;
        int min = std::numeric_limits<int>::max();
        int max = 0;

        std::ofstream myfile;
        myfile.open("TABU_ALGO.csv", std::ofstream::out | std::ofstream::trunc);
        myfile << "FILE,AVG,MIN,MAX,TIME";
        for (int i = 0; i < it; ++i) {
            AlgorithmGreedy a(file);
            auto start = std::chrono::high_resolution_clock::now();
            int score = a.run();
            if (DEBUG) {
                for (std::shared_ptr<Edge> &e : a.g.edges) {
                    std::cout << e->src->value << " -> " << e->dest->value << " ";
                    std::cout << "(" << e->src->x << "," << e->src->y << ") ";
                    std::cout << "(" << e->dest->x << "," << e->dest->y << ") ";
                    std::cout << e->distance() <<
                              std::endl;
                }
                std::cout << "DISTANCE " << a.scoreDistance() << std::endl;
                std::cout << "COORD " << a.scoreCoordinate() << std::endl;
                a.displayMatriceWithValue();
            }
            auto end = std::chrono::high_resolution_clock::now();

            auto elapsed_seconds =
                    std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
                            end - start);
            millis += elapsed_seconds.count();
            count += score;
            min = std::min(min, score);
            max = std::max(score, max);
            if (score == min) {
                a.output();
                myfile << file << ",";
                myfile << count / it << ",";
                myfile << min << ",";
                myfile << max << ",";
                myfile << millis / it << ",";
                myfile.close();
            }
        }

        std::cout << "Count : " << count / it << std::endl;
        std::cout << "Min : " << min << std::endl;
        std::cout << "Max : " << max << std::endl;
        std::cout << "Time : " << millis / it << std::endl;

    });


}
