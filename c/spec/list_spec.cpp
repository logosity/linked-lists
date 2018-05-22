#include "catch.hpp"

#include <cstring>

extern "C" {
#include "list.h"
}

SCENARIO("Creating a Link") {
  GIVEN("A properly initialized link") {
    char link_value[] = "link";
    Link link = Link{link_value, NULL, NULL};

    THEN("the value and pointers are properly set up") {
      REQUIRE(strcmp(link.value, "link") == 0);
      REQUIRE(link.next == NULL);
      REQUIRE(link.ref == NULL);
    }
  }
}

SCENARIO("Lists can be created and cleaned up") {
  GIVEN("A single element List") {
    char link_value[] = "head";
    List list = List{};

    WHEN("a link is added") {
      add_link(&list, link_value);

      THEN("the value is set and the pointers are NULL") {
        REQUIRE(strcmp(list.head->value, "head") == 0);
        REQUIRE(list.head->next == NULL);
        REQUIRE(list.head->ref == NULL);
      }

      free_list(&list);

      THEN("the head is NULL") {
        REQUIRE(list.head == NULL);
      }

    }
  }

  GIVEN("A multi element List") {
    char head_value[] = "head";
    char second_value[] = "second";
    char third_value[] = "third";
    List list = List{};

    WHEN("links are added") {
      add_link(&list, head_value);
      add_link(&list, second_value);
      add_link(&list, third_value);

      THEN("the links are added sequentially") {
        REQUIRE(strcmp(list.head->value, "head") == 0);
        REQUIRE(strcmp(list.head->next->value, "second") == 0);
        REQUIRE(strcmp(list.head->next->next->value, "third") == 0);
      }
      free_list(&list);
    }
  }
  GIVEN("A multi element List") {
    char head_value[] = "head";
    char second_value[] = "second";
    char third_value[] = "third";
    List list = List{};

    WHEN("refs are added") {
      add_link(&list, head_value);
      add_link(&list, second_value);
      add_link(&list, third_value);

      set_ref(list.head, list.head->next->next);
      set_ref(list.head->next, list.head->next);
      set_ref(list.head->next->next, list.head);

      THEN("refs can point anywhere") {
        REQUIRE(strcmp(list.head->ref->value, "third") == 0);
        REQUIRE(strcmp(list.head->next->ref->value, "second") == 0);
        REQUIRE(strcmp(list.head->next->next->ref->value, "head") == 0);
      }
      free_list(&list);
    }
  }
}

SCENARIO("Problem Answer Test Cases") {
  GIVEN("A list matching the problem") {
    typedef struct {
      Link* head;
      Link* second;
      Link* third;
      Link* fourth;

    } test_links;

    char first_value[] = "Test1";
    char second_value[] = "Test2";
    char third_value[] = "Test3";
    char fourth_value[] = "Test4";
    List list = List{};

    add_link(&list, first_value);
    add_link(&list, second_value);
    add_link(&list, third_value);
    add_link(&list, fourth_value);

    set_ref(list.head, list.head->next->next->next);
    set_ref(list.head->next, list.head->next);
    set_ref(list.head->next->next, list.head->next);
    set_ref(list.head->next->next->next, list.head);

    test_links originals = {
      list.head,
      list.head->next,
      list.head->next->next,
      list.head->next->next->next
    };

    WHEN("list is copied") {
      List copy = List{};
      copy_list(&list, &copy);
      THEN("original values are unchanged") {
        REQUIRE(list.head->value == originals.head->value);
        REQUIRE(list.head->next->value == originals.second->value);
        REQUIRE(list.head->next->next->value == originals.third->value);
        REQUIRE(list.head->next->next->next->value == originals.fourth->value);
      }

      THEN("original links are unchanged") {
        REQUIRE(list.head == originals.head);
        REQUIRE(list.head->next == originals.second);
        REQUIRE(list.head->next->next == originals.third);
        REQUIRE(list.head->next->next->next == originals.fourth);
      }

      THEN("original refs are unchanged") {
        REQUIRE(list.head->ref == originals.head->ref);
        REQUIRE(list.head->next->ref == originals.second->ref);
        REQUIRE(list.head->next->next->ref == originals.third->ref);
        REQUIRE(list.head->next->next->next->ref == originals.fourth->ref);
      }

      THEN("copy values match originals") {
        REQUIRE(copy.head->value == originals.head->value);
        REQUIRE(copy.head->next->value == originals.second->value);
        REQUIRE(copy.head->next->next->value == originals.third->value);
        REQUIRE(copy.head->next->next->next->value == originals.fourth->value);
      }

      THEN("copy links link to different link objects") {
        REQUIRE(copy.head != originals.head);
        REQUIRE(copy.head->next != originals.second);
        REQUIRE(copy.head->next->next != originals.third);
        REQUIRE(copy.head->next->next->next != originals.fourth);
      }
      THEN("copy refs correspond to originals") {
        REQUIRE(copy.head->ref == copy.head->next->next->next);
        REQUIRE(copy.head->next->ref == copy.head->next);
        REQUIRE(copy.head->next->next->ref == copy.head->next);
        REQUIRE(copy.head->next->next->next->ref == copy.head);
      }

      free_list(&copy);

    }

    free_list(&list);
  }
}
/*
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
 */
