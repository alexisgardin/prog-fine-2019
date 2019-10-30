//
// Created by Alexis Gardin on 16/10/2019.
//

#include <fstream>
#include "Algorithm.h"
#include <boost/algorithm/string.hpp>
#include <unordered_map>
#include <unordered_set>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

Algorithm::Algorithm(std::string file) : file(file) {
    std::string line;
    std::ifstream myfile(file);
    unsigned int nodesNumber = 0;
    unsigned int count = 0;
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Edge>> edges;
    std::shared_ptr<Node> node;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            std::vector<std::string> results;
            boost::split(results, line, [](char c) { return c == ' '; });
            if (count == 0) {
                nodesNumber = std::stoi(results.at(0));
                nodes.resize(nodesNumber);
            } else {
                int value1 = std::stoi(results.at(0));
                int value2 = std::stoi(results.at(1));
                std::shared_ptr<Node> node1;
                std::shared_ptr<Node> node2;
                if (nodes.at(value1) == nullptr) {
                    node1 = std::make_shared<Node>(value1);
                    nodes[value1] = node1;
                }
                if (nodes.at(value2) == nullptr) {
                    node2 = std::make_shared<Node>(value2);
                    nodes[value2] = node2;
                }
                std::shared_ptr<Edge> edge = std::make_shared<Edge>(nodes[value1], nodes[value2]);
                edges.emplace_back(edge);
            }
            count++;
        }
        myfile.close();
    } else std::cout << "Unable to open file";
    g = Graph(nodesNumber, edges, nodes);
}

int Algorithm::score() {
    return scoreCoordinate() + scoreDistance();
}

int Algorithm::scoreCoordinate() {
    int maxX = 0;
    int maxY = 0;
    int minX = 0;
    int minY = 0;
    std::unordered_map<std::string, int> mapCoord;
    for (std::shared_ptr<Node> node : g.nodes) {
        maxX = std::max(maxX, node->x);
        maxY = std::max(maxY, node->y);
        minX = std::min(minX, node->x);
        minY = std::min(minY, node->y);
        std::string pair = std::to_string(node->x) + "-" + std::to_string(node->y);
        if (mapCoord.find(pair) == mapCoord.end()) {
            mapCoord.insert({pair, 1});
        } else {
            mapCoord[pair]++;
        }
    }
    int score = 0;
    for (std::pair<std::string, int> value : mapCoord) {
        score += 3 * std::pow(value.second - 1, 2);
    }

    maxX = std::abs(minX) + maxX;
    maxY = std::abs(minY) + maxY;
    int max = std::max(maxX, maxY);
    return score + (max * max);
}


int Algorithm::scoreDistance() {
    int score = 0;

    for (const std::shared_ptr<Edge> &edge : g.edges) {
        score += 2 * std::pow(edge->distance() - 1, 2);
        if (edge->src->x == edge->dest->x && edge->dest->y == edge->src->y)
            score = +99999;
    }
    return score;
}


void Algorithm::movedAllPointsToPositive() {
    int minX = 999999, minY = 999999;

    for (auto &node : g.nodes) {
        if (node->x < minX) {
            minX = node->x;
        }

        if (node->y < minY) {
            minY = node->y;
        }
    }

    int x = std::abs(minX), y = std::abs(minY);
    for (auto &node : g.nodes) {
        node->x += x;
        node->y += y;
    }
}

void Algorithm::displayMatrice() {
    // matrix<int> m(std::ceil(std::sqrt(g.nodes.size())) + 1, std::ceil(std::sqrt(g.nodes.size())) + 1, 0);
    matrix<int> m(g.nodes.size(), g.nodes.size(), 0);

    for (const std::shared_ptr<Node> &node : g.nodes) {
        //std::cout << node->x << ", " << node->y << std::endl;
        m(node->x, node->y) += 1;
    }

    for (unsigned i = 0; i < m.size1(); ++i) {
        std::cout << "| ";
        for (unsigned j = 0; j < m.size2(); ++j) {
            std::cout << m(i, j) << " | ";
        }
        std::cout << "|" << std::endl;
    }
}


void Algorithm::displayMatriceWithValue() {
    movedAllPointsToPositive();
    //matrix<int> m(std::ceil(std::sqrt(g.nodes.size())) + 1, std::ceil(std::sqrt(g.nodes.size())) + 1, 0);
    matrix<int> m(g.nodes.size(), g.nodes.size(), 0);

    for (std::shared_ptr<Node> &node : g.nodes) {
        // std::cout << node->x << ", " << node->y << std::endl;
        m(node->x, node->y) = node->value;
    }

    for (unsigned i = 0; i < m.size1(); ++i) {
        std::cout << "| ";
        for (unsigned j = 0; j < m.size2(); ++j) {
            std::cout << m(i, j) << " | ";
        }
        std::cout << "|" << std::endl;
    }
}

void Algorithm::output() {
    std::ofstream myfile;
    myfile.open(file + ".output", std::ofstream::out | std::ofstream::trunc);
    for (std::shared_ptr<Node> &node : g.nodes) {
        myfile << node->x << " " << node->y << std::endl;
    }
    myfile.close();

}

