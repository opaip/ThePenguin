#ifndef SOLVER_H
#define SOLVER_H

#include "Topology.h"
#include "MathUtils.h"

class Solver {
    NetworkManager* net;
    int system_size;
    
public:
    Solver(NetworkManager* network) : net(network), system_size(0) {}

   
    void assign_indices() {
        system_size = 0;
        for (auto& pair : net->nodes) {
            if (!pair.second.is_reference) {
                pair.second.matrix_index = system_size;
                system_size++;
            } else {
                pair.second.matrix_index = -1;
            }
        }
    }

   
    Vector compute(Vector inputs) {
        assign_indices();
        
        
        Matrix G(system_size, Vector(system_size, 0.0));

       
        for (auto& r : net->resistors) {
            int idx_a = net->nodes[r.node_a].matrix_index;
            int idx_b = net->nodes[r.node_b].matrix_index;
            Scalar g = r.get_conductance();

            if (idx_a != -1) G[idx_a][idx_a] += g;
            if (idx_b != -1) G[idx_b][idx_b] += g;
            
            if (idx_a != -1 && idx_b != -1) {
                G[idx_a][idx_b] -= g;
                G[idx_b][idx_a] -= g;
            }
        }

       
        return MathUtils::solve_linear_system(G, inputs);
    }
    
    void print_results(Vector potentials) {
        std::cout << "\n--- Results ---\n";
        int i = 0;
        for (auto const& [id, node] : net->nodes) {
            if (!node.is_reference) {
                std::cout << "Node " << id << ": " << potentials[i] << " V\n";
                i++;
            } else {
                std::cout << "Node " << id << ": 0.0000 V (Ref)\n";
            }
        }
    }
};

#endif