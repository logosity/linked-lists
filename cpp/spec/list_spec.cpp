#include "catch.hpp"

#include <string>
#include "list.h"

TEST_CASE("Creating Link", "[Link]") {
  auto link = Link("link");
  REQUIRE(link.value == "link");
}

TEST_CASE("default next is null", "[Link]") {
  auto link = Link("link");
  REQUIRE(link.next == nullptr);
}

TEST_CASE("default ref is null", "[Link]") {
  auto link = Link("link");
  REQUIRE(link.ref == nullptr);
}

TEST_CASE("Create single element List", "[List]") {
  auto list = List("link");
  REQUIRE(list.head->value == "link");
}

TEST_CASE("Create multi element List", "[List]") {
  auto list = List(Values{"head", "second"});
  REQUIRE(list.head->value == "head");
  REQUIRE(list.head->next->value == "second");
}
