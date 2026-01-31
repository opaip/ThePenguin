class Junction:
    """a point in state space which potentioal gets defined in"""
    def __init__(self, manager, is_reference=False):
        self.manager = manager
        self.is_reference = is_reference
        self.id = None
        self.matrix_index = None 

class ReferenceNode(Junction):
    """refrence point of the system"""
    def __init__(self, manager):
        super().__init__(manager, is_reference=True)
        self.id = 0 # refrence node's id is 0

class Component:
    """basic class for every elements"""
    def __init__(self, node_in, node_out, value, manager):
        self.node_in = node_in
        self.node_out = node_out
        self.value = value
        self.manager = manager
        # adding the element to the manager
        self.manager.elements.append(self)

    def get_contribution(self):
        """Stamping"""
        pass

class TransferLink(Component):
    """Modeling conductance between 2 nodes"""
    def __init__(self, node_in, node_out, value, manager):
        super().__init__(node_in, node_out, value, manager)

    def get_contribution(self):
        if self.value == 0:
            raise ZeroDivisionError("the value cant be zero")
        return 1.0 / self.value # conductance
