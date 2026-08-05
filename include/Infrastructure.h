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
    Scalar value; 

    Component(int n1, int n2, Scalar v) : node_a(n1), node_b(n2), value(v) {}
    virtual ~Component() {}

    virtual Scalar get_constitutive_value(Scalar dt) = 0;
    virtual Scalar get_history_source(Scalar dt) = 0; 
    virtual void update_history(Scalar e) = 0;
};

class Source : public Component {
public :
    bool type;  
    
    
    Source(int n1, int n2, Scalar v, bool t) : Component(n1, n2, v), type(t) {} // 0:potential , 1:current
    
    Scalar get_constitutive_value(Scalar dt) override {
        return 0.0;
    }
    Scalar get_history_source(Scalar dt) override {
        return value; 
    }
    void update_history(Scalar e) override {}
};

class Link : public Component {
public:
    Link(int n1, int n2, Scalar r) : Component(n1, n2, r) {}

    Scalar get_constitutive_value(Scalar dt) override {
        return 1.0 / value;
    }

    Scalar get_history_source(Scalar dt) override {
        return 0.0;
    }
    
    void update_history(Scalar e) override {}
};

class Storage : public Component {
public:
    Scalar potential_old;

    Storage(int n1, int n2, Scalar c) 
        : Component(n1, n2, c), potential_old(0.0) {}

    Scalar get_constitutive_value(Scalar dt) override {
        return value / dt;
    }

    Scalar get_history_source(Scalar dt) override {
        return (value / dt) * potential_old;
    }

    void update_history(Scalar e) override {
        potential_old = e;
    }
};

#endif