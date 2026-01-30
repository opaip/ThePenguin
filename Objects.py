class Manage:
    def __init__(self):
        self.elements = [] 
        self.nodes = []
        self._next_node_id = 0

    def get_new_node_id(self):
        current_id = self._next_node_id
        self._next_node_id += 1
        return current_id

class Node:
    def __init__(self, manager, is_ground=False):
        self.manager = manager
        self.is_ground = is_ground
        self.id = 0 if is_ground else self.manager.get_new_node_id()
        self.matrix_index = None 
        
        self.manager.nodes.append(self)

class Element:
    def __init__(self, node_in, node_out, value, manager):
        self.node_in = node_in
        self.node_out = node_out
        self.value = value
        self.manager = manager
    
        self.manager.elements.append(self)

    def get_stamp(self):
        pass

class Resistor(Element):
    def __init__(self, node_in, node_out, value, manager):
        super().__init__(node_in, node_out, value, manager)

    def get_stamp(self):
        
        return 1.0 / self.value
