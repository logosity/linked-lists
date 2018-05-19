import unittest
from sure import expect, assertion

import lib
from lib.list import Node

################################################################################
class DeepCopyProblem(unittest.TestCase):
#**** problem answer test cases ****

    def setUp(self):

        #create list
        self.second = Node("Test2")
        self.third = Node("Test3")
        self.fourth = Node("Test4")
        self.head = lib.list.create(Node("Test1"), self.second, self.third, self.fourth)

        #set random links
        self.head.link_any(self.fourth)
        self.fourth.link_any(self.head)
        self.second.link_any(self.second)
        self.third.link_any(self.second)

        #create deep copy
        self.copy = self.head.copy()

    def test_original_links_unchanged(self):
        self.head.next.should.be(self.second)
        self.second.next.should.be(self.third)
        self.third.next.should.be(self.fourth)
        self.fourth.next.should.be(None)

    def test_original_random_refs_unchanged(self):
        self.head.rand.should.be(self.fourth)
        self.second.rand.should.be(self.second)
        self.third.rand.should.be(self.second)
        self.fourth.rand.should.be(self.head)

    def test_copy_values_match_original_values(self):
        self.copy.value.should.equal(self.head.value)
        self.copy.next.value.should.equal(self.second.value)
        self.copy.next.next.value.should.equal(self.third.value)
        self.copy.next.next.next.value.should.equal(self.fourth.value)

    def test_copy_nodes_different_objects_than_originals(self):
        self.copy.value.should.equal(self.head.value)
        self.copy.should.not_be(self.head)
        self.copy.next.should.not_be(self.second)
        self.copy.next.next.should.not_be(self.third)
        self.copy.next.next.next.should.not_be(self.fourth)

    def test_copy_random_refs_correspond_to_original(self):
        self.copy.rand.should.be(self.copy.next.next.next)
        self.copy.next.rand.should.be(self.copy.next)
        self.copy.next.next.rand.should.be(self.copy.next)
        self.copy.next.next.next.rand.should.be(self.copy)

################################################################################

class DeepCopyImplementation(unittest.TestCase):
    def test_copying_nodes(self):
        head = lib.list.create(Node("head"), Node("second"), Node("third"), Node("fourth"))

        head._copy_nodes()

        head.value.should.equal("head")
        head.next.value.should.equal("head")
        head.next.next.value.should.equal("second")
        head.next.next.next.value.should.equal("second")
        head.next.next.next.next.value.should.equal("third")
        head.next.next.next.next.next.value.should.equal("third")
        head.next.next.next.next.next.next.value.should.equal("fourth")
        head.next.next.next.next.next.next.next.value.should.equal("fourth")
        head.next.next.next.next.next.next.next.next.should.equal(None)

    def test_copying_random_refs(self):
        second = Node("second")
        third = Node("third")
        fourth = Node("fourth")
        head = lib.list.create(Node("head"), second, third, fourth)

        head.link_any(fourth)
        fourth.link_any(head)
        second.link_any(second)
        third.link_any(second)

        head._copy_nodes()
        head._copy_rand_refs()

        head.rand.should.be(fourth)
        second.rand.should.be(second)
        third.rand.should.be(second)
        fourth.rand.should.be(head)

        head.next.rand.should.be(fourth.next)
        fourth.next.rand.should.be(head.next)
        second.next.rand.should.be(second.next)
        third.next.rand.should.be(second.next)

    def test_unset_random_refs(self):
        second = Node("second")
        head = lib.list.create(Node("head"), second)

        head.link_any(head)

        head.rand.should.be(head)
        head.next.rand.should.equal(None)

        copy = head.copy()

        copy.rand.should.be(copy)
        copy.next.rand.should.equal(None)

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
        head.link_any(head)
        second.link_any(head)

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

