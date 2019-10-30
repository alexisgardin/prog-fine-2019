
#include <iostream>
#include <Algorithm/strategies/AlgorithmTabu.h>
#include <Algorithm/strategies/AlgorithmQuadra.h>

#include <dirent.h>
#include <sys/types.h>

using namespace std;

std::vector<std::string> list_dir(std::string path) {
    std::vector<std::string> files;
    struct dirent *entry;
    DIR *dir = opendir(path.c_str());

    if (dir == NULL) {
        return files;
    }
    while ((entry = readdir(dir)) != NULL) {
        std::size_t found = std::string(entry->d_name).find(".txt");
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
        for (int i = 0; i < it; ++i) {
            AlgorithmTabu a(file);
            auto start = std::chrono::high_resolution_clock::now();
            int score = a.run();
            auto end = std::chrono::high_resolution_clock::now();

            // a.displayMatriceWithValue();
            auto elapsed_seconds =
                    std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
                            end - start);
            millis += elapsed_seconds.count();
            count += score;
            min = std::min(min, score);
            if (score == min) {
                a.output();
            }
            max = std::max(score, max);
        }
        std::cout << "Count : " << count / it << std::endl;
        std::cout << "Min : " << min << std::endl;
        std::cout << "Max : " << max << std::endl;
        std::cout << "Time : " << millis / it << std::endl;
    });


}
