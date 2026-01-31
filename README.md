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
```python
from Topology import NetworkManager
from PhysicsEngine import Solver

circuit = NetworkManager()
# Add resistors (Link between node 1 and 2 with R=10)
circuit.add_link(1, 2, 10.0) 
circuit.add_link(2, 0, 5.0)  # 0 is Ground

engine = Solver(circuit)
engine.compute([2.0, 0.0]) # Inject 2A at Node 1
```

### 2. Thermal Example (CanSat Chassis)
```python
# Modeling heat flow in a satellite structure
satellite = NetworkManager()
satellite.add_link(1, 2, 0.5) # Heat path
satellite.add_link(2, 0, 10.0) # Radiation to space

engine = Solver(satellite)
engine.compute([100.0, 0.0]) # 100W Heat from Sun
```

## Future Plans (Roadmap)
​This is v1.0 (Static Solver). I'm currently working on:
​MNA (Modified Nodal Analysis): Adding support for voltage sources and fixed constraints.
​Transient Analysis: Adding capacitors/thermal mass to simulate time-based behavior.

🐧 coded with love - torture and lots of confusion:))
