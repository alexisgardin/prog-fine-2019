
#include <iostream>
#include <Algorithm/strategies/AlgorithmTabu.h>
#include <Algorithm/strategies/AlgorithmGreedy.h>

using namespace std;

using namespace std;


int main() //Driver Function for Dijkstra SSSP
{
    int it = 50;
    int count = 0;
    int min = std::numeric_limits<int>::max();
    int max = 0;
    for (int i = 0; i < it; ++i) {
        AlgorithmGreedy a("../files/CP16.txt");
        int score = a.run();
        count += score;
        min = std::min(min, score);
        max = std::max(score, max);
    }
    std::cout << "Count : " << count / it << std::endl;
    std::cout << "Min : " << min << std::endl;
    std::cout << "Max : " << max << std::endl;
}