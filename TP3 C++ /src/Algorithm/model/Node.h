//
// Created by Alexis Gardin on 23/10/2019.
//

#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H


#include <ostream>

class Node {
public:
    int value, x, y;

    Node(int value);

    friend std::ostream &operator<<(std::ostream &os, const Node &node);
};


#endif //GRAPH_NODE_H
