#include <iostream>
#include "Solver.h"

int main() {
    std::cout << "--- Project Penguin: General Physics Kernel ---\n";
    std::cout << ">> Mode: Static Equilibrium Analysis\n\n";

    
    NetworkManager my_system;


    my_system.add_link(1, 2, 0.5);
    my_system.add_link(2, 3, 2.0); 
    my_system.add_link(3, 0, 10.0); 

    
    Solver engine(&my_system);

    
    Vector flows = {100.0, 0.0, 0.0}; 

    std::cout << ">> Solving System Matrix [G * P = F]...\n";
    Vector results = engine.compute(flows);

    engine.print_results(results);
    
    std::cout << "\n[Interpret]: If inputs were Amps, output is Volts.";
    std::cout << "\n[Interpret]: If inputs were Watts, output is Kelvin (above ref).\n";

    int temp; std::cin >> temp;
    return 0;
}