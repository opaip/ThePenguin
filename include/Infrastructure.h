#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

#include "Types.h"


struct Node {
    int id;
    bool is_reference;
    int matrix_index;

    Node(int _id = 0, bool _ref = false) 
        : id(_id), is_reference(_ref), matrix_index(-1) {}
};


class Component {
public:
    int node_a;
    int node_b;
    Scalar resistance;

    Component(int n1, int n2, Scalar r) : node_a(n1), node_b(n2), resistance(r) {}


    int mat_idx_a = -1;
    int mat_idx_b = -1;

    virtual void stamp(Matrix& G) = 0;
};


class Link : public Component {
public:
    Link(int n1, int n2, Scalar r) : Component(n1, n2, r) {}

    void stamp(Matrix& G) override {
        
        Scalar conductance = 1.0 / resistance; 

        if (mat_idx_a != -1) G[mat_idx_a][mat_idx_a] += conductance;
        if (mat_idx_b != -1) G[mat_idx_b][mat_idx_b] += conductance;
        
        if (mat_idx_a != -1 && mat_idx_b != -1) {
            G[mat_idx_a][mat_idx_b] -= conductance;
            G[mat_idx_b][mat_idx_a] -= conductance;
        }
    }
};

#endif