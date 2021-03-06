//
// Created by mariusz on 27.11.18.
//

#include "Astar.h"

Astar::Astar(const Graph &graph, NodeID from, NodeID to)
        : graph(graph), from(from), to(to) {
    open_set.insert(from);

    score_from_start.rehash(static_cast<unsigned long>(graph.size()));
    score_from_start.insert({from, 0.0});

    score_total_heuristic.rehash(static_cast<unsigned long>(graph.size()));
    for (auto id = 0; id < graph.size(); ++id)
        score_total_heuristic.insert({static_cast<const NodeID &>(id), std::numeric_limits<float>::max()});
    score_total_heuristic.insert({from, graph.straight_line(from, to)});
}

std::vector<NodeID> Astar::solve() {
    while (!open_set.empty()) {
        auto current = smallest_in_open_set();
        if (current == to)
            return reconstruct_path(current);

        open_set.erase(current);
        closed_set.insert(current);

        for (const auto &edge_out : graph.getEdges(current)) {
            auto neighbour = edge_out.to;

            if (std::find(closed_set.begin(), closed_set.end(), neighbour) != closed_set.end())
                continue;

            auto distance_from_start_to_neighbour = score_from_start[current] + edge_out.weight;
            if (std::find(open_set.begin(), open_set.end(), neighbour) == open_set.end())
                open_set.insert(neighbour);
            else if (distance_from_start_to_neighbour >= score_from_start[neighbour])
                continue;

            came_from.insert({neighbour, current});
            score_from_start.insert({neighbour, distance_from_start_to_neighbour});
            score_total_heuristic.insert(
                    {neighbour, distance_from_start_to_neighbour + graph.straight_line(neighbour, to)});
        }
    }
    return {};
}

NodeID Astar::smallest_in_open_set() {
    NodeID id = *open_set.begin();
    float value = std::numeric_limits<float>::max();
    for (const auto &n : open_set) {
        auto v = score_total_heuristic[n];
        if (v < value)
            id = n;
    }
    return id;
}

std::vector<NodeID> Astar::reconstruct_path(NodeID current) const {
    std::vector<NodeID> path;

    path.push_back(current);
    while (came_from.find(current) != came_from.end()) {
        current = came_from.at(current);
        path.push_back(current);
    }
    return path;
}
