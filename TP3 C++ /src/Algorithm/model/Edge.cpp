//
// Created by Alexis Gardin on 23/10/2019.
//

#include "Edge.h"

Edge::Edge(std::shared_ptr<Node> src, std::shared_ptr<Node> dest) : src(src), dest(dest) {}

int Edge::distance() {
    return std::abs(dest->x - src->x) + std::abs(dest->y - src->y);
}
