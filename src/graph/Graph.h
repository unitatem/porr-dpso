//
// Created by mariusz on 05.11.18.
//

#ifndef PORR_DPSO_GRAPH_H
#define PORR_DPSO_GRAPH_H

#include <ostream>
#include "Node.h"

class Graph {
public:
    explicit Graph(int size);

    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);

    void addNode(NodeID id, float x, float y);

    void addEdge(Edge edge);

    void consolidate();

    int size() const;

    const Node &getNode(NodeID id) const;

    const std::vector<Edge> &getEdges(NodeID id) const;

    void change_edge_weight(NodeID from, NodeID to, float weight);

    float straight_line(NodeID from, NodeID to) const;

private:
    std::vector<Node> nodes;
};


#endif //PORR_DPSO_GRAPH_H
