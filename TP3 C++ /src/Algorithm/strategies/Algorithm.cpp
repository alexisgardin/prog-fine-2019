//
// Created by Alexis Gardin on 16/10/2019.
//

#include <fstream>
#include "Algorithm.h"
#include <boost/algorithm/string.hpp>
#include <cstdlib>
#include <unordered_map>

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

