import numpy as np

class Solver:
    def __init__(self, manager):
        self.mindex = 0
        self.ans = None
        self.sAns = None
        
        sorted_nodes = sorted(manager.nodes.values(),key=lambda n:int(n.id))
        
        for node in sorted_nodes:
            if node.is_ground:
                node.matrix_index = -1
            else:
                node.matrix_index = self.mindex
                self.mindex += 1

        self.G = np.zeros((self.mindex, self.mindex), dtype=np.float64)

        for element in manager.elements:
            val = element.get_stamp()
            idx_in = element.node_in.matrix_index
            idx_out = element.node_out.matrix_index

            if idx_in != -1:
                self.G[idx_in, idx_in] += val
            if idx_out != -1:
                self.G[idx_out, idx_out] += val
            if idx_in != -1 and idx_out != -1:
                self.G[idx_in, idx_out] -= val
                self.G[idx_out, idx_in] -= val

    def solve(self, inputs):
        self.ans = np.linalg.solve(self.G, inputs)
        res_strings = [f"V{i+1}={val:.2f}" for i, val in enumerate(self.ans)]
        self.sAns = "Voltages: " + ", ".join(res_strings)
        return self.ans

    def print_ans(self):
        if self.sAns:
            print(self.sAns)

















