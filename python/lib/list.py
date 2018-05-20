################################################################################
# Deep Copy in time O(n), space O(1). Used the following link for reference:
# https://www.tutorialcup.com/linked-list/clone-linked-list-next-random-pointer.htm
################################################################################
from collections.abc import Sequence

class List(Sequence):
    def __init__(self, *links):
        self._head = None

        if len(links) == 0:
            return

        if len(links) == 1 and isinstance(links[0], Link):
            self._head = links[0]
            return

        for n in reversed(links):
            link = Link(n)
            link.next = self._head
            self._head = link

    def __getitem__(self, i):
        if not self.head:
            raise IndexError("list index out of range")

        link = self.head
        for x in range(i):
            if not link.next:
                raise IndexError
            link = link.next

        return link

        while link is not None:
            result += 1
            link = self.head.next


    def __len__(self, i):
        result = 0
        link = self.head
        while link is not None:
            result += 1
            link = self.head.next

    @property
    def head(self):
        return self._head

    def copy(self):
        self._copy_links()
        self._copy_refs()

        current = self.head
        copy = self.head.next
        while current is not None:
            current_copy = current.next
            current.next = current.next.next

            if current_copy.next:
                current_copy.next = current_copy.next.next

            current = current.next

        return List(copy)

    def _copy_links(self):
        current = self.head
        while current is not None:
            new = Link(current.value)
            new.next = current.next
            current.next = new
            current = new.next

    def _copy_refs(self):
        current = self.head
        while current is not None:
            if current.ref:
                current.next.ref = current.ref.next

            current = current.next.next

class Link:
    def __init__(self, value):
        self._value = value
        self._next = None
        self._ref = None

    @property
    def value(self):
        return self._value

    @property
    def next(self):
        return self._next

    @next.setter
    def next(self, link):
        self._next = link

    @property
    def ref(self):
        return self._ref

    @ref.setter
    def ref(self, link):
        self._ref = link

