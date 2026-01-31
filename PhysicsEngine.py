import numpy as np

class Solver:
    """THe computaion code to extract the system information"""
    def __init__(self, network):
        self.mindex = 0
        self.solution = None
        self.report = ""
        
        # sorting the nodes to make a meaningful connection between matrix index and id
        sorted_nodes = sorted(network.nodes.values(), key=lambda n: int(n.id))
        
        for node in sorted_nodes:
            if node.is_reference:
                node.matrix_index = -1
            else:
                node.matrix_index = self.mindex
                self.mindex += 1

        # system matrix
        self.M = np.zeros((self.mindex, self.mindex), dtype=np.float64)

        for element in network.elements:
            val = element.get_contribution()
            idx_in = element.node_in.matrix_index
            idx_out = element.node_out.matrix_index

            if idx_in != -1:
                self.M[idx_in, idx_in] += val
            if idx_out != -1:
                self.M[idx_out, idx_out] += val
            if idx_in != -1 and idx_out != -1:
                self.M[idx_in, idx_out] -= val
                self.M[idx_out, idx_in] -= val

    def compute(self, excitations):
        """solving the matrix based on the inputs"""
        self.solution = np.linalg.solve(self.M, excitations)
        res_strings = [f"P{i+1}={val:.4f}" for i, val in enumerate(self.solution)]
        self.report = "System Potentials: " + ", ".join(res_strings)
        return self.solution

    def display_results(self):
        if self.report:
            print(self.report)
