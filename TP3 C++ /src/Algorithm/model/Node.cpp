//
// Created by Alexis Gardin on 23/10/2019.
//

#include "Node.h"

Node::Node(int value) : value(value), x(NULL_INT), y(NULL_INT) {}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << node.value;
    return os;
}

bool Node::hasCoordinates() {
    return this->x != NULL_INT || this->y != NULL_INT;
}
