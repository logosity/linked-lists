class Node():
    def __init__(self, value):
        self._value = value
        self._next = None
        self._rand = None

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        self._value = value

    @property
    def next(self):
        return self._next

    @next.setter
    def next(self, next_node):
        self._next = next_node

    @property
    def rand(self):
        return self._rand

    @rand.setter
    def rand(self, rand_node):
        self._rand = rand_node

    def clone(self):
        new = Node(self.value)

        if self.next is self:
            new.next = new
            return new

        if self.next is not None:
            new.next = self.next.clone()
            return new

        return new


