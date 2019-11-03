//
// Created by Jérémi Ferré on 23/10/2019.
//

#include <random>
#include <array>
#include "AlgorithmGreedy.h"

double distance(int x1, int y1, int x2, int y2);

double distance(int x1, int y1, int x2, int y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

AlgorithmGreedy::AlgorithmGreedy(const std::string &file) : Algorithm(file) {}

long AlgorithmGreedy::run() {

    auto node = this->g.nodes[0];
    this->setCoordinates(node, 0, 0);
    this->evaluateNode(node);

    for (const auto &n : this->g.nodes) {
        if (n->hasCoordinates()) {
            this->evaluateNode(n);
        }
    }

    for (const auto &n : this->g.nodes) {
        if (!n->hasCoordinates()) {
            auto coord = this->findNearestCoordinates(0, 0, n, true);
            this->setCoordinates(n, coord.first, coord.second);
        }
    }

    return score();
}

void AlgorithmGreedy::evaluateNode(const std::shared_ptr<Node> &node) {
    // Node already placed here
    this->evaluatedNodes.insert(this->evaluatedNodes.end(), node);

    bool jump = false;
    std::vector<std::shared_ptr<Node>> nodesToPlace;
    for (const auto &n : this->g.adjList[node->value]) {
        if (n->hasCoordinates()) continue;

        for (const auto &n2 : this->g.adjList[n->value]) {
            if (n2->value == node->value) continue;

            // Two cases, is there a square, or not
            for (const auto &n3 : this->g.adjList[n2->value]) {
                if (n3->value == n->value) continue;

                auto it = this->g.adjList[node->value].find(n3);
                if (it != this->g.adjList[node->value].end()) {
                    // First case
                    const auto &farFromCur = n2;
                    const auto &firstClose = n;
                    const auto &secondClose = n3;

                    placeSquare(node, firstClose, secondClose, farFromCur);
                    jump = true;
                    goto cnt;
                }
            }
        }
        cnt:;

        if (!jump) {
            // Second case : no square found in second level
            // Need to place n correctly
            nodesToPlace.emplace_back(n);
        }

        jump = false;
    }

    for (const auto &n : nodesToPlace) {
        this->placeOne(node, n);
    }

    for (const auto &n : this->g.adjList[node->value]) {
        if (this->evaluatedNodes.find(n) == this->evaluatedNodes.end()) {
            this->evaluateNode(n);
        }
    }
}

std::pair<int, int>
AlgorithmGreedy::findNearestCoordinates(const int curX, const int curY, const std::shared_ptr<Node> &nodeToPlace,
                                        bool isAvailable = false) {

    int x = curX, y = curY, dx = 0, dy = -1, temp;
    for (;;) {
        // DO STUFF
        std::string str = std::to_string(x) + "-" + std::to_string(y);
        auto it = this->usedCoordinates.find(str);
        if (it == this->usedCoordinates.end()) {
            return std::pair<int, int>(x, y);
        } else {
            if (isAvailable) {
                goto fnt;
            }

            auto tuple = *it;
            auto list = this->g.adjList[nodeToPlace->value];
            bool found = false;
            for (const auto &n : tuple.second) {
                auto f = list.find(n);
                if (f != list.end()) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return std::pair<int, int>(x, y);
            }
        }
        fnt:;

        if (x == y || (x < 0 && x == -y) || (x > 0 && x == 1 - y)) {
            temp = dx;
            dx = -dy;
            dy = temp;
        }
        x += dx;
        y += dy;
    }
}

void AlgorithmGreedy::placeOne(const std::shared_ptr<Node> &current, const std::shared_ptr<Node> &toPlace) {
    int curX = current->x;
    int curY = current->y;

    std::string north = std::to_string(curX) + "-" + std::to_string(curY + 1);
    std::string east = std::to_string(curX + 1) + "-" + std::to_string(curY);
    std::string south = std::to_string(curX) + "-" + std::to_string(curY - 1);
    std::string west = std::to_string(curX - 1) + "-" + std::to_string(curY);

    bool northAvailable = this->usedCoordinates.find(north) == this->usedCoordinates.end();
    bool eastAvailable = this->usedCoordinates.find(east) == this->usedCoordinates.end();
    bool southAvailable = this->usedCoordinates.find(south) == this->usedCoordinates.end();
    bool westAvailable = this->usedCoordinates.find(west) == this->usedCoordinates.end();

    std::vector<std::pair<double, std::pair<bool, std::pair<int, int>>>> toEvaluate;
    toEvaluate.emplace_back(std::pair<double, std::pair<bool, std::pair<int, int>>>(distance(0, 0, curX, curY + 1),
                                                                                    std::pair<bool, std::pair<int, int>>(
                                                                                            northAvailable,
                                                                                            std::pair<int, int>(curX,
                                                                                                                curY +
                                                                                                                1))));
    toEvaluate.emplace_back(std::pair<double, std::pair<bool, std::pair<int, int>>>(distance(0, 0, curX + 1, curY),
                                                                                    std::pair<bool, std::pair<int, int>>(
                                                                                            eastAvailable,
                                                                                            std::pair<int, int>(
                                                                                                    curX + 1,
                                                                                                    curY))));
    toEvaluate.emplace_back(std::pair<double, std::pair<bool, std::pair<int, int>>>(distance(0, 0, curX, curY - 1),
                                                                                    std::pair<bool, std::pair<int, int>>(
                                                                                            southAvailable,
                                                                                            std::pair<int, int>(curX,
                                                                                                                curY -
                                                                                                                1))));
    toEvaluate.emplace_back(std::pair<double, std::pair<bool, std::pair<int, int>>>(distance(0, 0, curX - 1, curY),
                                                                                    std::pair<bool, std::pair<int, int>>(
                                                                                            westAvailable,
                                                                                            std::pair<int, int>(
                                                                                                    curX - 1,
                                                                                                    curY))));

    std::sort(std::begin(toEvaluate), std::end(toEvaluate));
    for (auto &tuple : toEvaluate) {
        if (tuple.second.first) {
            this->setCoordinates(toPlace, tuple.second.second.first, tuple.second.second.second);
            return;
        }
    }

    auto coord = this->findNearestCoordinates(curX, curY, toPlace, true);
    this->setCoordinates(toPlace, coord.first, coord.second);
}

void AlgorithmGreedy::placeSquare(const std::shared_ptr<Node> &current, const std::shared_ptr<Node> &close1,
                                  const std::shared_ptr<Node> &close2, const std::shared_ptr<Node> &far) {
    int curX = current->x;
    int curY = current->y;

    std::string north = std::to_string(curX) + "-" + std::to_string(curY + 1);
    std::string east = std::to_string(curX + 1) + "-" + std::to_string(curY);
    std::string south = std::to_string(curX) + "-" + std::to_string(curY - 1);
    std::string west = std::to_string(curX - 1) + "-" + std::to_string(curY);

    bool northAvailable = this->usedCoordinates.find(north) == this->usedCoordinates.end();
    bool eastAvailable = this->usedCoordinates.find(east) == this->usedCoordinates.end();
    bool southAvailable = this->usedCoordinates.find(south) == this->usedCoordinates.end();
    bool westAvailable = this->usedCoordinates.find(west) == this->usedCoordinates.end();

    if (close2->hasCoordinates()) {
        int close2X = close2->x;
        int close2Y = close2->y;

        std::string close2Coord = std::to_string(close2X) + "-" + std::to_string(close2Y);
        if (!northAvailable && !eastAvailable && !southAvailable && !westAvailable) {
            auto coord1 = this->findNearestCoordinates(curX, curY, close1, true);
            this->setCoordinates(close1, coord1.first, coord1.second);

            auto coord2 = this->findNearestCoordinates(curX, curY, far, true);
            this->setCoordinates(far, coord2.first, coord2.second);
            return;
        }

        if (close2Coord == north) {
            if (eastAvailable) {
                this->setCoordinates(close1, curX + 1, curY);
                this->setCoordinates(far, close2X + 1, close2Y);
                return;
            } else if (westAvailable) {
                this->setCoordinates(close1, curX - 1, curY);
                this->setCoordinates(far, close2X - 1, close2Y);
                return;
            } else if (southAvailable) {
                this->setCoordinates(close1, curX, curY - 1);
                this->setCoordinates(far, close1->x - 1, close1->y);
                return;
            }
        } else if (close2Coord == south) {
            if (eastAvailable) {
                this->setCoordinates(close1, curX + 1, curY);
                this->setCoordinates(far, close2X + 1, close2Y);
                return;
            } else if (westAvailable) {
                this->setCoordinates(close1, curX - 1, curY);
                this->setCoordinates(far, close2X - 1, close2Y);
                return;
            } else if (northAvailable) {
                this->setCoordinates(close1, curX, curY + 1);
                this->setCoordinates(far, close1->x + 1, close1->y);
                return;
            }
        } else if (close2Coord == east) {
            if (northAvailable) {
                this->setCoordinates(close1, curX, curY + 1);
                this->setCoordinates(far, close2X, close2Y + 1);
                return;
            } else if (southAvailable) {
                this->setCoordinates(close1, curX, curY - 1);
                this->setCoordinates(far, close2X, close2Y - 1);
                return;
            } else if (westAvailable) {
                this->setCoordinates(close1, curX - 1, curY);
                this->setCoordinates(far, close1->x, close1->y - 1);
                return;
            }
        } else if (close2Coord == west) {
            if (northAvailable) {
                this->setCoordinates(close1, curX, curY + 1);
                this->setCoordinates(far, close2X, close2Y + 1);
                return;
            } else if (southAvailable) {
                this->setCoordinates(close1, curX, curY - 1);
                this->setCoordinates(far, close2X, close2Y - 1);
                return;
            } else if (eastAvailable) {
                this->setCoordinates(close1, curX + 1, curY);
                this->setCoordinates(far, close1->x, close1->y + 1);
                return;
            }
        }
    }

    if (!northAvailable && !eastAvailable && !southAvailable && !westAvailable) {
        auto coord1 = this->findNearestCoordinates(curX, curY, close1, true);
        this->setCoordinates(close1, coord1.first, coord1.second);

        auto coord2 = this->findNearestCoordinates(curX, curY, far, true);
        this->setCoordinates(far, coord2.first, coord2.second);

        auto coord3 = this->findNearestCoordinates(curX, curY, close2, true);
        this->setCoordinates(close2, coord3.first, coord3.second);
        return;
    }

    if (northAvailable && eastAvailable) {
        this->setCoordinates(close1, curX, curY + 1);
        this->setCoordinates(close2, curX + 1, curY);
        this->setCoordinates(far, curX + 1, curY + 1);
        return;
    } else if (northAvailable && westAvailable) {
        this->setCoordinates(close1, curX, curY + 1);
        this->setCoordinates(close2, curX - 1, curY);
        this->setCoordinates(far, curX - 1, curY + 1);
        return;
    } else if (southAvailable && eastAvailable) {
        this->setCoordinates(close1, curX, curY - 1);
        this->setCoordinates(close2, curX + 1, curY);
        this->setCoordinates(far, curX + 1, curY - 1);
        return;
    } else if (southAvailable && westAvailable) {
        this->setCoordinates(close1, curX, curY - 1);
        this->setCoordinates(close2, curX - 1, curY);
        this->setCoordinates(far, curX - 1, curY - 1);
        return;
    } else {
        if (northAvailable) {
            this->setCoordinates(close1, curX, curY + 1);

            auto coord1 = this->findNearestCoordinates(curX, curY, close2, true);
            this->setCoordinates(close2, coord1.first, coord1.second);

            auto coord2 = this->findNearestCoordinates(curX, curY, far, true);
            this->setCoordinates(far, coord2.first, coord2.second);
            return;
        } else if (eastAvailable) {
            this->setCoordinates(close1, curX + 1, curY);

            auto coord1 = this->findNearestCoordinates(curX, curY, close2, true);
            this->setCoordinates(close2, coord1.first, coord1.second);

            auto coord2 = this->findNearestCoordinates(curX, curY, far, true);
            this->setCoordinates(far, coord2.first, coord2.second);
            return;
        } else if (southAvailable) {
            this->setCoordinates(close1, curX, curY - 1);

            auto coord1 = this->findNearestCoordinates(curX, curY, close2, true);
            this->setCoordinates(close2, coord1.first, coord1.second);

            auto coord2 = this->findNearestCoordinates(curX, curY, far, true);
            this->setCoordinates(far, coord2.first, coord2.second);
            return;
        } else if (westAvailable) {
            this->setCoordinates(close1, curX - 1, curY);

            auto coord1 = this->findNearestCoordinates(curX, curY, close2, true);
            this->setCoordinates(close2, coord1.first, coord1.second);

            auto coord2 = this->findNearestCoordinates(curX, curY, far, true);
            this->setCoordinates(far, coord2.first, coord2.second);
            return;
        } else {
            auto coord1 = this->findNearestCoordinates(curX, curY, close1, true);
            this->setCoordinates(close1, coord1.first, coord1.second);

            auto coord2 = this->findNearestCoordinates(curX, curY, far, true);
            this->setCoordinates(far, coord2.first, coord2.second);

            auto coord3 = this->findNearestCoordinates(curX, curY, close2, true);
            this->setCoordinates(close2, coord3.first, coord3.second);
            return;
        }
    }
}

void AlgorithmGreedy::setCoordinates(const std::shared_ptr<Node> &node, const int x, const int y) {
    node->x = x;
    node->y = y;

    std::string str = std::to_string(x) + "-" + std::to_string(y);
    auto it = this->usedCoordinates.find(str);
    if (it == this->usedCoordinates.end()) {
        std::unordered_set<std::shared_ptr<Node>> set;
        set.insert(set.end(), node);
        this->usedCoordinates.emplace(str, set);
    } else {
        auto tuple = *it;
        it->second.insert(it->second.end(), node);
    }
}

