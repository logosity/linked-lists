import unittest
from sure import expect, assertion

import lib
from lib.list import List, Link

################################################################################
class DeepCopyProblem(unittest.TestCase):
#**** problem answer test cases ****

    def setUp(self):
        self.list = List("Test1", "Test2", "Test3", "Test4")

        #set arbitrary links
        self.list[0].ref = self.list[3]
        self.list[1].ref = self.list[1]
        self.list[2].ref = self.list[1]
        self.list[3].ref = self.list[0]

        self.copy = self.list.copy()

    def test_original_links_unchanged(self):
        self.list[0].next.should.be(self.list[1])
        self.list[1].next.should.be(self.list[2])
        self.list[2].next.should.be(self.list[3])
        self.list[3].next.should.be(None)

    def test_original_refs_unchanged(self):
        self.list[0].ref.should.be(self.list[3])
        self.list[1].ref.should.be(self.list[1])
        self.list[2].ref.should.be(self.list[1])
        self.list[3].ref.should.be(self.list[0])

    def test_copy_values_match_original_values(self):
        self.copy[0].value.should.equal(self.list[0].value)
        self.copy[1].value.should.equal(self.list[1].value)
        self.copy[2].value.should.equal(self.list[2].value)
        self.copy[3].value.should.equal(self.list[3].value)

    def test_copy_links_different_objects_than_originals(self):
        self.copy[0].value.should.equal(self.list[0].value)
        self.copy[0].should.not_be(self.list[0])
        self.copy[1].should.not_be(self.list[1])
        self.copy[2].should.not_be(self.list[2])
        self.copy[3].should.not_be(self.list[3])

    def test_copy_refs_correspond_to_original(self):
        self.copy[0].ref.should.be(self.copy[3])
        self.copy[1].ref.should.be(self.copy[1])
        self.copy[2].ref.should.be(self.copy[1])
        self.copy[3].ref.should.be(self.copy[0])

################################################################################

class DeepCopyImplementation(unittest.TestCase):
    def setUp(self):
        self.list = List("first", "second", "third", "fourth")

    def test_copying_links(self):
        self.list._copy_links()

        self.list[0].value.should.equal("first")
        self.list[1].value.should.equal("first")
        self.list[2].value.should.equal("second")
        self.list[3].value.should.equal("second")
        self.list[4].value.should.equal("third")
        self.list[5].value.should.equal("third")
        self.list[6].value.should.equal("fourth")
        self.list[7].value.should.equal("fourth")
        self.list[7].next.should.equal(None)

    def test_copying_refs(self):
        self.list[0].ref = self.list[3]
        self.list[1].ref = self.list[1]
        self.list[2].ref = self.list[1]
        self.list[3].ref = self.list[0]

        self.list._copy_links()
        self.list._copy_refs()

        self.list[0].ref.should.be(self.list[6])
        self.list[2].ref.should.be(self.list[2])
        self.list[4].ref.should.be(self.list[2])
        self.list[6].ref.should.be(self.list[0])

        self.list[1].ref.should.be(self.list[7])
        self.list[3].ref.should.be(self.list[3])
        self.list[5].ref.should.be(self.list[3])
        self.list[7].ref.should.be(self.list[1])

    def test_unset_refs(self):
        self.list = List("first", "second")

        self.list[0].ref = self.list[0]

        self.list[0].ref.should.be(self.list[0])
        self.list[0].next.ref.should.equal(None)

        copy = self.list.copy()

        copy[0].ref.should.be(copy[0])
        copy[0].next.ref.should.equal(None)

class CreatingLists(unittest.TestCase):
    def test_creating_empty_lists(self):
        List().head.should.equal(None)

    def test_out_of_bounds(self):
        List().__getitem__.when.called_with(0).should.throw(IndexError, "list index out of range")
        List("first").__getitem__.when.called_with(1).should.throw(IndexError)

    def test_creating_single_link_lists(self):
        List("head")[0].value.should.equal("head")
        List("head")[0].next.should.equal(None)
        List("head")[0].ref.should.equal(None)

    def test_creating_multi_link_lists(self):
        List("head", "second")[0].value.should.equal("head")
        List("head", "second")[1].value.should.equal("second")
        List("head", "second")[1].next.should.equal(None)

class CreatingLinks(unittest.TestCase):
    def setUp(self):
        self.link = Link("Hello")

    def test_single_link_value(self):
        self.link.value.should.equal("Hello")

    def test_default_next(self):
        self.link.next.should.equal(None)

    def test_default_ref(self):
        self.link.ref.should.equal(None)

