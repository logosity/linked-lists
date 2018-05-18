class Node():
    def __init__(self, value):
        self._value = value
        self._next = None

    @property
    def value(self):
        return self._value

    @property
    def next(self):
        return self._next

    @next.setter
    def next(self, next_node):
        self._next = next_node

    def clone(self):
        new = Node(self.value)
        new.next = self.next
        return new
