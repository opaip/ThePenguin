# Project Penguin 🐧

**A simple, general-purpose network solver for linear physical systems.**

I started Project Penguin to move beyond standard circuit solvers. The goal was to build a kernel that understands **graph topology** first, and applies physics second. This allows it to solve not just electrical circuits, but thermal and hydraulic networks too, since they all share the same underlying math ($Ax = b$).

## How it works
The core idea is simple: separate the **Structure** (Nodes/Links) from the **Physics**.
Instead of hardcoding "Voltage" or "Current", Penguin uses generic concepts:
* **Potential** (Voltage, Temperature, Pressure)
* **Flow** (Current, Heat Flux)
* **Conductance** (1/Resistance)

It builds the Laplacian Matrix for the network and solves for the equilibrium state using Linear Algebra principles.

## Features
* **Multi-Domain:** Works for Circuits, Heat transfer, etc.
* **Pure Python:** No heavy dependencies, just `numpy` for matrix math.
* **Readable Code:** Designed to be studied and extended (part of my learning roadmap for Complex Systems).

## The Math
For a network with $N$ nodes, we solve:
$$\mathbf{G} \cdot \mathbf{x} = \mathbf{b}$$

Where $\mathbf{G}$ is the Conductance Matrix, $\mathbf{x}$ is the Potentials vector, and $\mathbf{b}$ is the Inputs.

## Usage

### 1. Circuit Example (Wheatstone Bridge)

```cpp
#include <iostream>
#include <iomanip>
#include "Solver.h"

int main() {
    std::cout << "--- Project Penguin: Dynamic Physics Engine ---\n";

    // 1. Initialize the topology manager
    NetworkManager my_system;

    // 2. Build the network structure (Node A, Node B, Parameter Value)
    my_system.add_link(1, 2, 2.0);      // Conductive link (e.g., 2.0 Ohm Resistor)
    my_system.add_storage(2, 0, 0.5);   // Storage element (e.g., 0.5 Farad Capacitor connected to Ground)

    // 3. Initialize the Mathematical Solver Engine
    Solver engine(&my_system);

    // 4. Define simulation parameters
    Scalar dt = 0.1;                    // Time step (delta t) = 0.1 seconds
    Vector external_flux = {10.0, 0.0}; // Steady 10-unit flow injected into Node 1

    std::cout << std::setw(10) << "Time(s)" 
              << std::setw(15) << "Node 1 Potential" 
              << std::setw(15) << "Node 2 Potential" << "\n";
    std::cout << "---------------------------------------------\n";

    // 5. Run transient time-stepping loop (10 steps = 1.0 second)
    for (int step_idx = 1; step_idx <= 10; step_idx++) {
        Vector potentials = engine.step(dt, external_flux);
        
        std::cout << std::fixed << std::setprecision(2)
                  << std::setw(10) << (step_idx * dt)
                  << std::setw(15) << potentials[0]
                  << std::setw(15) << potentials[1] << "\n";
    }

    return 0;
}
```

## Future Plans (Roadmap)
​This is v1.1 (Dynamic Solver). I'm currently working on:
​MNA (Modified Nodal Analysis): Adding support for voltage sources and fixed constraints.
​Transient Analysis: Adding capacitors/thermal mass to simulate time-based behavior.

🐧 coded with love - torture and lots of confusion:))
