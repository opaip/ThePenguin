#include <iostream>
#include <iomanip>
#include <cmath>
#include "Solver.h"

int main() {
    std::cout << "--- Project Penguin: Mixed Source MNA Test ---\n\n";

    NetworkManager system;

    system.add_source(1, 0, 10.0, false);
    system.add_source(0, 2, 3.0, true);

    
    system.add_link(1, 2, 2.0);
    system.add_link(2, 0, 4.0); 

    Solver engine(&system);

    Scalar dt = 1.0; 
    Vector external_flux = {0.0, 0.0};

    Vector x = engine.step(dt, external_flux);

    Scalar v1_exact = 10.0;
    Scalar v2_exact = 32.0 / 3.0;
    Scalar i_vs_exact = (v2_exact - v1_exact) / 2.0;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Node 1 Voltage:\n"
              << "  Expected : " << v1_exact << " V\n"
              << "  Computed : " << x[0] << " V\n\n";

    std::cout << "Node 2 Voltage:\n"
              << "  Expected : " << v2_exact << " V\n"
              << "  Computed : " << x[1] << " V\n\n";

    if (x.size() > 2) {
        std::cout << "Voltage Source Branch Current:\n"
                  << "  Expected : " << i_vs_exact << " A\n"
                  << "  Computed : " << x[2] << " A\n\n";
    }

    bool pass_v1 = std::abs(x[0] - v1_exact) < 1e-4;
    bool pass_v2 = std::abs(x[1] - v2_exact) < 1e-4;

    if (pass_v1 && pass_v2) {
        std::cout << ">> TEST PASSED: MNA formulation for mixed sources is correct.\n";
    } else {
        std::cout << ">> TEST FAILED: Mismatch in MNA matrix assembly.\n";
    }

    return 0;
}