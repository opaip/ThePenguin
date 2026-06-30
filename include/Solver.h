#ifndef SOLVER_H
#define SOLVER_H

#include "Topology.h"
#include "MathUtils.h"
#include <iostream>

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
        
        for(int i = 0; i < m; i++) {
           
            C[i][i] = net->components[i]->get_constitutive_value(dt);
        }  
        return C;
    }

    
    Vector calculate_y_hist(Scalar dt) {
        int m = net->components.size();
        Vector y(m, 0.0);
        
        for(int i = 0; i < m; i++) {
            y[i] = net->components[i]->get_history_source(dt);
        }
        return y;
    }
	
	

	
	Vector step(Scalar dt, Vector f_external) {
        
        Matrix A = net->calculate_A();
        
        
        Matrix C = calculate_C(dt);
        Vector y_hist = calculate_y_hist(dt);

        
        Matrix A_T = MathUtils::transpose(A);
        Matrix G = MathUtils::multiply(A_T, MathUtils::multiply(C, A));
    	Vector f_hist = MathUtils::multiply(A_T, y_hist);
        
        
        Vector b = MathUtils::add(f_external, f_hist);

        
        Vector x = MathUtils::solve_linear_system(G, b);

        
        Vector e = MathUtils::multiply(A,x);
        for(int i=0;i<net->components.size();i++){
			net->components[i]->update_history(e[i]);
		}

        current_time += dt;
        return x;
    }
	
	
};

#endif