#define TOPOLOGY_H

#include <map>
#include <vector>
#include <memory>
#include "Infrastructure.h"

class NetworkManager {
public:
    std::map<int, Node> nodes;  
    std::vector<Component*> components;
    
    NetworkManager() {
        nodes[0] = Node(0, true);
    }

    void add_link(int n1, int n2, Scalar value) {
        ensure_nodes(n1, n2);
        components.push_back(new Link(n1, n2, value));
    }
    
    void add_storage(int n1, int n2, Scalar capacity) {
        ensure_nodes(n1, n2);
        components.push_back(new Storage(n1, n2, capacity));
    }

    void ensure_nodes(int n1, int n2) {
        if (nodes.find(n1) == nodes.end()) nodes[n1] = Node(n1);
        if (nodes.find(n2) == nodes.end()) nodes[n2] = Node(n2);
    }
    
    Matrix calculate_A() {
        int m = components.size();
        int n = 0;
        
       
        for(auto& [id, node] : nodes) {
            if (!node.is_reference) {
                node.matrix_index = n;
                n++;
            } else {
                node.matrix_index = -1;
            }
        }
        
        Matrix A(m, Vector(n, 0.0));
        
       
        for(int i = 0; i < m; i++) {
            int idx_a = nodes[components[i]->node_a].matrix_index;
            int idx_b = nodes[components[i]->node_b].matrix_index;
            
            if (idx_a != -1) A[i][idx_a] = 1.0;
            if (idx_b != -1) A[i][idx_b] = -1.0;
        }
        
        return A;
    }

    ~NetworkManager() {
        for (auto c : components) {
            delete c;
        }
        components.clear();
    }
};

#endif