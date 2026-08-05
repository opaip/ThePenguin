#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <map>
#include <vector>
#include <memory>
#include "Infrastructure.h"

class NetworkManager {
public:
    std::map<int, Node> nodes;  
    std::vector<Component*> components;
    std::vector<Source*> sources;
    int vsrc{0};
    int n_nodes{0};
    
	
    
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
    
    void add_source(int n1,int n2, Scalar value,bool type)// 0:potential , 1:current
    {
    	ensure_nodes(n1, n2);
    	if(type==0) vsrc++;
    	sources.push_back((new Source(n1,n2,value,type)));
    	
	}

    void ensure_nodes(int n1, int n2) {
        if (nodes.find(n1) == nodes.end()) nodes[n1] = Node(n1);
        if (nodes.find(n2) == nodes.end()) nodes[n2] = Node(n2);
    }
    
    Matrix calculate_A() {
        int m = components.size();
        
        
       
        for(auto& [id, node] : nodes) {
            if (!node.is_reference) {
                node.matrix_index = n_nodes;
                n_nodes++;
            } else {
                node.matrix_index = -1;
            }
        }
        
        Matrix A(m, Vector(n_nodes, 0.0));
        
        
       
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
        
        for (auto s : sources) {
            delete s;
        }
        sources.clear();
    }
};

#endif