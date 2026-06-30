#include <iostream>
#include <iomanip>
#include "Solver.h"

int main() {
    std::cout << "--- Project Penguin: Dynamic Physics Engine ---\n";
    std::cout << ">> Mode: Transient Time-Stepping Analysis (Backward Euler)\n\n";

    NetworkManager my_system;

    
    my_system.add_link(1, 2, 2.0);      
    my_system.add_storage(2, 0, 0.5);

    Solver engine(&my_system);

    Scalar dt = 0.1;
    Vector external_flux = {10.0, 0.0};

    std::cout << std::setw(10) << "Time(s)" 
              << std::setw(15) << "Node 1 (V)" 
              << std::setw(15) << "Node 2 (V)" << "\n";
    std::cout << "---------------------------------------------\n";

    
    for (int step_idx = 1; step_idx <= 10; step_idx++) {
        Vector potentials = engine.step(dt, external_flux);
        
        std::cout << std::fixed << std::setprecision(2)
                  << std::setw(10) << (step_idx * dt)
                  << std::setw(15) << potentials[0]
                  << std::setw(15) << potentials[1] << "\n";
    }

    std::cout << "\n>> Simulation completed successfully.\n";
    return 0;
}