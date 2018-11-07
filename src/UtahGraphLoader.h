//
// Created by mariusz on 07.11.18.
//

#ifndef PORR_DPSO_UTAHGRAPHLOADER_H
#define PORR_DPSO_UTAHGRAPHLOADER_H


#include <string>
#include "graph/Graph.h"

class UtahGraphLoader {
public:
    UtahGraphLoader(std::string name, int nodes);

    Graph load();

private:
    const std::string path;
    Graph graph;
    const int nodes_cnt;

    void load_nodes();

    void load_edges();

};


#endif //PORR_DPSO_UTAHGRAPHLOADER_H