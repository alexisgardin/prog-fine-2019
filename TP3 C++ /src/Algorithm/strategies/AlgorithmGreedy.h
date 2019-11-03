//
// Created by Jérémi Ferré on 23/10/2019.
//

#ifndef GRAPH_ALGORITHMGREEDY_H
#define GRAPH_ALGORITHMGREEDY_H

#include <unordered_map>
#include "Algorithm.h"

class AlgorithmGreedy : public Algorithm {
public:
    std::unordered_map<std::string, std::unordered_set<std::shared_ptr<Node>>> usedCoordinates;
    std::unordered_set<std::shared_ptr<Node>> evaluatedNodes;

    AlgorithmGreedy(const std::string &file);

    long run() override;

    std::pair<int, int>
    findNearestCoordinates(const int curX, const int curY, const std::shared_ptr<Node> &nodeToPlace, bool isAvailable);

    void placeOne(const std::shared_ptr<Node> &current, const std::shared_ptr<Node> &toPlace);

    void setCoordinates(const std::shared_ptr<Node> &, const int, const int);

    void evaluateNode(const std::shared_ptr<Node> &);

    void placeSquare(const std::shared_ptr<Node> &current, const std::shared_ptr<Node> &close1,
                     const std::shared_ptr<Node> &close2, const std::shared_ptr<Node> &far);

};


#endif //GRAPH_ALGORITHMGREEDY_H
