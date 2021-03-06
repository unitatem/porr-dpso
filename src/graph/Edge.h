//
// Created by mariusz on 05.11.18.
//

#ifndef PORR_DPSO_EDGE_H
#define PORR_DPSO_EDGE_H


#include <functional>

using NodeID = unsigned int;

struct Edge {
    NodeID from;
    NodeID to;
    float weight;

    friend bool operator==(const Edge &lhs, const Edge &rhs);

    Edge(NodeID from, NodeID to, float weight);
};

namespace std {
    template<>
    struct hash<Edge> {
        size_t operator()(const Edge &obj) const noexcept {
            int lo = min(obj.from, obj.to);
            int hi = max(obj.from, obj.to);
            return hash<int>{}(lo)
                   ^ (hash<int>{}(hi) << 1)
                   ^ (hash<float>{}(obj.weight) << 2);
        }
    };
}

#endif //PORR_DPSO_EDGE_H
