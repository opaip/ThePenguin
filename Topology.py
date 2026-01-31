from Infrastructure import *

class NetworkManager:
    """topology management and system configuration"""
    def __init__(self):
        self.reference = ReferenceNode(self)
        self.elements = [] 
        self.nodes = {"0": self.reference} # saving the nodes

    def add_link(self, id_start, id_end, value):
        """making a path between tow point of a system"""
        ids = [str(id_start), str(id_end)]
        target_nodes = []

        for node_id in ids:
            if node_id not in self.nodes:
                new_node = Junction(self)
                new_node.id = int(node_id)
                self.nodes[node_id] = new_node
                target_nodes.append(new_node)
            else:
                target_nodes.append(self.nodes[node_id])

       # making the path
        TransferLink(target_nodes[0], target_nodes[1], value, self)
