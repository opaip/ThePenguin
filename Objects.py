class Node:
    def __init__(self, manager, is_ground=False):
        self.manager = manager
        self.is_ground = is_ground
        self.id = None
        self.matrix_index = None 
        

class GND(Node):
    def __init__(self, manager):
        super().__init__(manager, is_ground=True)
        self.id=0
        self.is_ground=True

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
        if self.value ==0:
            raise ZeroDivisionError
            
        return 1.0 / self.value
























