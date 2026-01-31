from Topology import Manage
from PhysicsEngine import Solver
import numpy as np


m = Manage()


m.add_R(1, 2, 10.0)
m.add_R(1, 3, 20.0)
m.add_R(2, 0, 30.0)
m.add_R(3, 0, 40.0)
m.add_R(2, 3, 50.0)


solve_engine = Solver(m)


inputs = np.array([1.0, 0.0, 0.0]) 


voltages = solve_engine.solve(inputs)


solve_engine.print_ans()
