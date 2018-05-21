#include "catch.hpp"

#include <cstring>

extern "C" {
#include "list.h"
}

TEST_CASE("Creating Link", "[Link]") {
  char link_value[] = "link";
  auto link = Link{link_value, NULL, NULL};
  REQUIRE(strcmp(link.value, "link") == 0);
}

TEST_CASE("default next is null", "[Link]") {
  char link_value[] = "link";
  auto link = Link{link_value, NULL, NULL};
  REQUIRE(link.next == NULL);
}

TEST_CASE("default ref is null", "[Link]") {
  char link_value[] = "link";
  auto link = Link{link_value, NULL, NULL};
  REQUIRE(link.ref == NULL);
}

TEST_CASE("Create single element List", "[List, add_link]") {
  char link_value[] = "head";
  auto list = List{};
  add_link(&list, link_value);
  REQUIRE(strcmp(list.head->value, "head") == 0);
  REQUIRE(list.head->next == NULL);
  REQUIRE(list.head->ref == NULL);
  free_list(&list);
}

TEST_CASE("free links created by list", "[List, free_list]") {
  char link_value[] = "head";
  auto list = List{};
  add_link(&list, link_value);
  free_list(&list);
  REQUIRE(list.head == NULL);
}

TEST_CASE("Create multi element List", "[List]") {
  char head_value[] = "head";
  char second_value[] = "second";
  char third_value[] = "third";
  auto list = List{};
  add_link(&list, head_value);
  add_link(&list, second_value);
  add_link(&list, third_value);
  REQUIRE(strcmp(list.head->value, "head") == 0);
  REQUIRE(strcmp(list.head->next->value, "second") == 0);
  REQUIRE(strcmp(list.head->next->next->value, "third") == 0);
  free_list(&list);
}
