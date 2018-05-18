import unittest

from unittest.mock import ANY, Mock, PropertyMock, call
from sure import expect, assertion

from lib.list import Node

    #@unittest.skip("WIP")

class CreatingLists(unittest.TestCase):
    def setUp(self):
        self.node = Node("Hello")

    def test_single_node_value(self):
        self.node.value.should.equal("Hello")

    def test_single_node_next(self):
        self.node.next.should.equal(None)

class CloningOneElementLists(unittest.TestCase):
    def setUp(self):
        self.node = Node("Hello")

    def test_single_node_value(self):
        result = self.node.clone()

        result.value.should.equal("Hello")
        result.should.not_be(self.node)

    def test_value_after_mutation(self):
        result = self.node.clone()

        self.node.value = "World"

        result.value.should.equal("Hello")
        self.node.value.should.equal("World")

    def test_single_node_next(self):
        result = self.node.clone()

        result.next.should.equal(None)
        result.should.not_be(self.node)

    def test_single_node_self_ref(self):
        self.node.next = self.node

        result = self.node.clone()

        result.value.should.equal("Hello")
        result.next.should.be(result)

class CloningMultiElements(unittest.TestCase):
    def setUp(self):
        self.first = Node("Test1")
        self.second = Node("Test2")
        self.third = Node("Test3")
        self.fourth = Node("Test4")

        self.first.next = self.second
        self.second.next = self.third
        self.third.next = self.fourth

    def test_values(self):
        result = self.first.clone()

        result.value.should.equal("Test1")
        result.next.value.should.equal("Test2")
        result.next.next.value.should.equal("Test3")
        result.next.next.next.value.should.equal("Test4")

    def test_identities(self):
        result = self.first.clone()

        result.should.not_be(self.first)
        result.next.should.not_be(self.second)
        result.next.next.should.not_be(self.third)
        result.next.next.next.should.not_be(self.fourth)

        result.next.next.next.next.should.equal(None)

class RandomRefs(CloningMultiElements):
    def setUp(self):

        super().setUp()

        self.first.rand = self.fourth
        self.fourth.rand = self.first
        self.second.rand = self.second
        self.third.rand = self.second

        self.result = self.first.clone()
        self.new_first = self.result
        self.new_second = self.result.next
        self.new_third = self.result.next.next
        self.new_fourth = self.result.next.next.next

    def test_random_identities(self):
        self.new_first.rand.should.be(self.new_fourth)
        self.new_fourth.rand.should.be(self.new_first)
        self.new_second.rand.should.be(self.new_second)
        self.new_third.rand.should.be(self.new_second)

