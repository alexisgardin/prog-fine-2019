//
// Created by Alexis Gardin on 23/10/2019.
//

#include "Node.h"

Node::Node(int value) : value(value) {}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << node.value;
    return os;
}
