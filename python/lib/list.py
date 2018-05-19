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

################################################################################
# Deep Copy in time O(n), space O(1). Used the following link for reference:
# https://www.tutorialcup.com/linked-list/clone-linked-list-next-random-pointer.htm
    def copy(self):
        self._copy_nodes()
        self._copy_rand_refs()

        current = self
        copy = self.next
        while current is not None:
            current_copy = current.next
            current.link(current.next.next)

            if current_copy.next:
                current_copy.link(current_copy.next.next)

            current = current.next

        return copy

    def _copy_nodes(self):
        current = self
        while current is not None:
            new = Node(current.value)
            new.link(current.next)
            current.link(new)
            current = new.next

    def _copy_rand_refs(self):
        current = self
        while current is not None:
            if current.rand:
                current.next.link_any(current.rand.next)

            current = current.next.next

################################################################################

    @property
    def next(self):
        return self._next

    @property
    def rand(self):
        return self._rand

    @property
    def value(self):
        return self._value

    def link(self, next_node):
        self._next = next_node
        return self._next

    def link_any(self, random_node):
        self._rand = random_node
        return self._rand

    @value.setter
    def value(self, value):
        self._value = value

