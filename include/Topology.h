#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <map>
#include <vector>
#include "Infrastructure.h"

class NetworkManager {
public:
    std::map<int, Node> nodes;
    std::vector<Link> links;

    NetworkManager() {
        
        nodes[0] = Node(0, true);
    }

    void add_link(int n1, int n2, Scalar value) {
        
        if (nodes.find(n1) == nodes.end()) nodes[n1] = Node(n1);
        if (nodes.find(n2) == nodes.end()) nodes[n2] = Node(n2);
        
        
        links.emplace_back(n1, n2, value);
    }
};

#endif