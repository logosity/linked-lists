import unittest

from unittest.mock import ANY, Mock, PropertyMock, call
from sure import expect, assertion

from lib.list import Node

#@unittest.skip("WIP")

class CreatingLists(unittest.TestCase):
    def setUp(self):
        pass

    def test_single_node_value(self):
        node = Node("Hello")
        node.value.should.equal("Hello")

    def test_single_node_next(self):
        node = Node("Hello")
        node.next.should.equal(None)

class CloningLists(unittest.TestCase):
    def setUp(self):
        pass

    def test_single_node_value(self):
        node = Node("Hello")

        result = node.clone()
        result.value.should.equal("Hello")
        result.should.not_be(node)

    def test_single_node_next(self):
        node = Node("Hello")

        result = node.clone()
        result.next.should.equal(None)
        result.should.not_be(node)

    @unittest.skip("WIP")
    def test_single_node_self_ref(self):
        node = Node("Hello")
        node.next = node

        result = node.clone()
        result.value.should.equal("Hello")
        result.next.should.equal(result)
        result.should.not_be(node)

