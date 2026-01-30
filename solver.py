import numpy as np
from Objects import *

class Solver:
    def __init__(self,manager:Manage):
        self.mindex = 0
        for node in manager.nodes:
            if node.is_ground:
                node.matrix_index = -1
            else:
                node.matrix_index = self.mindex
                self.mindex+=1

        self.G = np.matrix(np.zeros((self.mindex, self.mindex), dtype = np.float64))

        for element in manager.elements:
            val = element.get_stamp()
            idx_in = element.node_in.matrix_index
            idx_out = element.node_out.matrix_index

            if not element.node_in.is_ground:
                self.G[idx_in, idx_in] += val

            if not element.node_out.is_ground:
                self.G[idx_out, idx_out] += val

            if not element.node_in.is_ground and not element.node_out.is_ground:
                self.G[idx_in, idx_out] -= val
                self.G[idx_out, idx_in] -= val

        
