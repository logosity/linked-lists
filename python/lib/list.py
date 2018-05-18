def create(*nodes):
    result = None
    for n in reversed(nodes):
        n.link(result)
        result = n
        
    return result

class Node:
    def __init__(self, value):
        self._value = value
        self._next = None
        self._rand = None

    def link(self, next_node):
        self._next = next_node
        return self._next

    @property
    def next(self):
        return self._next

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        self._value = value

    @property
    def rand(self):
        return self._rand

    @rand.setter
    def rand(self, rand_node):
        self._rand = rand_node

class Clone:
    def _copy_nodes(self, head):
        node = head
        while node is not None:
            new = Node(node.value)
            new.link(node.next)
            node.link(new)
            node = new.next
