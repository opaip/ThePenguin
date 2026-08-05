#ifndef SOLVER_H
#define SOLVER_H

#include "Topology.h"
#include "MathUtils.h"
#include <iostream>
#include <algorithm>

class Solver {
private:
    NetworkManager* net;
    int system_size;
    Scalar current_time;

public:
    Solver(NetworkManager* network) : net(network), system_size(0), current_time(0.0) {}

    Matrix calculate_C(Scalar dt) {
        int m = net->components.size();
        Matrix C(m, Vector(m, 0.0)); 
        for (int i = 0; i < m; i++) {
            C[i][i] = net->components[i]->get_constitutive_value(dt);
        }  
        return C;
    }

    Vector calculate_y_hist(Scalar dt) {
        int m = net->components.size();
        Vector y(m, 0.0);
        for (int i = 0; i < m; i++) {
            y[i] = net->components[i]->get_history_source(dt);
        }
        return y;
    }

    Vector step(Scalar dt, Vector f_external) {
    
        Matrix A = net->calculate_A();
        int n = net->n_nodes;
        system_size = n + net->vsrc;

        if (system_size == 0) return Vector();

        
        Matrix G_sys(system_size, Vector(system_size, 0.0));
        Vector b_sys(system_size, 0.0);

        int m = net->components.size();
        if (m > 0) {
            Matrix C = calculate_C(dt);
            Vector y_hist = calculate_y_hist(dt);

            Matrix A_T = MathUtils::transpose(A);
            Matrix G = MathUtils::multiply(A_T, MathUtils::multiply(C, A));
            Vector f_hist = MathUtils::multiply(A_T, y_hist);

          
            Vector f_ext_aligned(n, 0.0);
            for (size_t i = 0; i < std::min((size_t)n, f_external.size()); i++) {
                f_ext_aligned[i] = f_external[i];
            }

            Vector b = MathUtils::add(f_ext_aligned, f_hist);

            
            for (int i = 0; i < G.size(); i++) {
                for (int j = 0; j < n; j++) {
                    if (j < G[i].size()) {
                        G_sys[i][j] = G[i][j];
                    }
                }
                if (i < b.size()) {
                    b_sys[i] = b[i];
                }
            }
        } else {
            for (size_t i = 0; i < std::min((size_t)n, f_external.size()); i++) {
                b_sys[i] = f_external[i];
            }
        }

        
        int k = 0;
        for (auto src : net->sources) {
            int idx_a = net->nodes[src->node_a].matrix_index;
            int idx_b = net->nodes[src->node_b].matrix_index;

            if (src->type == 1) {
                if (idx_a >= 0) b_sys[idx_a] -= src->value;
                if (idx_b >= 0) b_sys[idx_b] += src->value;
            } 
            else {
                int v_row = n + k;
                if (idx_a >= 0) {
                    G_sys[v_row][idx_a] = 1.0;
                    G_sys[idx_a][v_row] = 1.0;
                }
                if (idx_b >= 0) {
                    G_sys[v_row][idx_b] = -1.0;
                    G_sys[idx_b][v_row] = -1.0;
                }
                b_sys[v_row] = src->value;
                k++;
            }
        }

       
        Vector x = MathUtils::solve_linear_system(G_sys, b_sys);

        if (m > 0 && x.size() >= (size_t)n) {
            Vector x_nodes(n, 0.0);
            for (int i = 0; i < n; i++) {
                x_nodes[i] = x[i];
            }

            Vector e = MathUtils::multiply(A, x_nodes);
            for (int i = 0; i < m; i++) {
                net->components[i]->update_history(e[i]);
            }
        }

        current_time += dt;
        return x;
    }
};

#endif