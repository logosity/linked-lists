#include "catch.hpp"

#include <cstring>

extern "C" {
#include "list.h"
}

SCENARIO("Creating a Link (Sanity Check)") {
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
    List list = List{};

    WHEN("a link is added") {
      Link* link = list_add_link(&list, "head");
      REQUIRE(link != NULL);
      REQUIRE(link == list.head);

      THEN("the value is set, the pointers are NULL and value is mutable") {
        REQUIRE(strcmp(list.head->value, "head") == 0);
        REQUIRE(list.head->next == NULL);
        REQUIRE(list.head->ref == NULL);

        list.head->value[2] = 'e';
        REQUIRE(strcmp(list.head->value, "heed") == 0);
      }

      list_free(&list);

      THEN("the head is NULL") {
        REQUIRE(list.head == NULL);
      }

    }
  }

  GIVEN("A multi element List") {
    List list = List{};

    WHEN("links are added") {
      list_add_link(&list, "head");
      list_add_link(&list, "second");
      Link* third = list_add_link(&list, "third");

      REQUIRE(third == list.head->next->next);
      REQUIRE(NULL == list.head->next->next->next);

      THEN("the links are added sequentially") {
        REQUIRE(strcmp(list.head->value, "head") == 0);
        REQUIRE(strcmp(list.head->next->value, "second") == 0);
        REQUIRE(strcmp(list.head->next->next->value, "third") == 0);
      }
      list_free(&list);
    }
  }
  GIVEN("A multi element List") {
    List list = List{};
    list_add_link(&list, "head");
    list_add_link(&list, "second");
    list_add_link(&list, "third");

    WHEN("refs are added") {
      list_set_ref(list.head, list.head->next->next);
      list_set_ref(list.head->next, list.head->next);
      list_set_ref(list.head->next->next, list.head);

      THEN("refs can point anywhere and do not affect link order") {
        REQUIRE(strcmp(list.head->ref->value, "third") == 0);
        REQUIRE(strcmp(list.head->next->ref->value, "second") == 0);
        REQUIRE(strcmp(list.head->next->next->ref->value, "head") == 0);

        REQUIRE(strcmp(list.head->value, "head") == 0);
        REQUIRE(strcmp(list.head->next->value, "second") == 0);
        REQUIRE(strcmp(list.head->next->next->value, "third") == 0);
        REQUIRE(list.head->next->next->next == NULL);
      }
      list_free(&list);
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

    List list = List{};

    list_add_link(&list, "Test1");
    list_add_link(&list, "Test2");
    list_add_link(&list, "Test3");
    list_add_link(&list, "Test4");

    list_set_ref(list.head, list.head->next->next->next);
    list_set_ref(list.head->next, list.head->next);
    list_set_ref(list.head->next->next, list.head->next);
    list_set_ref(list.head->next->next->next, list.head);

    test_links originals = {
      list.head,
      list.head->next,
      list.head->next->next,
      list.head->next->next->next
    };

    WHEN("list is copied") {
      List copy = {};
      list_copy(&list, &copy);
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
        REQUIRE(list.head->next->next->next->next == NULL);
      }

      THEN("original refs are unchanged") {
        REQUIRE(list.head->ref == originals.head->ref);
        REQUIRE(list.head->next->ref == originals.second->ref);
        REQUIRE(list.head->next->next->ref == originals.third->ref);
        REQUIRE(list.head->next->next->next->ref == originals.fourth->ref);
      }

      THEN("copy values match originals") {
        REQUIRE(strcmp(copy.head->value, originals.head->value) == 0);
        REQUIRE(strcmp(copy.head->next->value, originals.second->value) == 0);
        REQUIRE(strcmp(copy.head->next->next->value, originals.third->value) == 0);
        REQUIRE(strcmp(copy.head->next->next->next->value, originals.fourth->value) == 0);
      }

      THEN("changing original values does not change copies") {
        list.head->value[4] = '9';
        REQUIRE(strcmp(list.head->value, "Test9") == 0);
        REQUIRE(strcmp(copy.head->value, "Test1") == 0);
      }

      THEN("copy links link to different link objects") {
        REQUIRE(copy.head != originals.head);
        REQUIRE(copy.head->next != originals.second);
        REQUIRE(copy.head->next->next != originals.third);
        REQUIRE(copy.head->next->next->next != originals.fourth);
        REQUIRE(copy.head->next->next->next->next == NULL);
      }

      THEN("copy refs correspond to originals") {
        REQUIRE(copy.head->ref == copy.head->next->next->next);
        REQUIRE(copy.head->next->ref == copy.head->next);
        REQUIRE(copy.head->next->next->ref == copy.head->next);
        REQUIRE(copy.head->next->next->next->ref == copy.head);
      }

      list_free(&copy);

    }

    list_free(&list);
  }
}

SCENARIO("Refs are optional") {
  GIVEN("A multi element List") {
    List list = List{};
    list_add_link(&list, "first");
    list_add_link(&list, "second");

    WHEN("one ref is added and list is copied") {
      list_set_ref(list.head, list.head);
      REQUIRE(list.head->ref == list.head);
      REQUIRE(list.head->next->ref == NULL);

      List copy = {};
      list_copy(&list, &copy);

      THEN("copy refs still refer to originals") {
        REQUIRE(copy.head->ref == copy.head);
        REQUIRE(copy.head->next->ref == NULL);
      }

      list_free(&list);
      list_free(&copy);
    }
  }
}
