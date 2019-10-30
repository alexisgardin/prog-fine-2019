//
// Created by Alexis Gardin on 23/10/2019.
//

#include <iostream>
#include <utility>
#include "Graph.h"


void Graph::printGraph() {

    std::cout << "NODES : " << std::endl;
    for (std::shared_ptr<Node> node: nodes) {
        std::cout << node->value << ", ";
    }
    std::cout << std::endl;

    std::cout << "GRAPHES : " << std::endl;
    for (unsigned int i = 0; i < this->N; i++) {
        // print current vertex number
        std::cout << i << " --> ";

        // print all neighboring vertices of vertex i
        for (std::shared_ptr<Node> v : this->adjList[i])
            std::cout << v->value << " ";
        std::cout << std::endl;
    }


}

Graph::Graph(unsigned int n, std::vector<std::shared_ptr<Edge>> edges,
             std::vector<std::shared_ptr<Node>> nodes) : N(n), edges(std::move(edges)), nodes(std::move(nodes)) {
    adjList.resize(N);

    // add edges to the directed graph
    for (const std::shared_ptr<Edge> &edge: this->edges) {
        // insert at the end
        adjList[edge->src->value].insert(adjList[edge->src->value].end(), edge->dest);

        // Uncomment below line for undirected graph
        adjList[edge->dest->value].insert(adjList[edge->dest->value].end(), edge->src);
    }

}

