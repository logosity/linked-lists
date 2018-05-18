import unittest

from unittest.mock import ANY, Mock, PropertyMock, call
from sure import expect, assertion

import lib
from lib.list import Node, Clone

    #@unittest.skip("WIP")

class CreatingNodes(unittest.TestCase):
    def setUp(self):
        self.node = Node("Hello")

    def test_single_node_value(self):
        self.node.value.should.equal("Hello")

    def test_default_next(self):
        self.node.next.should.equal(None)

    def test_linking(self):
        n = Node("next")
        self.node.link(n).should.be(n)
        self.node.next.should.be(n)

    def test_chaining_links(self):
        head = Node("head")
        head.link(Node("second")).link(Node("third")).link(Node("fourth"))

        head.value.should.equal("head")
        head.next.value.should.equal("second")
        head.next.next.value.should.equal("third")
        head.next.next.next.value.should.equal("fourth")
        head.next.next.next.next.should.equal(None)

    def test_random_refs(self):
        head = Node("head")
        second = Node("second")
        head.rand = head
        second.rand = head

        head.rand.should.be(head)
        second.rand.should.be(head)

    def test_creating_empty_lists(self):
        lib.list.create().should.equal(None)

    def test_creating_single_node_lists(self):
        head = lib.list.create(Node("head"))
        head.value.should.equal("head")
        head.next.should.equal(None)
        head.rand.should.equal(None)

    def test_creating_multi_node_lists(self):
        head = lib.list.create(Node("head"), Node("second"))
        head.value.should.equal("head")
        head.next.value.should.equal("second")
        head.next.next.should.equal(None)

class CloningListTest(unittest.TestCase):
    def setUp(self):
        pass

    def test_copying_nodes(self):
        head = lib.list.create(Node("head"), Node("second"), Node("third"), Node("fourth"))

        algo = Clone()
        algo._copy_nodes(head)

        head.value.should.equal("head")
        head.next.value.should.equal("head")
        head.next.next.value.should.equal("second")
        head.next.next.next.value.should.equal("second")
        head.next.next.next.next.value.should.equal("third")
        head.next.next.next.next.next.value.should.equal("third")
        head.next.next.next.next.next.next.value.should.equal("fourth")
        head.next.next.next.next.next.next.next.value.should.equal("fourth")
        head.next.next.next.next.next.next.next.next.should.equal(None)

    @unittest.skip("WIP")
    def test_copying_random_refs(self):
        second = Node("second")
        third = Node("third")
        fourth = Node("fourth")
        head = lib.list.create(Node("head"), second, third, fourth)

        head.rand = fourth
        fourth.rand = head
        second.rand = second
        third.rand = second

        algo = Clone()
        algo._copy_nodes(head)
        algo._copy_rand_refs(head)

        head.rand.should.be(fourth)
        fourth.rand.should.be(head)
        second.rand.should.be(second)
        third.rand.should.be(second)

        head.next.rand.should.be(fourth.next)
        fourth.next.rand.should.be(head.next)
        second.next.rand.should.be(second.next)
        third.next.rand.should.be(second.next)

#    def setUp(self):
#        self.head = Node("Test1")
#        self.second = Node("Test2")
#        self.third = Node("Test3")
#        self.fourth = Node("Test4")
#
#        self.head.next = self.second
#        self.second.next = self.third
#        self.third.next = self.fourth
#
#    def test_values(self):
#        result = self.head.clone()
#
#        result.value.should.equal("Test1")
#        result.next.value.should.equal("Test2")
#        result.next.next.value.should.equal("Test3")
#        result.next.next.next.value.should.equal("Test4")
#
#    def test_identities(self):
#        result = self.head.clone()
#
#        result.should.not_be(self.head)
#        result.next.should.not_be(self.second)
#        result.next.next.should.not_be(self.third)
#        result.next.next.next.should.not_be(self.fourth)
#
#        result.next.next.next.next.should.equal(None)

#class RandomRefs(CloningMultiElements):
#    def setUp(self):
#
#        super().setUp()
#
#        self.head.rand = self.fourth
#        self.fourth.rand = self.head
#        self.second.rand = self.second
#        self.third.rand = self.second
#
#        self.result = self.head.clone()
#        self.new_head = self.result
#        self.new_second = self.result.next
#        self.new_third = self.result.next.next
#        self.new_fourth = self.result.next.next.next
#
#    @unittest.skip("WIP")
#    def test_random_identities(self):
#        self.new_head.rand.should.be(self.new_fourth)
#        self.new_fourth.rand.should.be(self.new_head)
#        self.new_second.rand.should.be(self.new_second)
#        self.new_third.rand.should.be(self.new_second)
#


