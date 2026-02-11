#ifndef PENGUIN_KERNEL_H
#define PENGUIN_KERNEL_H

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <iomanip>

// --- Infrastructure Layer ---

struct Node {
    int id;
    bool is_reference; // Ground (0V)
    int matrix_index;  // Index in the system matrix (0 to N-1)

    Node(int _id = 0, bool _ref = false) 
        : id(_id), is_reference(_ref), matrix_index(-1) {}
};

struct Link {
    int node_in_id;
    int node_out_id;
    double value;       // Resistance
    double conductance; // 1/Resistance

    Link(int in, int out, double val) : node_in_id(in), node_out_id(out), value(val) {
        if (std::abs(val) < 1e-9) conductance = 1e9; // Avoid division by zero
        else conductance = 1.0 / val;
    }
};

// --- Topology Layer ---

class NetworkManager {
public:
    std::map<int, Node> nodes;
    std::vector<Link> elements;

    NetworkManager() {
        // Create Reference Node (ID: 0)
        nodes[0] = Node(0, true);
    }

    void add_link(int id_start, int id_end, double value) {
        // Create nodes if they don't exist
        if (nodes.find(id_start) == nodes.end()) nodes[id_start] = Node(id_start);
        if (nodes.find(id_end) == nodes.end()) nodes[id_end] = Node(id_end);

        elements.emplace_back(id_start, id_end, value);
    }
};

// --- Physics Engine & Math Layer ---

class Solver {
private:
    NetworkManager* network;
    int system_size;
    std::vector<std::vector<double>> G_matrix; // Conductance Matrix
    std::vector<double> results;

    // First Principles: Custom Gaussian Elimination Solver
    // Solves Ax = b
    std::vector<double> solve_linear_system(std::vector<std::vector<double>> A, std::vector<double> b) {
        int n = A.size();

        // Forward Elimination
        for (int i = 0; i < n; i++) {
            // Partial Pivoting
            int max_row = i;
            for (int k = i + 1; k < n; k++) {
                if (std::abs(A[k][i]) > std::abs(A[max_row][i])) {
                    max_row = k;
                }
            }
            std::swap(A[i], A[max_row]);
            std::swap(b[i], b[max_row]);

            // Make triangular
            for (int k = i + 1; k < n; k++) {
                double factor = A[k][i] / A[i][i];
                b[k] -= factor * b[i];
                for (int j = i; j < n; j++) {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }

        // Back Substitution
        std::vector<double> x(n);
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0;
            for (int j = i + 1; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
        return x;
    }

public:
    Solver(NetworkManager* net) : network(net), system_size(0) {
        assign_indices();
        build_matrix();
    }

    void assign_indices() {
        system_size = 0;
        // Map allows strictly ordered iteration by ID, ensuring consistent indexing
        for (auto& pair : network->nodes) {
            if (!pair.second.is_reference) {
                pair.second.matrix_index = system_size;
                system_size++;
            } else {
                pair.second.matrix_index = -1;
            }
        }
    }

    void build_matrix() {
        // Initialize N x N matrix with 0.0
        G_matrix.assign(system_size, std::vector<double>(system_size, 0.0));

        for (const auto& el : network->elements) {
            int idx_in = network->nodes[el.node_in_id].matrix_index;
            int idx_out = network->nodes[el.node_out_id].matrix_index;
            double g = el.conductance;

            // Apply Stamping Rule (MNA basis)
            if (idx_in != -1)  G_matrix[idx_in][idx_in] += g;
            if (idx_out != -1) G_matrix[idx_out][idx_out] += g;
            
            if (idx_in != -1 && idx_out != -1) {
                G_matrix[idx_in][idx_out] -= g;
                G_matrix[idx_out][idx_in] -= g;
            }
        }
    }
	std::vector<double> compute(std::vector<double> inputs) {
        if (inputs.size() != system_size) {
            std::cerr << "Error: Input vector size mismatch!" << std::endl;
            return {};
        }
        results = solve_linear_system(G_matrix, inputs);
        return results;
    }

    void print_results() {
        std::cout << "\n--- System State (Potentials) ---\n";
        int i = 0;
        for (const auto& pair : network->nodes) {
            if (!pair.second.is_reference) {
                std::cout << "Node " << pair.first << ": " 
                          << std::fixed << std::setprecision(4) << results[i] << " (Unit)" << std::endl;
                i++;
            } else {
                std::cout << "Node " << pair.first << ": 0.0000 (Ref)" << std::endl;
            }
        }
    }
};

#endif