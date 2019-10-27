//
// Created by Alexis Gardin on 23/10/2019.
//

#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H


#include "Node.h"

class Edge {
public:
    std::shared_ptr<Node> src, dest;

    Edge(std::shared_ptr<Node> src, std::shared_ptr<Node> dest);

    int distance();

};


#endif //GRAPH_EDGE_H
