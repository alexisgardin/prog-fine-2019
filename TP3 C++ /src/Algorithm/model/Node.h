//
// Created by Alexis Gardin on 23/10/2019.
//

#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H
#define NULL_INT -999999

#include <ostream>

class Node {
public:
    int value, x, y;

    Node(int value);

    bool hasCoordinates();

    bool operator==(const Node &rhs) const {
        return value == rhs.value;
    }

    bool operator!=(const Node &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const Node &node);
};

#endif //GRAPH_NODE_H
