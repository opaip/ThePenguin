from Objects import *

class Manage:
    def __init__(self):
        self.GND = GND(self)
        self.elements = [] 
        self.nodes = {"0": self.GND} 

    

    def add_R(self, node_in_id, node_out_id, value):
        
        id_in = str(node_in_id)
        id_out = str(node_out_id)

        if id_in not in self.nodes:
            n_in = Node(self)
            n_in.id = int(id_in)
            self.nodes[id_in] = n_in
        else:
            n_in = self.nodes[id_in]

        if id_out not in self.nodes:
            n_out = Node(self)
            n_out.id = int(id_out)
            self.nodes[id_out] = n_out
        else:
            n_out = self.nodes[id_out]
            
        Resistor(n_in, n_out, value, self)





















