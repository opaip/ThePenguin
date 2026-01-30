from solver import *
from Objects import *
import numpy as np


m = Manage()
gnd = Node(m, is_ground=True) # ID 0
n1 = Node(m) # ID 1
n2 = Node(m) # ID 2
n3 = Node(m) # ID 3


r1 = Resistor(n1, n2, 2, m)
r2 = Resistor(n1, n3, 4, m)
r3 = Resistor(n2, n3, 5, m) 
r4 = Resistor(n2, gnd, 10, m)
r5 = Resistor(n3, gnd, 8, m)


solver = Solver(m)
I_vec = np.array([5.0, 0.0, 0.0]) 
V = np.linalg.solve(solver.G, I_vec)

print("Matrix G (3x3):")
print(solver.G)
print(f"Voltages: V1={V[0]:.2f}, V2={V[1]:.2f}, V3={V[2]:.2f}")