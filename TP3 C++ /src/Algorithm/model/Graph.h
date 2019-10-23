//
// Created by Alexis Gardin on 23/10/2019.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <unordered_map>
#include "Edge.h"
#include "Node.h"

class Graph {
public:
    unsigned int N;
    std::vector<std::shared_ptr<Edge>> edges;
    std::vector<std::vector<std::shared_ptr<Node>>> adjList;
    std::vector<std::shared_ptr<Node>> nodes;


    Graph(unsigned int n, std::vector<std::shared_ptr<Edge>> edges,
          std::vector<std::shared_ptr<Node>> nodes);

    Graph() = default;

    void printGraph();


};


#endif //GRAPH_GRAPH_H
